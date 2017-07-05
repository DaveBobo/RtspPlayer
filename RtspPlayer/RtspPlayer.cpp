
#include "stdafx.h"
#include "RtspPlayer.h"
#include "ourRTSPClient.h"
#include "StaticData.h"

// If you don't want to see debugging output for each received frame, then comment out the following line:
//#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1
// If you don't want to save the stream into the file, then comment out the following line:
//#define SAVE_THE_STREAM_INTO_FILE 1

char url[BUFFER_SIZE]		= {0};	// url地址数组
HANDLE tRecvHandle			= NULL;	// 循环接收视频数据线程句柄

LONG ScreenWidth = 640;
LONG ScreenHeight = 480;

//// live555相关变量定义
//static RTSPClient*			rtspClient	= NULL;

char eventLoopWatchVariable = START_EVENT_LOOP;
PacketQueue* videoq			= NULL;

// 状态控制的全局变量
bool isPause				= false;	// false:代表当前状态非暂停状态；	true,则代表当前状态为暂停状态

char nalu_buffer[NALU_BUFFER_SIZE]	= {0};	// 用于保存添加起始码等信息的视频数据
char* p_nalu_tail = nalu_buffer;			// nalu_buffer数组的游标

static struct timeval pre_time_stamp = {0,0};
unsigned char const start_code[START_CODE_SIZE] = {0x00, 0x00, 0x00, 0x01};	// 起始码

#ifdef SAVE_THE_STREAM_INTO_FILE
FILE* fout = fopen(VIDEOFILE, "wb");	// 用于保存接收到的H264视频文件
#endif

//ffmpeg//
AVCodec *codec			= NULL;
AVCodecContext *c		= NULL;
AVFrame *decoded_frame	= NULL;

SDL_Thread*		SdlPlayThread = NULL;
SDL_Surface*	Screen	= NULL;

HWND			SmartPlayer	= NULL;
MSG				SendMsg;		// 发送给SmartPlayer的消息

//////////////////////////////////////////////////////////////////////////////////////////////////////

// 播放线程
int play_thread(LPVOID lpParam)
{
	SDL_Surface* Screen	= (SDL_Surface*)lpParam;

	int frameFinished = 0;
	bool isFirst = true;
    static struct SwsContext *img_convert_ctx;

    SDL_Overlay		*bmp;
    SDL_Rect        rect;
	
	rect.x = 0;
	rect.y = 0;
	rect.w = ScreenWidth;
	rect.h = ScreenHeight;

    decoded_frame = avcodec_alloc_frame();

	AVPacket pkt, *packet = &pkt;

	while(packet_queue_get(videoq, packet, 1) >= 0)
	{
		if(isFirst)
		{
			SendMsg.wParam = WPARAM_PLAYING;
			SendMessageToSmartPlayer(SmartPlayer, SendMsg);
			isFirst = false;
		}
		// Decode video frame
		avcodec_decode_video2(c, decoded_frame, &frameFinished, packet);
	
		// Did we get a video frame?
		if(frameFinished)
		{
			// Allocate a place to put our YUV image on that screen
			bmp = SDL_CreateYUVOverlay(c->width, c->height, SDL_YV12_OVERLAY, Screen);
			
			img_convert_ctx = sws_getContext(c->width, c->height, c->pix_fmt,
				c->width, c->height, PIX_FMT_YUV420P,
				SWS_BICUBIC, NULL, NULL, NULL);
			
			SDL_LockYUVOverlay(bmp);

			AVPicture pict;
			pict.data[0] = bmp->pixels[0];
			pict.data[1] = bmp->pixels[2];
			pict.data[2] = bmp->pixels[1];

			pict.linesize[0] = bmp->pitches[0];
			pict.linesize[1] = bmp->pitches[2];
			pict.linesize[2] = bmp->pitches[1];

			// Convert the image into YUV format that SDL uses
			sws_scale(img_convert_ctx, (const uint8_t * const *)decoded_frame->data,
				decoded_frame->linesize, 0, c->height,
				pict.data, pict.linesize);

			SDL_UnlockYUVOverlay(bmp);
			SDL_DisplayYUVOverlay(bmp, &rect);
			SDL_FreeYUVOverlay(bmp);
			sws_freeContext(img_convert_ctx);
		}
		av_free_packet(packet);
	}
	return 0;
}

