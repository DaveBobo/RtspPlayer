/****************************************************** 
		文件名:		StaticData.h 声明文件

		编辑工具:	Microsoft Visual Studio 2010

		作者:		UESTC-PRMI

		创建时间:	2014-10-18

		修改者:		
		
		修改时间:

		主要内容:	声明一些全局不变并常用的结构体,常
					量,枚举等
******************************************************/ 
#pragma once

// 自定义windows消息
#define	WM_SOCKET			(WM_USER + 30)
#define WM_PLAYER			(WM_USER + 31)
#define WM_CONTROL			(WM_USER + 32)
#define WM_RTSP				(WM_USER + 33)
#define WM_RECT				(WM_USER + 34)		// 发送给RTSP进程,参数为播放区域高宽

const int WPARAM_RECT		= 0;	// RTSP进程接收到长宽
const int WPARAM_START		= 1;	// SmartControl 启动
const int WPARAM_CLOSE		= 2;	// SmartControl 关闭
const int WPARAM_STOP		= 3;	// 播放器停止播放 或 播放器退出

const int WPARAM_PLAYING	= 4;	// RtspPlayer发送来的消息,表示开始播放
const int WPARAM_PAUSE		= 5;	// 暂停参数

// 常量定义
const int BUFFER_SIZE		= 128;			// url地址最大长度

const char PLAYER_NAME[]	= _T("Smart Player");
const char CONTROL_NAME[]	= _T("Smart Control");

const char URLFILE[]		= _T(".\\DATA\\url.pref");
const char FOLDERPATH[]		= _T(".\\DATA");

#ifdef DEBUG
const char SMARTCTRLPATH[]	= _T("..\\Debug\\SmartControl.exe");
const char RTSPPLAYERPATH[] = _T("..\\Debug\\RtspPlayer.exe");
#else
const char SMARTCTRLPATH[]	= _T("SmartControl.exe");
const char RTSPPLAYERPATH[] = _T("RtspPlayer.exe");
#endif

enum PlayerStatus
{
	NOTHING = 0,	// 初始化完毕，或者播放结束以后
	PLAYING,		// 正在播放
	WAITING,		// 等待播放进程响应
	PAUSE,			// 当前处于暂停状态
};