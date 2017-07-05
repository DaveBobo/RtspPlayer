//megaplay.h
#ifndef __MEGAPLAY_H__
#define __MEGAPLAY_H__

#define ERROR_FILENOTFOUND   1L
#define ERROR_FILESIZE       2L
#define ERROR_FILEFORMAT     3L
#define ERROR_FILEVERSION    4L
#define ERROR_STARTPLAY      5L
#define ERROR_PLAYNOTINIT    6L
#define ERROR_NOTREALIZE     7L
#define ERROR_CHANNELERROR   8L
#define ERROR_OTHER          9L
#define ERROR_INVALIDPARAM   10L

#define MAX_DISPLAY_RECT_NUM 4      //�����ʾ����
#define MAX_DELAYFRAMENUM    500    //�����ӳ�֡��
#define MAX_BUFFFRAMENUM     500    //���Ļ���֡��
#define MIN_BUFFFRAMENUM     10     //��С�Ļ���֡��

enum
{
	PARAM_DELAYTIME     = 0,        //���û�ȡ�ӳ�֡��
	PARAM_BUFFNUM       = 1,        //���û�ȡ����֡��
	PARAM_CUR_BUFFNUM   = 2,        //��ȡ��ǰ����֡��
};

typedef struct
{
    unsigned int    timetick;       //ʱ��� (ms)
    unsigned int    nChannels;      //ͨ������
    unsigned int    nSamplesPerSec; //������
    unsigned int    wBitsPerSample; //����λ��
    const char      *pbuff;         //��Ƶ����buff
    int             size;           //��Ƶ���ݳ���
}AUDIO_FRAMEINFO;

typedef struct
{
    unsigned int    timetick;       //ʱ��� (ms)
    const char      *pY;            //YV12��ʽ,Y buff
    const char      *pU;            //U buff
    const char      *pV;            //V buff
    int             stridey;        //Y ���
    int             strideuv;       //UV ���
    int             width;          //ͼ����
    int             height;         //ͼ��߶�
}VIDEO_FRAMEINFO;

#define FRAMETYPE_VIDEO     1
#define FRAMETYPE_AUDIO     2

#define CPLAY_APIIMPORT  extern "C"__declspec(dllexport)
typedef long (__stdcall *MessageCallBack)(long lType,long lPara1,long lPara2);

CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Initial(long hWnd);
CPLAY_APIIMPORT	HRESULT __stdcall LCPLAYM4_Free();
CPLAY_APIIMPORT	HRESULT __stdcall LCPLAYM4_OpenFile(long hHandle,LPCTSTR sFileName);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_CloseFile(long hHandle);
CPLAY_APIIMPORT	HRESULT __stdcall LCPLAYM4_OpenStream(long hHandle,long *pFileHeadBuf,long lSize);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_CloseStream(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_InputData(long hHandle, long *pBuf, long lSize);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_PlaySound(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StopSound(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetVolume(long hHandle,long lVolume);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Play(long hHandle,long hWnd);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Stop(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Pause(long hHandle,long lPause);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_RefreshSurface(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetPlayPos(long hHandle,long lPos);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Fast(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Slow(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_CapPic(long hHandle,LPCTSTR sFileName);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetPlayPos(long hHandle,long *pPos);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetVersion(long *lVer);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_QueryFunction(LPCTSTR sFunctionName,long *lCanUse);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetParameter(long hHandle,long lType,long lPara1,long lPara2);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetParameter(long hHandle,long lType,long *pPara1,long *pPara2);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetCallBack(long hHandle,long (__stdcall *CallBack)(long lType,long lPara1,long lPara2));
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetFileEndMsgWnd(long hHandle,long hWnd,long lMsg);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StartASFFileCap(long hHandle,LPCTSTR sFileName,BOOL index = FALSE);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StopCapture(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StartMp4Capture(long hHandle, LPCTSTR sFileName);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StopMp4Capture(long hHandle);
CPLAY_APIIMPORT DWORD   __stdcall LCPLAYM4_GetFileTime(long hHandle);
CPLAY_APIIMPORT DWORD   __stdcall LCPLAYM4_GetPlayedTime(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetPlayedTime(long hHandle,DWORD nTime);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetDecodeCallBack(long hHandle,long( CALLBACK *DecodeCallBack)(long hHandle,long frametype,long *frameinfo,long lParam ),long lParam);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetDisplayRect(long hHandle,int num,RECT *rect,HWND hWnd,BOOL bEnable);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetVideoSize(long hHandle,DWORD *Width,DWORD *Height);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_OneByOne(long hHandle);
#endif
