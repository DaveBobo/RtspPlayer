

#if !defined (FHNRTVIDEO2_H_LLL)
#define FHNRTVIDEO2_H_LLL
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNRTVIDEO2_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNRTVIDEO2_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNRTVIDEO2_EXPORTS
#define FHNRTVIDEO2_API __declspec(dllexport)
#else
#define FHNRTVIDEO2_API __declspec(dllimport)
#endif

#include "fhncucommon.h"

#define rtv_success          0
#define rtv_sendmsg_error    10001
#define rtv_dest_nomedia     10002
#define rtv_dest_nosupport_media 10003
#define rtv_dest_no_mie       10004   /*���ص���Ϣȱ��IE*/


#define rtvnotify_startvideo_ok    1            /*����ʵʱ��Ƶ�ɹ�*/
#define rtvnotify_startvideo_error 2            /*����ʵʱ��Ƶ����ʧ�ܣ�V2.0����*/
#define rtvnotify_bye              3            /*ʵʱ��Ƶ�յ��Զ˵�bye*/

#define rtvnotify_askspeak_error 4              /*����Խ�ʧ�� V2.0����*/
#define rtvnotify_askspeak_ok    5              /*����Խ��ɹ�*/
#define rtvnotify_speak_bye      6              /*�Խ��ĶԶ�bye������*/

#define rtvnotify_startvideo_ms_error 7         /* ����ʵʱ��Ƶ���Զ�û�л�Ӧ200OK*/
#define rtvnotify_askspeak_ms_error    8        /* ����Խ����Զ�û�л�Ӧ200OK*/

#define rtvnotify_media_rtcp_bye       9       /*�յ�ý������rtcp bye�� �Զ�����bye��*/
#define rtvnotify_media_rtcp_unreceive 10      /*û���յ��Զ�ý���rtcp���� ���ܶԶ˷����쳣*/

#define rtvnotify_broadcast_ok      11         /*����㲥�ɹ�*/
#define rtvnotify_broadcast_list_error   12    /*����㲥���б�ʧ��*/
#define rtvnotify_broadcast_ms_error   13      /*�����㲥ý������ʧ��*/  
#define rtvnotify_broadcast_bye        14      /*�㲥�յ��Զ˵�bye*/


#define rtvnotify_speak_rtcp_bye       15
#define rtvnotify_speak_rtcp_unreceive 16


#define rtvnotify_broadcast_rtcp_bye    18
#define rtvnotify_broadcast_rtcp_unreceive 19

#define rtvnotify_broadcast_list_ok    20     /*����㲥���б�ɹ� */


#define rtvnotify_receive_invite       21  /*�յ�invite���� reserved is a point to fhnrtv2_invite_info*/
#define rtvnotify_accept_invite        22  /*����invite����, callidΪ���������id��*/

#define rtvnotify_broadcast_socket_error 23   /*ý�����������ݴ���*/
#define rtvnotify_speak_socket_error     24   
#define rtvnotify_media_socket_error     25

#define rtv_media_transtype_error  26   /*���紫������Э�̴���*/


#define rtvnotify_gotpicture   27   /*������ͼƬ�ص�*/
#define rtvnotify_gotframe     28   /*�յ�ý�����ݻص�*/



struct fhnrtv2_picture_data
{
	int picturetype;   /*0��bgr24   1��yuv420*/
	int width;
	int height;
	void* picturedata;
	long reserved;
};


struct fhnrtv2_frame_data
{
	int framelength;   /*ý��֡���ݳ���*/
	void* framedata;   /*ý������*/
	long reserved;
};


struct fhnrtv2_invite_info
{
	fhnrtv2_destlist *pInviteList;
	int mediatype;       /*invite �����ý������*/
};

struct fhnrtv2_broadcast_list_result
{
	int errorcode;
	int listid;
	fhnrtv2_destlist* pErrorList;
};
typedef int (*rtvideocallback) (long handle, long callid, int notifycode, 
							    long errorcode,long calluserdata,long reserved);

