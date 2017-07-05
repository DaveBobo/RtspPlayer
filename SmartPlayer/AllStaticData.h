#pragma once

/** ��ӡ���ÿһ֡���ݵ�log.pref���������Ҫ��ע������һ�� */
//#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

/** ������յ���H264��Ƶ���ݵ�Recieved.264���������Ҫ��ע������һ�� */
//#define SAVE_THE_STREAM_INTO_FILE 1

// �Զ���windows��Ϣ
// ��Ϣ��ʹ�ã������ñ�ʶ��Ϣ + ���� ����ʽ
#define	WM_SOCKET			(WM_USER + 30)		// SmartControl�н���SmartControlWiFi����ʱʹ�õ���Ϣ
#define WM_PLAYER			(WM_USER + 31)		// SmartPlayer���͸��������̵ı�ʶ��Ϣ
#define WM_CONTROL			(WM_USER + 32)		// SmartControl���͸��������̵ı�ʶ��Ϣ
#define WM_RTSP				(WM_USER + 33)		// RtspPlayer���͸��������̵ı�ʶ��Ϣ
#define WM_RECT				(WM_USER + 34)		// ���͸�RTSP����,����Ϊ��������߿�
// ��ʶ��Ϣ��Я������������
const int WPARAM_RECT		= 0;	// RTSP���̽��յ�����
const int WPARAM_START		= 1;	// SmartControl ����
const int WPARAM_CLOSE		= 2;	// SmartControl �ر�
const int WPARAM_STOP		= 3;	// ������ֹͣ���� �� �������˳�

const int WPARAM_PLAYING	= 4;	// RtspPlayer����������Ϣ,��ʾ��ʼ����
const int WPARAM_PAUSE		= 5;	// ��ͣ����

// ��������
const int CONTROL_PORT		= 8088;			// �ش�����ʱ�Ķ˿�
const int UDP_PORT			= 8087;			// ��������Android�ֻ�ͨ�Ŷ˿�
const int COMMAND_SIZE		= 1;			// ���͸�Զ���ֻ�ָ��(ͷ)�Ĵ�С
const int BUFFER_SIZE		= 128;			// url��ַ��󳤶�
const int EVENT_RISE		= 1;
const int EVENT_DROP		= 2;
const int EVENT_LFTTRN		= 3;
const int EVENT_RGTTRN		= 4;
const int EVENT_ANTICLK		= 5;
const int EVENT_WISECLK		= 6;

const int START_EVENT_LOOP	= 0;			// 0,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)����һֱѭ����ȥ
const int STOP_EVENT_LOOP	= 1;			// ����,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)�����˳�ѭ��
const int START_CODE_SIZE	= 4;			// {0x00, 0x00, 0x00, 0x01}		4λ��ʼ��
const int HAVE_ACCESSED_POSITION = 1;		// �Ѿ���ø����ؼ��ĳ�ʼλ��
const int RTSP_CLIENT_VERBOSITY_LEVEL = 1;	// by default, print verbose output from each "RTSPClient"
const int NALU_BUFFER_SIZE	= 1024 * 1024;

// ���²���Ϊ��������̨�ƶ�ʱ��������ʱ������ͣ�ĸ�Spydroid��������
const int TIME_SPAN			= 30;			// ��ʱ�����ʱ��
// ����������ȡ��,ʹ��20,40�̶���������
const int TURN_STOP			= 30;			// �Դ�ֹͣ����
const int COMMAND_LEFT		= 20;			// ��̨����������µĲ���
const int COMMAND_RIGHT		= 40;			// ��̨���һ������ϵĲ���
// ���յ���һ֡ʱ,��Ҫ����Ƶ���ݵ�SPS,PPS���в���.false,��ʾ��δ���в���;true,��ʾ�Ѿ������˲���
static bool fHaveWrittenFirstFrame = false;	
// ��IP��ַ,��ʱ����δ�趨android��IP��ַ
const char NULL_ADDR[]	= "0.0.0.0";
// SmartPlayer��������
const char PLAYER_NAME[]	= _T("Smart Player");
// SmartControl��������
const char CONTROL_NAME[]	= _T("Smart Control");
// �����ļ������ļ���·������
const char FOLDERPATH[]		= _T(".\\DATA");
const char RANDGEFILE[]		= _T(".\\DATA\\SliderRange.pref");
const char VIDEOFILE[]		= _T(".\\DATA\\Recieved.264");
const char URLFILE[]		= _T(".\\DATA\\url.pref");

// SmartControl �� RtspPlayer��������·��
#ifdef DEBUG
const char SMARTCTRLPATH[]	= _T("..\\Debug\\SmartControl.exe");
const char RTSPPLAYERPATH[] = _T("..\\Debug\\RtspPlayer.exe");
#else
const char SMARTCTRLPATH[]	= _T("SmartControl.exe");
const char RTSPPLAYERPATH[] = _T("RtspPlayer.exe");
#endif

// SmartPlayer�ļ�ʹ�õ�״̬ö��
enum PlayerStatus
{
	NOTHING = 0,	// ��ʼ����ϣ����߲��Ž����Ժ�
	PLAYING,		// ���ڲ���
	WAITING,		// �ȴ����Ž�����Ӧ
	PAUSE,			// ��ǰ������ͣ״̬
};

// ��ͬ������ͨѶ״̬�������� (һ�����һ����,���ݾ�ֻ�������е�һ��Ԫ��)
const char StatusArray[] = {'A', 'C', 'S', 'D', 'Q', 'J', 'O', 'N'};
enum Stu_Type
{
	ACCEPT = 0,
	CONNECT,
	STOP,
	DISCONNECT,
	REQ_UPDATE,
	REJ_UPDATE,
	OK_UPDATE,
	NO_UPDATE,
};

// ��ʻ������������
const char CommandArray[] = {'w', 'e', 'd', 'c', 'x', 'z', 'a', 'q', 's', 'r', 'f', 'v', 't', 'g'};
enum Command_Type
{
	CT_UP= 0,
	CT_RUP,
	CT_RIGHT,
	CT_RDOWN,
	CT_DOWN,
	CT_LDOWN,
	CT_LEFT,
	CT_LUP,
	CT_STOP,
	CT_RESET,
//	ǰ10��Ԫ��,�ֱ��Ӧ�˷���ֹͣ�͸�λ������.e.g.���ܵ�CommandArray[CT_LUP]�ʹ���I
	CT_LIFT,
	CT_HOLDLEFT,
	CT_HOLDUP,
	CT_TURN,
//	���ĸ�Ϊ�ĸ�Slider���������ͷ,һ����ܻ򷢳�������ӦΪ"f65",f����Lift������,65�������ֵ
};

// ���������ͣ������ã�
enum Slider_Type
{
	ST_LIFT = 0,
	ST_HOLDLEFT,
	ST_HOLDUP,
	ST_TURN,
};
// ������ֵ���ͣ������ã�
enum Slider_Value
{
	SV_MIN = 0,
	SV_MAX,
	SV_INIT,
};
// ���ڱ�����Ƶ���ݵĽṹ��
typedef struct PacketQueue
{
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;