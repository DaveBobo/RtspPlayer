
#if !defined (CUBASICMSG_H_LLL)
#define CUBASICMSG_H_LLL
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CUBASICMSG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CUBASICMSG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CUBASICMSG_EXPORTS
#define CUBASICMSG_API __declspec(dllexport)
#else
#define CUBASICMSG_API __declspec(dllimport)
#endif


//#define cubm_error_sendmsg    10001
//#define cubm_error_ielack     10002
//#define cubm_error_picsize_too_lager    10006	/*ͼƬ̫��*/
//#define cubm_error_findnotsrv	404	/*�Ҳ���������*/
//#define cubm_error_findnotfile	204 /*�Ҳ���ͼƬ�ļ�*/

//#define cubm_error_register_timeout  10003   /*ע����Ϣ���ͳ�ʱ*/
//#define cubm_error_register_resp     10004   /*ע����Ϣ����ʧ��*/
//#define cubm_error_nullmsg           10005   /*����Ϣ*/

#define cubm_pulistv3_ack      1   

#define cubm_puinfo_ack        3

#define cubm_login_ack         5
#define cubm_register_ack      6   /*added by lllei 20080807 ע����Ӧ*/

#define cubm_offline           7    

#define cubm_pulistv2_ack      9
#define cubm_ptzset_ack        10    


#define cubm_receive_alm 		 11
#define cubm_receive_threshold   12

#define cubm_receive_time_verify_resp 13
#define cubm_receive_pu_notify_req    14
#define cubm_receive_alarm_query_resp 15

#define cubm_ipmatric_query_resp  16  /*�����ѯ��Ӧ*/

#define cubm_getchannelposition	 17	 /*��ص�λ�ø�����Ӧ*/

#define cubm_VersionInfo_resp 18	/*�汾��Ϣ��Ӧ*/

#define cubm_callstatus_notify  19   /*����״̬֪ͨ*/
#define cubm_pswchange_resp     20   /*�޸��û�������Ӧ*/

#define cubm_http_get_pic_resp	21	/*��ȡͼƬ����*/

#define cubm_querypic_resp 22 /*ǰ��ͼƬ��ѯ��Ӧ*/
#define cubm_delpic_resp 23 /*ǰ��ͼƬɾ����Ӧ*/

#define cubm_regekey_resp 23 /*key��֤��Ӧ*/

#define STREAM_DISCONNECT_ALARM 1  /*��Ƶ���Ͽ�*/
#define STREAM_INTERRUPT_ALARM 2   /*��Ƶ������*/





#define CUMSG_VERSION_2    1
#define CUMSG_VERSION_3    2

#define CUBM_IPADDR_LEN		40	//for support ipv6

struct user
{
	char  name[128];
	char  psw[128];
	char  id[64];
	char  sessionid[64];
	BOOL  isadmin;
};

struct ikeyinfo
{
	long errorcode;
	char chancode[64];
};

struct cubm_alminfo
{
	char puid[64];
	int  channelno;
	int  almtype;
	char almtime[64];  /*yyyy-mm-dd  hh:mm:ss*/
	char almdesp[128];
	char almid[33];
	char channelname[33];
	int almchanneltype;  /*����ͨ������*/
	char almlevel[33]; //��������
};

struct alarmLogQuery
{
	unsigned int logType;
	char logTime[128];
	char logEvent;
	char logObjectID[19];
	short logChannel;
	unsigned int logInfo;
	char logDesp[256];
	struct alarmLogQuery *next;
	char almlevel[33]; //��������
};

struct cubm_alarmLogQueryInfo
{
	struct alarmLogQuery *LogQuerylist;
	int	logCount;
};

typedef struct group group;
typedef struct pu    pu;
typedef struct channel channel;

struct moniter  /*no use */
{
	moniter* pnext; 
	pu*	parent;
	int videoid;
	channel* VideoChannel;
	channel* channellist;
};

