/****************************************************** 
		�ļ���:		StaticData.h �����ļ�

		�༭����:	Microsoft Visual Studio 2010

		����:		UESTC-PRMI

		����ʱ��:	2014-10-18

		�޸���:		
		
		�޸�ʱ��:

		��Ҫ����:	����һЩȫ�ֲ��䲢���õĽṹ��,��
					��,ö�ٵ�
******************************************************/ 
#pragma once

/** ��ӡ���ÿһ֡���ݵ�log.pref���������Ҫ��ע������һ�� */
//#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

/** ������յ���H264��Ƶ���ݵ�Recieved.264���������Ҫ��ע������һ�� */
//#define SAVE_THE_STREAM_INTO_FILE 1

// �Զ���windows��Ϣ
#define	WM_SOCKET			(WM_USER + 30)
#define WM_PLAYER			(WM_USER + 31)
#define WM_CONTROL			(WM_USER + 32)
#define WM_RTSP				(WM_USER + 33)
#define WM_RECT				(WM_USER + 34)		// ���͸�RTSP����,����Ϊ��������߿�	

const int WPARAM_RECT		= 0;	// RTSP���̽��յ�����
const int WPARAM_START		= 1;	// ����
const int WPARAM_CLOSE		= 2;	// �ر�
const int WPARAM_STOP		= 3;	// ������ֹͣ���� �� �������˳� �����ò���,������������

const int WPARAM_PLAYING	= 4;	// RtspPlayer����������Ϣ,��ʾ��ʼ����
const int WPARAM_PAUSE		= 5;	// ��ͣ����

// ��������
const int BUFFER_SIZE		= 128;			// url��ַ��󳤶�
const int CONTROL_PORT		= 8088;			// �ش�����ʱ�Ķ˿�
const int UDP_PORT			= 8087;			// ��������Android�ֻ�ͨ�Ŷ˿�
const int COMMAND_SIZE		= 1;			// ���͸�Զ���ֻ�ָ��(ͷ)�Ĵ�С
const int START_EVENT_LOOP	= 0;			// 0,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)����һֱѭ����ȥ
const int STOP_EVENT_LOOP	= 1;			// ����,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)�����˳�ѭ��
const int START_CODE_SIZE	= 4;			// {0x00, 0x00, 0x00, 0x01}		4λ��ʼ��
const int HAVE_ACCESSED_POSITION = 1;		// �Ѿ���ø����ؼ��ĳ�ʼλ��
const int RTSP_CLIENT_VERBOSITY_LEVEL = 1;	// by default, print verbose output from each "RTSPClient"
const int NALU_BUFFER_SIZE	= 1024 * 1024;

const char PLAYER_NAME[]	= "Smart Player";
const char CONTROL_NAME[]	= "Smart Control";

const char LOGFILE[]		= _T(".\\DATA\\log.pref");
const char URLFILE[]		= _T(".\\DATA\\url.pref");
const char VIDEOFILE[]		= _T(".\\DATA\\Recieved.264");

const char FOLDERPATH[]		= _T(".\\DATA");
#ifdef DEBUG
const char SMARTCTRLPATH[]	= _T("..\\Debug\\SmartControl.exe");
#endif

#ifndef DEBUG
const char SMARTCTRLPATH[]	= _T("SmartControl.exe");
#endif


// ��̬��������
static bool fHaveWrittenFirstFrame = false;		// ���յ���һ֡ʱ,��Ҫ����Ƶ���ݵ�SPS,PPS���в���.false,��ʾ��δ���в���;true,��ʾ�Ѿ������˲���

typedef struct PacketQueue
{
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;