// 清除一些全局变量.为下一次播放做准备
void ClearPlayerResoure()
{
	eventLoopWatchVariable = STOP_EVENT_LOOP;

	if(!SdlPlayThread)
	{
		SDL_KillThread(SdlPlayThread);
		SdlPlayThread = NULL;
	}

	// SDL刷新 否则最大化然后缩小有问题
	SDL_Flip(Screen);

	if(NULL != videoq)
	{
		packet_queue_destroy(videoq);
		delete videoq;
		videoq = NULL;
	}

	if(NULL != codec)
		codec = NULL;

	if(NULL != c)
	{
		avcodec_close(c);
		av_free(c);
		c = NULL;
	}

	if(NULL != decoded_frame)
	{
		avcodec_free_frame(&decoded_frame);
		decoded_frame = NULL;
	}

	p_nalu_tail = nalu_buffer;
	memset(nalu_buffer, '\0', NALU_BUFFER_SIZE);

	memset(url, '\0', BUFFER_SIZE);
	
	pre_time_stamp.tv_sec	= 0;
	pre_time_stamp.tv_usec	= 0;
	fHaveWrittenFirstFrame	= false;
	isPause					= false;
	eventLoopWatchVariable	= START_EVENT_LOOP;
	

	CloseHandle(tRecvHandle);
	tRecvHandle = NULL;
}


DWORD WINAPI RTSP_Recv(LPVOID lpParameter)
{
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	UsageEnvironment* env = MyUsageEnvironment::createNew(*scheduler);
	
	openURL(*env, "rtsp_player", url);

	// All subsequent activity takes place within the event loop:
	// This function call does not return, unless, at some point in time, "eventLoopWatchVariable" gets set to something non-zero.
	env->taskScheduler().doEventLoop(&eventLoopWatchVariable);

	if(SmartPlayer)
		::PostMessage(SmartPlayer, WM_RTSP, WPARAM_CLOSE, 0);

	return 0;
}

// 发送消息到SmartPlayer
bool SendMessageToSmartPlayer(HWND hWnd, MSG msg)
{
	if(!hWnd)
		hWnd = ::FindWindowA(NULL, PLAYER_NAME);
	if(!hWnd)
		return false;

	::SendMessage(hWnd, msg.message, msg.wParam, msg.lParam);

	return true;
}

// 响应SmartPlayer发送来的开始消息
bool OnMessageStart(WPARAM wParam, LPARAM lParam)
{
	ScreenWidth = wParam;
	ScreenHeight = lParam;

	if((ScreenWidth <= 0) || (ScreenHeight <= 0))
	{
		// 告之SmartPlayer播放不行了
		SendMsg.wParam = WPARAM_CLOSE;
		SendMessageToSmartPlayer(SmartPlayer, SendMsg);
		return false;
	}

// 初始化m_screen模式
	int flags = SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_HWACCEL | SDL_RESIZABLE;
	Screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, 0, flags);
	if (!Screen)
	{
		// 告之SmartPlayer播放不行了
		SendMsg.wParam = WPARAM_CLOSE;
		SendMessageToSmartPlayer(SmartPlayer, SendMsg);
		return false;
	}

//初始化解码器
	if(!ffmpeg_init())
	{
		// 告之SmartPlayer播放不行了
		SendMsg.wParam = WPARAM_CLOSE;
		SendMessageToSmartPlayer(SmartPlayer, SendMsg);
		return false;
	}

// 每次播放前为队列申请内存，播放停止后释放掉该内存
	videoq = new PacketQueue;
	packet_queue_init(videoq);

