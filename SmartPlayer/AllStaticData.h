#pragma once

/** 打印输出每一帧数据到log.pref，如果不需要，注释下面一行 */
//#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

/** 保存接收到的H264视频数据到Recieved.264，如果不需要，注释下面一行 */
//#define SAVE_THE_STREAM_INTO_FILE 1

// 自定义windows消息
// 消息的使用，均是用标识消息 + 参数 的形式
#define	WM_SOCKET			(WM_USER + 30)		// SmartControl中接收SmartControlWiFi连接时使用的消息
#define WM_PLAYER			(WM_USER + 31)		// SmartPlayer发送给其他进程的标识消息
#define WM_CONTROL			(WM_USER + 32)		// SmartControl发送给其他进程的标识消息
#define WM_RTSP				(WM_USER + 33)		// RtspPlayer发送给其他进程的标识消息
#define WM_RECT				(WM_USER + 34)		// 发送给RTSP进程,参数为播放区域高宽
// 标识消息所携带参数的意义
const int WPARAM_RECT		= 0;	// RTSP进程接收到长宽
const int WPARAM_START		= 1;	// SmartControl 启动
const int WPARAM_CLOSE		= 2;	// SmartControl 关闭
const int WPARAM_STOP		= 3;	// 播放器停止播放 或 播放器退出

const int WPARAM_PLAYING	= 4;	// RtspPlayer发送来的消息,表示开始播放
const int WPARAM_PAUSE		= 5;	// 暂停参数

// 常量定义
const int CONTROL_PORT		= 8088;			// 回传命令时的端口
const int UDP_PORT			= 8087;			// 局域网内Android手机通信端口
const int COMMAND_SIZE		= 1;			// 发送给远程手机指令(头)的大小
const int BUFFER_SIZE		= 128;			// url地址最大长度
const int EVENT_RISE		= 1;
const int EVENT_DROP		= 2;
const int EVENT_LFTTRN		= 3;
const int EVENT_RGTTRN		= 4;
const int EVENT_ANTICLK		= 5;
const int EVENT_WISECLK		= 6;

const int START_EVENT_LOOP	= 0;			// 0,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)函数一直循环下去
const int STOP_EVENT_LOOP	= 1;			// 非零,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)函数退出循环
const int START_CODE_SIZE	= 4;			// {0x00, 0x00, 0x00, 0x01}		4位起始码
const int HAVE_ACCESSED_POSITION = 1;		// 已经获得各个控件的初始位置
const int RTSP_CLIENT_VERBOSITY_LEVEL = 1;	// by default, print verbose output from each "RTSPClient"
const int NALU_BUFFER_SIZE	= 1024 * 1024;

// 以下参数为当控制云台移动时，启动定时器，不停的给Spydroid发送命令
const int TIME_SPAN			= 30;			// 定时器间隔时间
// 滑动块命令取消,使用20,40固定代表左右
const int TURN_STOP			= 30;			// 自传停止参数
const int COMMAND_LEFT		= 20;			// 云台向左或是向下的参数
const int COMMAND_RIGHT		= 40;			// 云台向右或是向上的参数
// 接收到第一帧时,需要对视频数据的SPS,PPS进行补偿.false,表示还未进行补偿;true,表示已经进行了补偿
static bool fHaveWrittenFirstFrame = false;	
// 空IP地址,此时代表未设定android端IP地址
const char NULL_ADDR[]	= "0.0.0.0";
// SmartPlayer窗口名称
const char PLAYER_NAME[]	= _T("Smart Player");
// SmartControl窗口名称
const char CONTROL_NAME[]	= _T("Smart Control");
// 本地文件或是文件夹路径常亮
const char FOLDERPATH[]		= _T(".\\DATA");
const char RANDGEFILE[]		= _T(".\\DATA\\SliderRange.pref");
const char VIDEOFILE[]		= _T(".\\DATA\\Recieved.264");
const char URLFILE[]		= _T(".\\DATA\\url.pref");

// SmartControl 和 RtspPlayer两个进程路径
#ifdef DEBUG
const char SMARTCTRLPATH[]	= _T("..\\Debug\\SmartControl.exe");
const char RTSPPLAYERPATH[] = _T("..\\Debug\\RtspPlayer.exe");
#else
const char SMARTCTRLPATH[]	= _T("SmartControl.exe");
const char RTSPPLAYERPATH[] = _T("RtspPlayer.exe");
#endif

// SmartPlayer文件使用的状态枚举
enum PlayerStatus
{
	NOTHING = 0,	// 初始化完毕，或者播放结束以后
	PLAYING,		// 正在播放
	WAITING,		// 等待播放进程响应
	PAUSE,			// 当前处于暂停状态
};

// 与同局域网通讯状态命令数组 (一个命令发一个包,数据就只有数组中的一个元素)
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

// 行驶按键命令数组
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
//	前10个元素,分别对应八方向、停止和复位的命令.e.g.接受到CommandArray[CT_LUP]就代表↖
	CT_LIFT,
	CT_HOLDLEFT,
	CT_HOLDUP,
	CT_TURN,
//	后四个为四个Slider命令的命令头,一般接受或发出的命令应为"f65",f代表Lift滑动块,65代表进度值
};

// 滑动块类型（已弃用）
enum Slider_Type
{
	ST_LIFT = 0,
	ST_HOLDLEFT,
	ST_HOLDUP,
	ST_TURN,
};
// 滑动块值类型（已弃用）
enum Slider_Value
{
	SV_MIN = 0,
	SV_MAX,
	SV_INIT,
};
// 用于保存视频数据的结构体
typedef struct PacketQueue
{
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;