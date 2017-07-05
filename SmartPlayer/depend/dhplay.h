    /********************************************************************
 * �ļ�: dhplay.h
 * ��Ȩ:
 * ����: �ܹ���, ������
 * ����: 2006.12
	purpose:	�����ṩ���û������ο����ṩ�����ӿڵĶ����˵��
*********************************************************************/
#ifndef _DHPLAY_H
#define _DHPLAY_H

#define PLAYSDK_API  __declspec(dllexport)

#define CALLMETHOD __stdcall
#define CALLBACK __stdcall

#define  FUNC_MAX_PORT 101              //��󲥷�ͨ����
//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100
//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 
//��������
#define BUF_VIDEO_SRC 1    //��ƵԴ����        
#define BUF_AUDIO_SRC 2    //��ƵԴ����
#define BUF_VIDEO_RENDER 3  //�������Ƶ���ݻ���
#define BUF_AUDIO_RENDER 4  //�������Ƶ���ݻ���

//��������
#define	DH_PLAY_NOERROR					0              //û�д���
#define DH_PLAY_PARA_OVER				1              //��������Ƿ���
#define DH_PLAY_ORDER_ERROR				2              //����˳�򲻶ԣ�
#define DH_PLAY_TIMER_ERROR				3              //��ý��ʱ������ʧ�ܣ�
#define DH_PLAY_DEC_VIDEO_ERROR			4	           //��Ƶ����ʧ�ܣ�
#define DH_PLAY_DEC_AUDIO_ERROR			5	           //��Ƶ����ʧ�ܣ�
#define DH_PLAY_ALLOC_MEMORY_ERROR		6		       //�����ڴ�ʧ�ܣ�
#define DH_PLAY_OPEN_FILE_ERROR			7			   //�ļ�����ʧ�ܣ�
#define DH_PLAY_CREATE_OBJ_ERROR		8	           //�����߳��¼���ʧ�ܣ�
#define DH_PLAY_CREATE_DDRAW_ERROR		9		       //����directDrawʧ�ܣ�
#define DH_PLAY_CREATE_OFFSCREEN_ERROR	10		       //������˻���ʧ�ܣ�
#define DH_PLAY_BUF_OVER				11	           //����������������ʧ�ܣ�
#define DH_PLAY_CREATE_SOUND_ERROR		12		       //������Ƶ�豸ʧ�ܣ�
#define DH_PLAY_SET_VOLUME_ERROR		13	           //��������ʧ�ܣ�
#define DH_PLAY_SUPPORT_FILE_ONLY		14		       //ֻ���ڲ����ļ�ʱ����ʹ�ô˽ӿڣ�
#define DH_PLAY_SUPPORT_STREAM_ONLY		15		       //ֻ���ڲ�����ʱ����ʹ�ô˽ӿڣ�
#define DH_PLAY_SYS_NOT_SUPPORT			16		       //ϵͳ��֧�֣�������ֻ�ܹ�����Pentium 3���ϣ�
#define DH_PLAY_FILEHEADER_UNKNOWN		17		       //û���ļ�ͷ��
#define DH_PLAY_VERSION_INCORRECT		18	           //�������ͱ������汾����Ӧ��
#define DH_PLAY_INIT_DECODER_ERROR		19		       //��ʼ��������ʧ�ܣ�
#define DH_PLAY_CHECK_FILE_ERROR		20		       //�ļ�̫�̻������޷�ʶ��
#define DH_PLAY_INIT_TIMER_ERROR		21		       //��ʼ����ý��ʱ��ʧ�ܣ�
#define DH_PLAY_BLT_ERROR				22		       //λ����ʧ�ܣ�
#define DH_PLAY_UPDATE_ERROR            23			   //��ʾoverlayʧ�ܣ�


//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2	

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 6

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100

#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//ϵͳ֧�ֵĹ��ܣ����ڰ�λ��ʾϵͳ����
#define SUPPORT_DDRAW		1  //֧��DIRECTDRAW�������֧�֣��򲥷������ܹ�����
#define SUPPORT_BLT         2  //�Կ�֧��BLT�����������֧�֣��򲥷������ܹ���
#define SUPPORT_BLTFOURCC   4  //�Կ�BLT֧����ɫת����
#define SUPPORT_BLTSHRINKX  8  //�Կ�BLT֧��X����С��
#define SUPPORT_BLTSHRINKY  16 //�Կ�BLT֧��Y����С��
#define SUPPORT_BLTSTRETCHX 32 //�Կ�BLT֧��X��Ŵ�
#define SUPPORT_BLTSTRETCHY 64 //�Կ�BLT֧��Y��Ŵ�
#define SUPPORT_SSE         128 //CPU֧��SSEָ��,Intel Pentium3����֧��SSEָ�
#define SUPPORT_MMX			256 //CPU֧��MMXָ���

//Frame position
typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct{
	long nWidth;  //�������λ���ء��������Ƶ������Ϊ0��
	long nHeight; //����ߡ��������Ƶ������Ϊ0��
	long nStamp;  //ʱ����Ϣ����λ���롣
	long nType;   //�������ͣ�T_AUDIO16��T_RGB32�� T_YV12������궨��˵����
	long nFrameRate; //����ʱ������ͼ��֡�ʡ�
}FRAME_INFO;

typedef struct 
{
	char *pDataBuf;
	long nSize;
	long nFrameNum;
	BOOL bIsAudio;
	long nReserved;
}FRAME_TYPE;