// 开启接收线程
	HANDLE tRecvHandle = CreateThread(NULL, 0, RTSP_Recv, NULL, 0, NULL);
	if(NULL == tRecvHandle)
	{
		CloseHandle(tRecvHandle);
		// 告之SmartPlayer播放不行了
		SendMsg.wParam = WPARAM_CLOSE;
		SendMessageToSmartPlayer(SmartPlayer, SendMsg);
		return false;
	}

// 对话框类this指针为参数,传给播放线程
	SdlPlayThread = SDL_CreateThread(play_thread, (void*)Screen);	
	if(!SdlPlayThread)
	{
		// 告之SmartPlayer播放不行了
		SendMsg.wParam = WPARAM_CLOSE;
		SendMessageToSmartPlayer(SmartPlayer, SendMsg);
		return false;
	}

	// SDL刷新 否则最大化然后缩小有问题
	SDL_Flip(Screen);

	/*if(SmartPlayer)
		::PostMessage(SmartPlayer, WM_RTSP, WPARAM_RECT, 0);*/
	return true;
}

int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	// 得到命令行参数,并对其进行判断正误
	// 若从SmartPlayer中启动该进程,则命令行参数为SDL_WINDOWID=%d形式
	LPSTR sdl_var = GetCommandLine();
	
	int TempLen = strlen("SDL_WINDOWID\0");
	char* Temp = new char[TempLen];
	memset(Temp, '\0', TempLen);
	memcpy(Temp, "SDL_WINDOWID", TempLen);
	for(int i = 0; i < TempLen; ++i)
	{
		if(Temp[i] != sdl_var[i])
		{
			MessageBox(NULL, _T("参数错误"), _T("提示"), MB_OK);
			return 0;
		}
	}

	MSG				RecvMsg;		// 用于接收Message的消息

	FILE* UrlFile = fopen(URLFILE, "r");
	if(!UrlFile)
	{
		SendMsg.wParam = WPARAM_CLOSE;
		if(!SendMessageToSmartPlayer(SmartPlayer, SendMsg))
		{
			MessageBox(NULL, _T("请运行SmartPlayer"), _T("提示"), MB_OK);
			return 0;
		}
	}

	fread(url, BUFFER_SIZE, 1, UrlFile);
	
	fclose(UrlFile);
	UrlFile = NULL;

	// 告之SmartPlayer我已启动
	SendMsg.hwnd = NULL;
	SendMsg.message = WM_RTSP;
	SendMsg.wParam = WPARAM_START;
	SendMsg.lParam = 0;
	if(!SendMessageToSmartPlayer(SmartPlayer, SendMsg))
	{
		MessageBox(NULL, _T("请运行SmartPlayer"), _T("提示"), MB_OK);
		return 0;
	}

	SDL_putenv(sdl_var);
	char *myvalue = SDL_getenv("SDL_WINDOWID");   // 让SDL取得窗口ID

    while(GetMessage(&RecvMsg,NULL,0,0))
    {
        TranslateMessage(&RecvMsg);
        DispatchMessage(&RecvMsg);

		if(!::FindWindowA(NULL, PLAYER_NAME))
		{
			ClearPlayerResoure();
			return 0 ;
		}

		if(WM_PLAYER != RecvMsg.message)
			continue;

		if(WPARAM_STOP == RecvMsg.wParam)
			break;

		if(WPARAM_PAUSE == RecvMsg.wParam)
		{
			isPause = !isPause;

			SendMsg.wParam = WPARAM_PAUSE;
			SendMessageToSmartPlayer(SmartPlayer, SendMsg);
			continue;
		}
		
		if(!OnMessageStart(RecvMsg.wParam, RecvMsg.lParam))
		{
			// 告之SmartPlayer播放不行了
			SendMsg.wParam = WPARAM_CLOSE;
			SendMessageToSmartPlayer(SmartPlayer, SendMsg);
			break;
		}

    }

	ClearPlayerResoure();

	/*MessageBox(NULL, _T("播放结束"), _T("提示"), MB_OK);*/
	SendMsg.wParam = WPARAM_CLOSE;
	SendMessageToSmartPlayer(SmartPlayer, SendMsg);

    return 0;
}





DummySink* DummySink::createNew(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId)
{
	return new DummySink(env, subsession, streamId);
}

