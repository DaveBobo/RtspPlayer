
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNNETMSG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNNETMSG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNNETMSG_EXPORTS
#define FHNNETMSG_API __declspec(dllexport)
#else
#define FHNNETMSG_API __declspec(dllimport)
#endif

#if !defined FHNNETMSG_H
#define FHNNETMSG_H

#include "nanohttp-common.h"
#include "nanohttp-clientserver.h"
#define enumnetmsgmodule unsigned int

#define  MODULE_BASIC          1   /*������Ϣ����ģ��*/
#define  MODULE_ALM            2   /*��������ģ��*/
#define  MODULE_MONITER        3   /*ʵʱ��ش���ģ��*/
#define  MODULE_PTZ            4   /*��̨����ģ��*/
#define  MODULE_RECORD         5   /*¼���ѯ �ط�ģ��*/
#define  MODULE_MEETING        6   /*��Ƶ����ģ��*/
#define  MODULE_PARAMSET       7   /*��������*/
#define  MODULE_IPMATRIX	   8   /*�������ģ��*/
#define  MODULE_SBSATX         9   /*BSģ��*/

enum enummsgformat
{
	FM_SIP,    /*mio���͵�sip��Ϣ*/
	FM_HTTP,  /*http��ʽ����Ϣ*/
	FM_MEDIA, /*sipЭ��*/
};

/*http����*/
enum enumhttpmsgtype
{
	NETMSG_HTTPCD_NC_RECV_REQ = 100,
	NETMSG_HTTPCD_NC_RECV_RESP,
	NETMSG_HTTPCD_NC_SND_REQ_FAIL,
	NETMSG_HTTPCD_NC_SND_RESP_FAIL,
	NETMSG_HTTPCD_NC_SND_AUTO_RESP,
	NETMSG_HTTPCD_NC_UNKNOWN,
};

enum enummediamsgtype
{
	MS_INVITE,    /*����ý��Э��*/
	MS_BYE,       /*�Ͽ�ý��*/
	MS_ACK,       /*����Ӧ��*/
};
typedef int (*moduleprocesscallback)(int notifycode, long msg, int msgid,long userdata);

/************************************************************************
function:fhnnetmsg_initial
author: lllei 20080304
param:  phandle: a point to a handle
		family: AF_INET or AF_INET6
process: initial the dll,create msg module
return: 0:success; else :error
        the phandle is a return
************************************************************************/
FHNNETMSG_API int  fhnnetmsg_initial(long * phandle, int family);

/************************************************************************
function:fhnnetmsg_destory
author: lllei 20080304
param:  the handle to destory
process: destory the msg module
return: void
************************************************************************/
FHNNETMSG_API  void   fhnnetmsg_destory(long handle);

/************************************************************************
function:fhnnetmsg_regmodule
author: lllei 20080304
param:  handle: initial function return value
        moduletype : the module
		moduleprocesscallback: receive function return
process: register a module to the dll
return: void
************************************************************************/
FHNNETMSG_API void fhnnetmsg_regmodule (long handle,enumnetmsgmodule moduletype,
									  moduleprocesscallback callbackproc);

/************************************************************************
function:fhnnetmsg_regreqmsg
author: lllei 20080304
param:  handle: initial function return value
        moduletype : the module
        msgtype: the module want req msg type
process: register a req msg receive
return: void
************************************************************************/
FHNNETMSG_API   void  fhnnetmsg_regreqmsg (long handle,enumnetmsgmodule moduletype,
										  int msgtype,long modulehandle);
/************************************************************************
function:fhhnnetmsg_sendreqmsg
author: lllei 20080304
param:  handle: initial function return value
        msg: the msg want to send,
		     if format == FM_MEDIA, the msg is ms_indicate_info_t struct
        userdata: msg userdata
process: send a req msg
return: msgid
************************************************************************/
FHNNETMSG_API int  fhhnnetmsg_sendreqmsg (long handle,void *msg,
										  void *userdata,char* toip, 
										  UINT port, enummsgformat format);

/************************************************************************
function:fhhnnetmsg_sendrespmsg
author: lllei 20080304
param:  handle: initial function return value
        msg: the msg want to send
        msgid: the req msgid
process: send a resp msg
return: void
************************************************************************/
FHNNETMSG_API int  fhhnnetmsg_sendrespmsg (long handle,void *msg, int msgid);

FHNNETMSG_API int fhnnetmsg_sendregister(long  handle, char* to, int toport,
										  char* username, char*passward,
										  int expires, void* reguserdata);

FHNNETMSG_API BOOL fhnnetmsg_cancelreg(long handle, int regid); 

FHNNETMSG_API miosMSG* fhnnetmsg_mallocmsghead(long handle);

FHNNETMSG_API void* fhnnetmsg_mallocie(long handle, int size);

FHNNETMSG_API void fhnnetmsg_malloclistnode(long handle);

FHNNETMSG_API void fhnnetmsg_add_ie_to_msg( long handle,miosMSG* msg, void* ie);

/*
 * ������miosMSG�ṹ����Ϣת������Ϣ�ı���
 *
 * �������壺
 *  handle: �ӿ�ģ����
 *  msg: ��Ҫת�����ı�����Ϣ
 *  buf: ����Ļ��档���ΪNULL������ֻ�Ǽ�����Ҫ��������ȡ�
 *  len: ����Ļ��泤�ȡ�
 *  
 *
 * ����ֵ��
 *  ����ת�����ı�֮��ĳ��ȡ����buf��ΪMIO_NULL������lenС��ʵ����Ҫ�ĳ��ȣ�����ֵΪ����Ҫ�ĳ��ȵ��෴����
 *
 */

FHNNETMSG_API int fhnnetmsg_encodeMSG( long handle, miosMSG *msg, char* buf, int len);

FHNNETMSG_API int fhhnnetmsg_sendhttpgetpic(long handle, hpair_t * querylist, void *userdata, char* toip, UINT port);
FHNNETMSG_API int fhnnetmsg_ConvertUTF8ToGb2312(long handle, char* utf8str, char* gb2312str, int gb2312len);

FHNNETMSG_API int fhnnetmsg_ConvertGb2312ToUTF8(long handle, char* gb2312str, char* utf8str, int utf8len);

FHNNETMSG_API int fhnnetmsg_SetSipKeepAliveInterval(long handle, int time);


FHNNETMSG_API miosMSG* fhnnetmsg_decodeMSG(long handle , char* buf, int len);

FHNNETMSG_API void fhnnetmsg_freeMsg(long handle, miosMSG* msg);
FHNNETMSG_API BOOL fhnnetmsg_GetLocalIp(long handle, char* localip, int len, char* dstip);
FHNNETMSG_API int fhnnetmsg_GetAddrFamily(char * ip);
#endif