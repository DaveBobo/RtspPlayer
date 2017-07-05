
#ifndef		_T15COMMON_H
#define		_T15COMMON_H


// ���������ʽ
#define	OUT_FMT_YUV_420	 0x00000601
#define OUT_FMT_YUV_422  0x00000102
#define OUT_FMT_RGB_032  0x00000204
#define OUT_FMT_RGB_024  0x00000303
#define OUT_FMT_RGB_565  0x00000402
#define OUT_FMT_RGB_555  0x00000502

#define	OUT_FMT_AUDIO	 0x00000602

#define		ERR_NO_ERROR					0	// �ɹ�
#define		ERR_MEMORY_ALLOC_ERROR			1	// �ڴ����ʧ��
#define		ERR_PARAM_INVALID_ERROR			2	// ������Ч
#define		ERR_OPEN_DDRAW_ERROR			3	// �Կ���ʼ��ʧ��
#define		ERR_OPEN_DSOUND_ERROR			4	// ��Ƶ��ʼ��ʧ��
#define		ERR_GETFILEINFO_ERROR			5	// ��ȡ�ļ���Ϣʧ��
#define		ERR_DECINIT_ERROR				6	// ��������ʼ��ʧ��
#define		ERR_INIT_DDRAW_ERROR			7	// �Կ���ʼ��ʧ��
#define		ERR_IFRAME_NOT_FOUND_ERROR		8	// ����IFrameʧ��
#define		ERR_OPENFILE_ERROR				9	// ���ļ�ʧ��
#define		ERR_OPEN_ALOW_ERROR				10	// ��ALaw��Ƶʧ��
#define		ERR_FILE_HEADER_ERROR			11  // ��Ч���ļ�ͷ
#define		ERR_DECODER_TYPE_ERROR			12	// �ļ�/��ģʽ�����Ѿ���:�л�����ʱ
#define		ERR_DEC_OPENED_ERROR			13	// �������Ѿ���
#define		ERR_DEC_BUSY_ERROR				14	// ������æ
#define		ERR_FILE_KEYFRAME				15	// û�йؼ�֡
#define		ERR_FRAME_HEAD_ERROR			16	// ֡ͷ����

#define		PLAYING_FILE				0
#define		PLAYING_STREAM				1

#define		STREAM_OPEN_REALTIME		0
#define		STREAM_OPEN_FILE			1




// T15_SetMsgWnd
/*
	lParam�а���ͨ����
*/
#define MSG_FILE_END_NOTIFICATION		(WM_USER+151)	// �ļ�������ɷ���
#define MSG_BUFFER_NOTIFICATION			(WM_USER+152)	// Դ��������ֵ��ʣ������С�ڵ��ڷ�ֵʱ���� wParam: 1
#define	MSG_EXCEPTION_ERROR				(WM_USER+152)	// �쳣����									wParam: 0
#define	MSG_INDEX_OK					(WM_USER+154)	// �����̴߳�������

#define BY_FRAMENUM				1	//��ʾ֡��
#define BY_FRAMTIME				2	//��ʾʱ�䣬��λms

typedef struct{
	long nFilePos;		//�ļ�λ�ã�
	long nFrameNum;		//֡��ţ�
	long nFrameTime;	//֡ʱ�꣨ms��;
}FRAME_POS,*PFRAME_POS;


typedef struct{
	long nWidth;	//�������λ���ء��������Ƶ������Ϊ0��
	long nHeight;	//����ߡ��������Ƶ������Ϊ��
	long nStamp;	//ʱ����Ϣ����λ���롣
	long nType;		//	 
	long nFrameRate;//����ʱ������ͼ��֡�ʡ�
}FRAME_INFO;

typedef	struct{
	WORD	wYear;
	WORD	wMonth;
	WORD	wWeek;
	WORD	wDay;
	WORD	wHour;
	WORD	wMinute;
	WORD	wSecond;
	WORD	wMilli;
}_SYSTEM_TIME;

typedef	struct {
		short	year;
		short	month;
		short	day;
		short	hour;
		short	minute;
		short	second;
		short	milli;	
		short	week;
}VIDEO_TIME;
typedef struct 
{
	char YinheID[8];	// :'YINHEBMW'
	DWORD HeadSize;		// :64
	char HeadID[4];		// :0x2008("MP4 ")
	DWORD framerate;	// :n (1/n)
	DWORD VideoStandard;// :0 ntsc;1 pal
	DWORD VideoWidth;	// :
	DWORD VideoHeight;	// :
	DWORD AudioType;	// 0: ����Ƶ, 1: G.729 8k, 2: a-law, 3: g.729a , 4: g.722
	char  reserved[28]; // 1. byte i-frame interval
}HB_FILE_HEAD;

// �ļ�¼��ʱ��
typedef	struct{
	WORD	wYear;
	WORD	wMonth;
	WORD	wWeek;
	WORD	wDay;
	WORD	wHour;
	WORD	wMinute;
	WORD	wSecond;
	WORD	wMilli;

}_RECORD_TIME;






































#endif