DummySink::DummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId)
  : MediaSink(env), fSubsession(subsession)
{
	fStreamId = strDup(streamId);
	fReceiveBuffer = new u_int8_t[NALU_BUFFER_SIZE];
}

DummySink::~DummySink()
{
	delete[] fReceiveBuffer;
	delete[] fStreamId;
}

void DummySink::afterGettingFrame(void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned durationInMicroseconds)
{
	DummySink* sink = (DummySink*)clientData;
	sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
}

void DummySink::afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned /*durationInMicroseconds*/) 
{
  // We've just received a frame of data.  (Optionally) print out information about it:
#ifdef DEBUG_PRINT_EACH_RECEIVED_FRAME
	if (fStreamId != NULL) envir() << "Stream \"" << fStreamId << "\"; ";
	envir() << fSubsession.mediumName() << "/" << fSubsession.codecName() << ":\tReceived " << frameSize << " bytes";
	if (numTruncatedBytes > 0) envir() << " (with " << numTruncatedBytes << " bytes truncated)";
	char uSecsStr[6+1]; // used to output the 'microseconds' part of the presentation time
	sprintf(uSecsStr, "%06u", (unsigned)presentationTime.tv_usec);
	envir() << ".\tPresentation time: " << (int)presentationTime.tv_sec << "." << uSecsStr;
	//if (fSubsession.rtpSource() != NULL && !fSubsession.rtpSource()->hasBeenSynchronizedUsingRTCP()) {
	//  envir() << "!"<<"\n"; // mark the debugging output to indicate that this presentation time is not RTCP-synchronized
	//}
	if (fSubsession.rtpSource() != NULL) {
	//  envir() << fSubsession.rtpSource()->curPacketRTPSeqNum()<<"\n";
		fprintf(stderr, "yyyyyyyyyyyy%d\n", fSubsession.rtpSource()->curPacketRTPSeqNum());
	}
#ifdef DEBUG_PRINT_NPT
	envir() << "\tNPT: " << fSubsession.getNormalPlayTime(presentationTime);
#endif

	envir() << "\n";

#endif
	// 此时,fReceiveBuffer中保存着接收到的视频数据,对该帧数据进行保存
	if((0 == strcmp(fSubsession.codecName(),"H264")) && (!isPause))
	{
	  if (!fHaveWrittenFirstFrame)			// 仅每次播放的第一次进入执行本段代码
	  {	// 对视频数据的SPS,PPS进行补偿
		  unsigned numSPropRecords;
		  SPropRecord* sPropRecords = parseSPropParameterSets(fSubsession.fmtp_spropparametersets(), numSPropRecords);
		  // spydroid v6.8 or spydroid v9.1.
		  for (unsigned i = 0; i < numSPropRecords; ++i) 
		  {
			  memcpy(p_nalu_tail, start_code, sizeof(start_code));
			  p_nalu_tail += sizeof(start_code);
			  memcpy(p_nalu_tail, sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength);
			  p_nalu_tail += sPropRecords[i].sPropLength;
		  }
		 
		  fHaveWrittenFirstFrame = true; // 标记SPS,PPS已经完成补偿

		  memcpy(p_nalu_tail, start_code, sizeof(start_code));
		  p_nalu_tail += sizeof(start_code);
		  memcpy(p_nalu_tail, fReceiveBuffer, frameSize);
		  p_nalu_tail += frameSize;
	  }
	  else
	  {
		  if(presentationTime.tv_sec == pre_time_stamp.tv_sec && presentationTime.tv_usec == pre_time_stamp.tv_usec)
		  {
			  memcpy(p_nalu_tail, start_code, sizeof(start_code));
			  p_nalu_tail += sizeof(start_code);
			  memcpy(p_nalu_tail, fReceiveBuffer, frameSize);
			  p_nalu_tail += frameSize;
		  }
		  else
		  {
			  if(p_nalu_tail != nalu_buffer)
			  {
				  AVPacket packet, *pkt = &packet;
				  av_new_packet(pkt, p_nalu_tail - nalu_buffer);
				  memcpy(pkt->data , nalu_buffer, p_nalu_tail - nalu_buffer);
				  packet_queue_put(videoq, pkt);
			  }
			  p_nalu_tail = nalu_buffer;
			  memcpy(p_nalu_tail, start_code, sizeof(start_code));
			  p_nalu_tail += sizeof(start_code);
			  memcpy(p_nalu_tail, fReceiveBuffer, frameSize);
			  p_nalu_tail += frameSize;
		  }
	  }
	  pre_time_stamp = presentationTime;
	}

// 可选的保存视频数据到Recieved.264文件
#ifdef SAVE_THE_STREAM_INTO_FILE
	if(NULL == fout)
	{
		envir() << "打开输出文件失败\n";
		return;
	}
	fwrite(nalu_buffer, p_nalu_tail - nalu_buffer, 1, fout);
#endif
	
	continuePlaying();								// 继续,请求下一帧数据
}