/************************************************************************
function:fhnrtv2_initial
author: lllei 20080319
param: 	phandle: the rt handle
        version: the msg version
		family: AF_INET or AF_INET6
process: initial rtvideo dll
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_initial(long* phandle,int version, int family);

FHNRTVIDEO2_API void fhnrtv2_setcallback(long handle, rtvideocallback rtvcallback);

/************************************************************************
function:fhnrtv2_setuserinfo
author: lllei 20080319
param: 	handle: the rt handle
        userid: the user id
process: set the user id
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_setuserinfo(long handle, char* userid,char* sessionid, char* serverid);

/************************************************************************
function:fhnrtv2_askmedia
author: lllei 20080319
param: 	handle: the rt handle
        destlist: ask media pu list, only broadcast can have multi dest
		          version2 can only process one dest
		mediatype:video/audio
process: ask dest media 
return: 0:error; else:the ask media callid
************************************************************************/
FHNRTVIDEO2_API long fhnrtv2_askmedia(long handle,fhnrtv2_destlist destlist,
									  enummediatype mt,char* destip, UINT destport,long calluserdata);

FHNRTVIDEO2_API long fhnrtv2_askmediaex(long handle,fhnrtv2_destlist destlist,enummediatype mt,
					  enumtranstype tt,char* destip, UINT destport, long calluserdata);
FHNRTVIDEO2_API long fhnrtv2_askmedia_broadcast(long handle,fhnrtv2_destlist destlist,enummediatype mt,
					  enumtranstype tt,char* destip, UINT destport, long calluserdata, int format);
FHNRTVIDEO2_API long fhnrtv2_setoverlaymode(long handle, long callhandle, BOOL boverlay, COLORREF clrkey);
/************************************************************************
function:fhnrtv2_setplaywnd
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
		hwnd:video play wnd
process: set video play wnd
return: NULL
************************************************************************/
FHNRTVIDEO2_API void fhnrtv2_setplaywnd(long handle, long callid, long hwnd, int videoindex); 
/************************************************************************
function:fhnrtv2_cappicture
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
		filepath:picture save path
process: capture picture
return: NULL
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_cappicture(long handle, long callid, char* filepath);

/************************************************************************
function:fhnrtv2_startrecord
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
		filepath:record save path
process: start record 
return: NULL
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_startrecord(long handle, long callid, char* filepath, int rec_type);

/************************************************************************
function:fhnrtv2_stoprecord
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
process: stop record 
return: NULL
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_stoprecord(long handle, long callid);

/************************************************************************
function:fhnrtv2_getframerate
author: lllei 20080319
param: 	handle: the rt handle
process: get the rtvideo framerate
return: framerate
************************************************************************/
FHNRTVIDEO2_API int  fhnrtv2_getframerate(long handle,long callid);

/************************************************************************
function:fhnrtv2_getflux
author: lllei 20080319
param: 	handle: the rt handle
process: get the rtvideo flux
return: flux
************************************************************************/
FHNRTVIDEO2_API float  fhnrtv2_getflux(long handle,long callid);

FHNRTVIDEO2_API void fhnrtv2_GetPacketCount(long  handle, long callid,int* RecPacket, int* LosePacket);

FHNRTVIDEO2_API BOOL fhnrtv2_RefreshPlaywnd(long handle, long callid);
/************************************************************************
function:fhnrtv2_stopmedia
author: lllei 20080319
param: 	phandle: the rt handle
        callid: askmedia return value
process: stop media
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_stopmedia(long handle,long callid);

FHNRTVIDEO2_API BOOL fhnrtv2_GetCallNetWorkInfo(long handle,long callid,fhn_Call_NetWork_Info *pCallInfo);

FHNRTVIDEO2_API BOOL fhnrtv2_GetCallMediaInfo(long handle,long callid,fhn_MediaInfo_rtp *pCallInfo);
/************************************************************************
function:fhnrtv2_destory
author: lllei 20080319
param: 	handle: the rt handle
process: destory rtvideo dll
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_destory(long handle);



FHNRTVIDEO2_API void fhnrtv2_EnablePictureCallback(long handle, BOOL benable);

FHNRTVIDEO2_API void fhnrtv2_EnableGrameCallback(long handle, BOOL benable);

#endif