struct channel
{
	int nodetype;         /*�ڵ�����*/
	channel *pnext;
	pu* parent;
	int id;               /*ͨ����*/
	int type;             /*ͨ������*/
	int coresvideoid;     /*��Ӧ����ƵID�� no use*/
	char name[128];       /*ͨ������*/
	double x;             /*X����*/
	double y;             /*Y����*/
	__int32 UserRight;    /*Ȩ��*/
	BOOL   HasAudioIn;      /*�Ƿ�����Ƶ����*/
	char outDevType[128]; /*����豸����*/
	
	/*	ͨ��״̬: ��bitλ����ʾ, ��0λ: ƽ̨�ֶ�¼��; 
	��1λ: ǰ���ֶ�¼��; 0: ��ʾû��¼��,1: ��ʾ����¼��  add by lxf */
	unsigned int channelstate;

	unsigned __int16 orderstate;  /*ͨ��������״̬*/
	void*  channeldata;
};

struct httppicinfo
{
	char filename[1024];		/*ͼƬ�ļ���*/
	char body[2*1024*1024];		/*ͼƬ����*/
	long	bodylen;
	char path[1024];
};

struct pu
{
	int    nodetype;
	pu*    pnext;
	group* parent;
	char   id[32];
	char   name[128];
	int    channelnum;            /*no use*/
	BOOL   online;
	channel* channellist;         /*��Ƶͨ���б�*/
	moniter* moniterlist;         /*no use */
	double x;
	double y;
	BOOL   HasAudioOut;            /*�Ƿ�����Ƶ���*/
	int    AlmInNum;               /*��������ͨ����*/
	int    AlmOutNum;              /*�������ͨ����*/
	__int32 PlatformManufactureID; /*����ID��*/
	__int16 m_ManufactureID;       /*������չ*/
	char    DeviceTypeName[33];    /*�豸��������*/
	char    Addr[CUBM_IPADDR_LEN];              /*ip��ַ*/
	UINT    port;                  /*�˿�*/               

	/* �Ƿ��Ѳ�ѯ����ϸPU��Ϣ���������£�
	��0λ��ͨ����Ϣ�Ƿ��ȡ��־����1λ����������Ϣ�Ƿ��ȡ��־����2λ��¼��״̬�Ƿ��ѯ*/
	int  HasGotDetail;    

	void * pAlmDesp;
};

struct group
{
	int   nodetype;
	group* pparent;             /*�ϲ���ڵ�*/
	group* downgroup;           /*�¼���*/
	group* pnext;
	unsigned __int64    id;
	char  name[128];
	pu*   pulist;
	BOOL  HasGotDetail;          /*�Ƿ��Ѳ�ѯ����ϸPU�б�*/

};

struct IpMatrixNode;
struct IpMatrixChannelNode
{
	IpMatrixChannelNode* pnext;
	IpMatrixNode*   pMatric;
	UINT            id;
	int             ChannelType;
	short			ChannelNum;
};
struct IpMatrixNode
{
	IpMatrixNode* pnext;
	BOOL Online;
	char ID[32];
	char IP[64];
	char Name[64];
	UINT port;
	int  ChannelNum;
	unsigned __int64 GroupID;
	char GroupName[33];
	int DeviceType;
	IpMatrixChannelNode* pChannelList;
};


struct PuChannelPositionNode
{
	char PUID[32];
	int  ChannelNo;
	int  ChannelType;
	double x;
	double y;
	PuChannelPositionNode* pnext;
};

struct VersionInfo
{
	char Version[32];
	int CuRole;  /*1:C/S�ͻ���; 2:B/S�ͻ���*/
	int SoftwareFlag;	/*1:�ļ�����; 2:���°�װ*/
	int UpdateFlag; /*0:����Ҫǿ������; 1:��Ҫǿ������*/
	char Ftp_addr[CUBM_IPADDR_LEN];	
	short Ftp_port;
	char Ftp_name[64];
	char Ftp_password[64];
	int Ftp_timeout;/*��Чʱ��*/
	char Ftp_folder[128];/*���λ��*/
};

struct PictureInfo 
{
	PictureInfo* pnext;
	long CapTime;
	char Name[255];
	long Size;
	char Address[CUBM_IPADDR_LEN];	
	long Port;
};