Boolean DummySink::continuePlaying() 
{
	if (fSource == NULL) 
		return False; // sanity check (should not happen)

	// Request the next frame of data from our input source.  "afterGettingFrame()" will get called later, when it arrives:
	fSource->getNextFrame(fReceiveBuffer, NALU_BUFFER_SIZE,
						afterGettingFrame, this,
						onSourceClosure, this);
	return True;
}

// Implementation of the RTSP 'response handlers':

void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString) {
	do
	{
		UsageEnvironment& env = rtspClient->envir(); // alias
		StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias

		if (resultCode != 0) 
		{
			env << *rtspClient << "Failed to get a SDP description: " << resultString << "\n";
			delete[] resultString;
			break;
		}

		char* const sdpDescription = resultString;

		env << *rtspClient << "Got a SDP description:\n" << sdpDescription << "\n";

		// Create a media session object from this SDP description:
		scs.session = MediaSession::createNew(env, sdpDescription);
		delete[] sdpDescription; // because we don't need it anymore
		if (scs.session == NULL) 
		{
			env << *rtspClient << "Failed to create a MediaSession object from the SDP description: " << env.getResultMsg() << "\n";
			break;
		} 
		else if (!scs.session->hasSubsessions()) 
		{
			env << *rtspClient << "This session has no media subsessions (i.e., no \"m=\" lines)\n";
			break;
		}

		// Then, create and set up our data source objects for the session.  We do this by iterating over the session's 'subsessions',
		// calling "MediaSubsession::initiate()", and then sending a RTSP "SETUP" command, on each one.
		// (Each 'subsession' will have its own data source.)
		scs.iter = new MediaSubsessionIterator(*scs.session);
		setupNextSubsession(rtspClient);
		return;
	}
	while (0);

	// An unrecoverable error occurred with this stream.
	shutdownStream(rtspClient);
}

void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString) {
	do
	{
		UsageEnvironment& env = rtspClient->envir(); // alias
		StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias

		if (resultCode != 0) 
		{
			env << *rtspClient << "Failed to set up the \"" << *scs.subsession << "\" subsession: " << resultString << "\n";
			break;
		}
		env << *rtspClient << "Set up the \"" << *scs.subsession << "\" subsession (";
		if (scs.subsession->rtcpIsMuxed())
			env << "client port " << scs.subsession->clientPortNum();
		else 
			env << "client ports " << scs.subsession->clientPortNum() << "-" << scs.subsession->clientPortNum()+1;
		env << ")\n";

		// Having successfully setup the subsession, create a data sink for it, and call "startPlaying()" on it.
		// (This will prepare the data sink to receive data; the actual flow of data from the client won't start happening until later,
		// after we've sent a RTSP "PLAY" command.)

		scs.subsession->sink = DummySink::createNew(env, *scs.subsession, rtspClient->url());
		  // perhaps use your own custom "MediaSink" subclass instead
		if (scs.subsession->sink == NULL)
		{
			env << *rtspClient << "Failed to create a data sink for the \"" << *scs.subsession
			<< "\" subsession: " << env.getResultMsg() << "\n";
			break;
		}

		env << *rtspClient << "Created a data sink for the \"" << *scs.subsession << "\" subsession\n";
		scs.subsession->miscPtr = rtspClient; // a hack to let subsession handle functions get the "RTSPClient" from the subsession 
		scs.subsession->sink->startPlaying(*(scs.subsession->readSource()),
						   subsessionAfterPlaying, scs.subsession);
		// Also set a handler to be called if a RTCP "BYE" arrives for this subsession:
		if (scs.subsession->rtcpInstance() != NULL)
		{
			scs.subsession->rtcpInstance()->setByeHandler(subsessionByeHandler, scs.subsession);
		}
	}
	while (0);
	
	delete[] resultString;

	// Set up the next subsession, if any:
	setupNextSubsession(rtspClient);
}