//����Ϊ����ӿڣ����û������ο�������
//���������ǿ��Բ���Ҫ���õĽӿ�
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDraw(HWND hWnd);

PLAYSDK_API BOOL CALLMETHOD PLAY_RealeseDDraw();

PLAYSDK_API BOOL CALLMETHOD PLAY_OpenFile(LONG nPort,LPSTR sFileName);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseFile(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Play(LONG nPort, HWND hWnd);
PLAYSDK_API BOOL CALLMETHOD PLAY_Stop(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Pause(LONG nPort,DWORD nPause);
PLAYSDK_API BOOL CALLMETHOD PLAY_Fast(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Slow(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOne(LONG nPort);//����طŵ�֡
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPos(LONG nPort,float fRelativePos);
PLAYSDK_API float CALLMETHOD PLAY_GetPlayPos(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVolume(LONG nPort,WORD nVolume);
PLAYSDK_API BOOL CALLMETHOD PLAY_StopSound();
PLAYSDK_API BOOL CALLMETHOD PLAY_PlaySound(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStream(LONG nPort);
PLAYSDK_API int  CALLMETHOD PLAY_GetCaps();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTime(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTime(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedFrames(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Back(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_BackOne(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved), long nUser = 0);
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTotalFrames(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameRate(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTimeEx(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameNum(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileHeadLength();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSdkVersion();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetLastError(LONG nPort);
PLAYSDK_API BOOL  CALLMETHOD PLAY_RefreshPlay(LONG nPort);
PLAYSDK_API BOOL  CALLMETHOD PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
PLAYSDK_API BOOL  CALLMETHOD PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
PLAYSDK_API BOOL  CALLMETHOD PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);
PLAYSDK_API BOOL  CALLMETHOD PLAY_PlaySoundShare(LONG nPort);
PLAYSDK_API BOOL  CALLMETHOD PLAY_StopSoundShare(LONG nPort);
PLAYSDK_API LONG CALLMETHOD PLAY_GetStreamOpenMode(LONG nPort);
PLAYSDK_API LONG CALLMETHOD PLAY_GetOverlayMode(LONG nPort);
PLAYSDK_API COLORREF CALLMETHOD PLAY_GetColorKey(LONG nPort);
PLAYSDK_API WORD CALLMETHOD PLAY_GetVolume(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSourceBufferRemain(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBuffer(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,void (CALLBACK * SourceBuf__stdcall)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBufFlag(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDisplayBuf(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOneBack(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileRefCallBack(LONG nPort, void (CALLBACK *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDrawDevice();
PLAYSDK_API void CALLMETHOD PLAY_ReleaseDDrawDevice();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDDrawDeviceTotalNums();
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

PLAYSDK_API BOOL CALLMETHOD PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,long *hhMonitor);
PLAYSDK_API int   CALLMETHOD PLAY_GetCapsEx(DWORD nDDrawDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayType(LONG nPort,LONG nType);
PLAYSDK_API long CALLMETHOD PLAY_GetDisplayType(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCBStream(LONG nPort,DWORD nStream);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStreamEx(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_RigisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetBuffer(LONG nPort,DWORD nBufType);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (CALLBACK * funVerify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser),  DWORD  nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioCallBack(LONG nPort, void (CALLBACK * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncTypeChangeCallBack(LONG nPort,void(CALLBACK *funEncChange)(long nPort, long nUser),long nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDRange(LONG nPort,RECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold) ;
PLAYSDK_API DWORD CALLMETHOD PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue) ;

PLAYSDK_API BOOL CALLMETHOD PLAY_CatchPic(LONG nPort,char* sFileName) ;

PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndCallBack(LONG nPort, void (CALLBACK *pFileEnd)(DWORD nPort,DWORD nUser),DWORD nUser);
//dataType 0 ��ԭʼ������ 1��AVI
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecord(LONG nPort, char *sFileName, int idataType=0);
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDataRecord(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustFluency(LONG nPort, int level);
PLAYSDK_API BOOL CALLMETHOD PLAY_ChangeRate(LONG nPort, int rate);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDemuxCallBack(LONG nPort, void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,void * pParam, long nReserved,long nUser), long nUser);
#define PLAY_CMD_GetTime 1
#define PLAY_CMD_GetFileRate 2
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryInfo(LONG nPort , int cmdType, char* buf, int buflen, int* returnlen);

typedef void (WINAPI *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, long nUser);

PLAYSDK_API BOOL CALLMETHOD PLAY_OpenAudioRecord(pCallFunction pProc, long nBitsPerSample, long nSamplesPerSec, long nLength, long nReserved, long nUser);

PLAYSDK_API BOOL CALLMETHOD PLAY_CloseAudioRecord();

//reserved 0 ��I֡֡����ˮӡ��Ϣ 1 ��֡ˮӡ 2 ��ˮӡУ�� 3�����ܷ���֡
typedef int (__stdcall* GetWaterMarkInfoCallbackFunc)(char* buf, long key, long len, long reallen, long reserved, long nUser);	//ˮӡ��Ϣ��ȡ����

PLAYSDK_API BOOL CALLMETHOD PLAY_SetWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, long nUser);

PLAYSDK_API DWORD CALLMETHOD PLAY_CreateFile(LPSTR sFileName);
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyFile(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_CreateStream(DWORD nBufPoolSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyStream(LONG nPort);

#endif