struct PicInfoResult
{
	long totalcount;
	long restcount;
	PictureInfo* pPicInfo;
};

//add by lm 20090415
enum ThresholType
{
	THRESH_RT_CONNECT = 1,	//������Ƶ���ӣ�
	THRESH_RT_CONNECT_SUCC,	//��Ƶ���ӳɹ�������
	THRESH_RT_CONNECT_FAIL,	//��Ƶ����ʧ�ܣ�
	THRESH_RT_DISCON,		//�ͷ���Ƶ���ӣ�
	THRESH_RT_DISCON_ABNORMAL,	//�쳣�ͷ���Ƶ���ӣ�
	THRESH_VOD_CONNECT,			//VOD���ӣ�
	THRESH_VOD_CONNECT_FAIL,	//VOD����ʧ�ܣ�
	THRESH_NO_VIDEO,			//�޼����Ƶ(������);
	THRESH_VIDEO_FRAME_CHANG	//�������䣻

};

struct ThresholdValue
{
	ThresholType thresholdType;
	int thresholdValue;
};


typedef struct thValueList{
	thValueList	*next;
	ThresholdValue	*obj;
}thValueList;


#define MAX_LOG_PUID_LEN            32
#define MAX_LOG_CHANNELNAME_LEN     64
#define MAX_LOG_DATA_LEN            32
#define MAX_LOG_EXTRA_LEN		    1024

struct NPCMedia_QueryInfo
{
	int   RecordReason;                 //��¼ԭ���ֶ���0��������1����ʱ��2(���أ�δʹ��)�����У�3
	char  PuId[MAX_LOG_PUID_LEN];       //ͨ��ID
	int   ChannelNo;                    //ͨ����
	long  BeginTime;					//��ѯ��ʼʱ��
	long  EndTime;						//��ѯ����ʱ��
	int	  from;							//��ѯ��Ŀ��ʼ��
	int	  to;							//��ѯ��Ŀ������
	int   storetype;					//�洢λ�ã�ƽ̨��1��ǰ�ˣ�0(���أ�δʹ��)
};

struct  cubm_CallStatus
{
	int CallListID;
	char PUID[32];
	int ChannelNo;
	int CallStatus;
};
/*********************************************************************
if notifycode = ****_nack, the result is the errorcode
if notifycode = cubm_login_ack , the result is a point to user struct
if notifycode = cubm_pulist_ack, the result is a point to group struct

*********************************************************************/
     
typedef int (* cubmcallback)(long phandle,int notifycode, int msgid, long result, 
							 long errorcode, long reserved2);

/************************************************************************
function:cubm_initial
author: lllei 20080321
param: phandle: a point to bm handle
	   family: AF_INET or AF_INET6
process: initial the basic msg dll
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_initial(long* phandle ,int version, int family);

CUBASICMSG_API void cubm_destory(long phandle);

/************************************************************************
function:cubm_setcallback
author: lllei 20080326
param: handle: bm handle
       proc: callback process
process: set the bm callback
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_setcallback(long handle, cubmcallback proc);

/************************************************************************
function:cubm_register  this function only used in version 3.0
author: lllei 20080318
param: handle: the bm handle
       username:the register username 
	   serverip:
	   port:
process: register to server,the register result will be notified in callback
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_register(long handle,char* username,char*password,
								 char* serverip, UINT port);

/************************************************************************
function:cubm_login  this function only used in version 2.0
author: lllei 20080318
param: handle: the bm handle
       username:the login username 
	   serverip: 
	   port:
process: login to server,the login result will be notified in callback
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_login(long handle,char* username,char*password,
								 char* serverip,char* sereverid, UINT port);

/************************************************************************
function:cubm_logout  this function only used in version 2.0
author: lllei 20080318
param: handle: the bm handle
process: logout to server
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API void cubm_logout(long handle);

/************************************************************************
function:cubm_pugrouplist
author: lllei 20080321
param: handle: the bm handle
       groupid:the pugroup want to list
	   if groupid is null, will list all the pu
process: send list req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_pugrouplist(long handle,/*in*/int groupid);