void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString) {
	Boolean success = False;

	do
	{
		UsageEnvironment& env = rtspClient->envir(); // alias
		StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias

		if (resultCode != 0)
		{
			env << *rtspClient << "Failed to start playing session: " << resultString << "\n";
			break;
		}

		env << *rtspClient << "Started playing session";
		if (scs.duration > 0)
		{
			env << " (for up to " << scs.duration << " seconds)";
		}
		env << "...\n";

		success = True;
	} 
	while (0);

	delete[] resultString;

	if (!success)
	{
		// An unrecoverable error occurred with this stream.
		shutdownStream(rtspClient);
	}
}



// Implementation of the other event handlers:
void subsessionAfterPlaying(void* clientData)
{
	MediaSubsession* subsession = (MediaSubsession*)clientData;
	RTSPClient* rtspClient = (RTSPClient*)(subsession->miscPtr);

	// Begin by closing this subsession's stream:
	Medium::close(subsession->sink);
	subsession->sink = NULL;

	// Next, check whether *all* subsessions' streams have now been closed:
	MediaSession& session = subsession->parentSession();
	MediaSubsessionIterator iter(session);
	while ((subsession = iter.next()) != NULL) 
	{
		if (subsession->sink != NULL)
			return; // this subsession is still active
	}

	// All subsessions' streams have now been closed, so shutdown the client:
	shutdownStream(rtspClient);
}

void subsessionByeHandler(void* clientData)
{
	MediaSubsession* subsession = (MediaSubsession*)clientData;
	RTSPClient* rtspClient = (RTSPClient*)subsession->miscPtr;
	UsageEnvironment& env = rtspClient->envir(); // alias

	env << *rtspClient << "Received RTCP \"BYE\" on \"" << *subsession << "\" subsession\n";

	// Now act as if the subsession had closed:
	subsessionAfterPlaying(subsession);
}

void streamTimerHandler(void* clientData)
{
	ourRTSPClient* rtspClient = (ourRTSPClient*)clientData;
	StreamClientState& scs = rtspClient->scs; // alias

	scs.streamTimerTask = NULL;

	// Shut down the stream:
	shutdownStream(rtspClient);
}

void openURL(UsageEnvironment& env, char const* progName, char const* rtspURL) 
{
	// Begin by creating a "RTSPClient" object.  Note that there is a separate "RTSPClient" object for each stream that we wish
	// to receive (even if more than stream uses the same "rtsp://" URL).
	RTSPClient* rtspClient = ourRTSPClient::createNew(env, rtspURL, RTSP_CLIENT_VERBOSITY_LEVEL, progName);
	if (rtspClient == NULL)
	{
		env << "Failed to create a RTSP client for URL \"" << rtspURL << "\": " << env.getResultMsg() << "\n";
		return;
	}

	// Next, send a RTSP "DESCRIBE" command, to get a SDP description for the stream.
	// Note that this command - like all RTSP commands - is sent asynchronously; we do not block, waiting for a response.
	// Instead, the following function call returns immediately, and we handle the RTSP response later, from within the event loop:
	rtspClient->sendDescribeCommand(continueAfterDESCRIBE); 
}

