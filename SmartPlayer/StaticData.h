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

// �Զ���windows��Ϣ
#define	WM_SOCKET			(WM_USER + 30)
#define WM_PLAYER			(WM_USER + 31)
#define WM_CONTROL			(WM_USER + 32)
#define WM_RTSP				(WM_USER + 33)
#define WM_RECT				(WM_USER + 34)		// ���͸�RTSP����,����Ϊ��������߿�

const int WPARAM_RECT		= 0;	// RTSP���̽��յ�����
const int WPARAM_START		= 1;	// SmartControl ����
const int WPARAM_CLOSE		= 2;	// SmartControl �ر�
const int WPARAM_STOP		= 3;	// ������ֹͣ���� �� �������˳�

const int WPARAM_PLAYING	= 4;	// RtspPlayer����������Ϣ,��ʾ��ʼ����
const int WPARAM_PAUSE		= 5;	// ��ͣ����

// ��������
const int BUFFER_SIZE		= 128;			// url��ַ��󳤶�

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
	NOTHING = 0,	// ��ʼ����ϣ����߲��Ž����Ժ�
	PLAYING,		// ���ڲ���
	WAITING,		// �ȴ����Ž�����Ӧ
	PAUSE,			// ��ǰ������ͣ״̬
};