/************************************************************************
function:cubm_getpuinfo, this function can only used in 3.0
author: lllei 20080321
param: handle: the bm handle
       puid:the puid want to get info, cant be null
process: send info req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_getpuinfo(long handle,/*in*/char* puid);
CUBASICMSG_API int cubm_getpuinfoex(long handle,/*in*/pu* pulist);
/************************************************************************
function:cubm_ptzcontrol
author: lllei 20080321
param: handle: the bm handle
process: send info req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_ptzcontrol(long handle, char* puid, int channelno,
								   int ptztype, int param1, int param2, char* channelname);

/*͸����Ϣ*/
CUBASICMSG_API int cubm_ComTransParent(long handle, char* puid, int channelno,
									char* ComData, int len);

/*��־��ѯ*/
CUBASICMSG_API int cubm_logquery(long handle,unsigned char logType,char *puid,int puChannel, int channeltype,long beginTime,long endTime,
		int startCount,int endCount, long userdata,int logInfo);

/*���������ϱ�*/
CUBASICMSG_API int cubm_stream_alarm_ind(long handle,int alarmType,char *puId,int channelNo,char *time);
/*��ѯ��������*/
CUBASICMSG_API int cubm_stream_threshold_query_req(long handle);

/*�ϱ��հ� ����״̬*/
CUBASICMSG_API int cubm_packet_loseinfo_ind(long handle,char *puId,int channelNo,
											long lostPacket,long rcvPacket);

/*��������ѯ*/
CUBASICMSG_API int cubm_ipmatric_query(long handle);
/************************************************************************
function:cubm_pugroup
author: lllei 20080321
param: handle: the bm handle
       groupid:the pugroup want to list
	   if groupid is null, will list all the pu
process: send list req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_getsessionid(long handle, /*out*/char* sessionid);

CUBASICMSG_API int cubm_getserverid(long handle, /*out*/char* serverid);
CUBASICMSG_API int cubm_getuserid(long handle, /*out*/ char* userid);

CUBASICMSG_API int cubm_UploadPuChannelPosition(long handle, PuChannelPositionNode* pPositionList, long temphandle);
CUBASICMSG_API int cubm_SendVersionInfo(long handle, VersionInfo* pMyVersion);

CUBASICMSG_API int cubm_ChangePsw(long handle,char* oldpsw, char* newpsw);
CUBASICMSG_API int cubm_QueryPic(long handle, char* puid, int ChannelNo, int channeltype, NPCMedia_QueryInfo* pPicQueryInfo, long temphandle);
CUBASICMSG_API int cubm_DelPic(long handle, char* puid, int ChannelNo, int channeltype, PictureInfo* pPicQueryInfo, long temphandle, int storetype);

CUBASICMSG_API  int cubm_ChangePsw(long handle,char* oldpsw, char* newpsw);

CUBASICMSG_API int cubm_verifyKey(long handle,char* chanllengecode,int codelen);
/*******************************************************
���ܣ����ͻ�ȡͼƬ������
filename: ͼƬ�����֣�
ip: ͼƬ��������ַ��
port: ͼƬ�������˿ڣ�
puserdata: Ӧ�ò�����
path: ͼƬ·��(����Ҫ�Ļ��ɲ���)
******************************************************/
CUBASICMSG_API int cubm_httpgetpicbyfilename(long handle, char * filename, char * ip, unsigned port, void * puserdata, char * path = NULL);

CUBASICMSG_API int cubm_query_alm_pic(long handle, NPCMedia_QueryInfo* pPicQueryInfo, char * almid, void * puserdata);

//add by lm 20090415
CUBASICMSG_API int cubm_getthresholdstate(long handle, int threshtype, int threshvalue,void * puserdata);
CUBASICMSG_API int cubm_reportthresholdvalue(long handle ,char* puid,int channelno,int threshtype,void * puserdata);

CUBASICMSG_API void cubm_setbasicinfo(long handle, char* userid, char* username,char*psw, char*serverip, UINT port);

#endif