// By default, we request that the server stream its data using RTP/UDP.
// If, instead, you want to request that the server stream via RTP-over-TCP, change the following to True:
#define REQUEST_STREAMING_OVER_TCP False

void setupNextSubsession(RTSPClient* rtspClient) 
{
	UsageEnvironment& env = rtspClient->envir(); // alias
	StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias
  
	scs.subsession = scs.iter->next();
	if (scs.subsession != NULL) 
	{
		if (!scs.subsession->initiate()) 
		{
			env << *rtspClient << "Failed to initiate the \"" << *scs.subsession << "\" subsession: " << env.getResultMsg() << "\n";
			setupNextSubsession(rtspClient); // give up on this subsession; go to the next one
		} 
		else 
		{
			env << *rtspClient << "Initiated the \"" << *scs.subsession << "\" subsession (";
			if (scs.subsession->rtcpIsMuxed()) 
			{
				env << "client port " << scs.subsession->clientPortNum();
			} 
			else
			{
				env << "client ports " << scs.subsession->clientPortNum() << "-" << scs.subsession->clientPortNum()+1;
			}
			env << ")\n";

			if (scs.subsession->rtpSource() != NULL) 
			{
				// Because we're saving the incoming data, rather than playing
				// it in real time, allow an especially large time threshold
				// (1 second) for reordering misordered incoming packets:
				/**
				*	减小时间
				**/
				/*
				unsigned const thresh = 100000; // 1 second
				*/
				unsigned const thresh = 10;
				scs.subsession->rtpSource()->setPacketReorderingThresholdTime(thresh);

				// Set the RTP source's OS socket buffer size as appropriate - either if we were explicitly asked (using -B),
				// or if the desired FileSink buffer size happens to be larger than the current OS socket buffer size.
				// (The latter case is a heuristic, on the assumption that if the user asked for a large FileSink buffer size,
				// then the input data rate may be large enough to justify increasing the OS socket buffer size also.)
				int socketNum = scs.subsession->rtpSource()->RTPgs()->socketNum();
				unsigned curBufferSize = getReceiveBufferSize(env, socketNum);
				unsigned int fileSinkBufferSize = 20000000;
				if ( fileSinkBufferSize > curBufferSize) 
				{
					unsigned newBufferSize =  fileSinkBufferSize;
					newBufferSize = setReceiveBufferTo(env, socketNum, newBufferSize);
					printf("actual buffer size = %d\n", newBufferSize);
				}
			}
			// Continue setting up this subsession, by sending a RTSP "SETUP" command:
			rtspClient->sendSetupCommand(*scs.subsession, continueAfterSETUP, False, REQUEST_STREAMING_OVER_TCP);
		}
		return;
	}

	// We've finished setting up all of the subsessions.  Now, send a RTSP "PLAY" command to start the streaming:
	if (scs.session->absStartTime() != NULL) 
	{
		// Special case: The stream is indexed by 'absolute' time, so send an appropriate "PLAY" command:
		rtspClient->sendPlayCommand(*scs.session, continueAfterPLAY, scs.session->absStartTime(), scs.session->absEndTime());
	} 
	else 
	{
		scs.duration = scs.session->playEndTime() - scs.session->playStartTime();
		rtspClient->sendPlayCommand(*scs.session, continueAfterPLAY);
	}
}

void shutdownStream(RTSPClient* rtspClient, int exitCode)
{
	UsageEnvironment& env = rtspClient->envir(); // alias
	StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias

	// First, check whether any subsessions have still to be closed:
	if (scs.session != NULL)
	{ 
		Boolean someSubsessionsWereActive = False;
		MediaSubsessionIterator iter(*scs.session);
		MediaSubsession* subsession;

		while ((subsession = iter.next()) != NULL)
		{
			if (subsession->sink != NULL)
			{
				Medium::close(subsession->sink);
				subsession->sink = NULL;
				if(subsession->rtcpInstance() != NULL)
				{
					subsession->rtcpInstance()->setByeHandler(NULL, NULL); // in case the server sends a RTCP "BYE" while handling "TEARDOWN"
				}
				
				someSubsessionsWereActive = True;
			}
		}

		if (someSubsessionsWereActive)
		{
			// Send a RTSP "TEARDOWN" command, to tell the server to shutdown the stream.
			// Don't bother handling the response to the "TEARDOWN".
			rtspClient->sendTeardownCommand(*scs.session, NULL);
		}
	}

	env << *rtspClient << "Closing the stream.\n";
	Medium::close(rtspClient);
    // Note that this will also cause this stream's "StreamClientState" structure to get reclaimed.
    // The final stream has ended, so exit the application now.
    // (Of course, if you're embedding this code into your own application, you might want to comment this out,
    // and replace it with "eventLoopWatchVariable = 1;", so that we leave the LIVE555 event loop, and continue running "main()".)
	/*MessageBox(NULL, _T("播放结束"), _T("提示"), MB_OK);*/
	SendMsg.wParam = WPARAM_CLOSE;
	SendMessageToSmartPlayer(SmartPlayer, SendMsg);
	
	exit(exitCode);

	// eventLoopWatchVariable = STOP_EVENT_LOOP;
}

// A function that outputs a string that identifies each stream (for debugging output).  Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const RTSPClient& rtspClient)
{
	return env << "[URL:\"" << rtspClient.url() << "\"]: ";
}

// A function that outputs a string that identifies each subsession (for debugging output).  Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const MediaSubsession& subsession)
{
	return env << subsession.mediumName() << "/" << subsession.codecName();
}

void usage(UsageEnvironment& env, char const* progName) 
{
	env << "Usage: " << progName << " <rtsp-url-1> ... <rtsp-url-N>\n";
	env << "\t(where each <rtsp-url-i> is a \"rtsp://\" URL)\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///		对视频数据进行解码,播放所需要的一些函数的实现
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool ffmpeg_init()
{
	av_register_all();
	 /* find the decoder */
    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec)
		return false;

    c = avcodec_alloc_context3(codec);

    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0) 
		return false;

	return true;
}

void packet_queue_init(PacketQueue *q) 
{
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
}

int packet_queue_put(PacketQueue *q, AVPacket *pkt)
{
    
    AVPacketList *pkt1;
    if(av_dup_packet(pkt) < 0)
	{
        return -1;
    }
    pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if (!pkt1)
        return -1;
    pkt1->pkt = *pkt;
    pkt1->next = NULL;
    
    
    SDL_LockMutex(q->mutex);
    
    if (!q->last_pkt)
        q->first_pkt = pkt1;
    else
        q->last_pkt->next = pkt1;
    q->last_pkt = pkt1;
    q->nb_packets++;
    q->size += pkt1->pkt.size;
    SDL_CondSignal(q->cond);
    
    SDL_UnlockMutex(q->mutex);
    return 0;
}

static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
    AVPacketList *pkt1;
    int ret;
    
    SDL_LockMutex(q->mutex);
    
    for(;;) 
	{
        pkt1 = q->first_pkt;
        if (pkt1) 
		{
            q->first_pkt = pkt1->next;
            if (!q->first_pkt)
                q->last_pkt = NULL;
            q->nb_packets--;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;
            av_free(pkt1);
            ret = 1;
            break;
        }
		else if (!block)
		{
            ret = 0;
            break;
        }
		else
		{
            SDL_CondWait(q->cond, q->mutex);
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}

void packet_queue_flush(PacketQueue *q) 
{
	AVPacketList *pkt, *pkt1;

	SDL_LockMutex(q->mutex);
	for(pkt = q->first_pkt; pkt != NULL; pkt = pkt1) 
	{
		pkt1 = pkt->next;
		av_free_packet(&pkt->pkt);
		av_freep(&pkt);
	}
	q->last_pkt = NULL;
	q->first_pkt = NULL;
	q->nb_packets = 0;
	q->size = 0;
	SDL_UnlockMutex(q->mutex);
}

void packet_queue_destroy(PacketQueue *q)
{
	packet_queue_flush(q);
	SDL_DestroyMutex(q->mutex);
	SDL_DestroyCond(q->cond);
}
