#ifndef _RTSPMODULE_H
#define _RTSPMODULE_H


#include "fhncucommon.h"
//RTSP��Ӧ�Ĵ�����
enum RTSPStatusCode 
{
	NOT_RTSPMESSAGE = 1,
	RTSP_200 = 200,
	RTSP_400 = 400,
	RTSP_404 = 404,
	RTSP_500 = 500,
	RTSP_461 = 461,

	//SET_PARAMETER,ANNOUNCE status code

	RTSP_SET_PARAMETER_800 = 800, //left boundary of timeshif,my server use set_parameter method
	RTSP_SET_PARAMETER_801 = 801, //right boundary of timeshif
	RTSP_ANNOUNCE_2101 = 2101,//left boundary of timeshif,china telecom use announce method
	RTSP_ANNOUNCE_2102 = 2102 //right boundary of timeshif ,china telecom use announce method
};

typedef enum rtsp_request_type 
{
    RTSP_GETINFO_REQ=1, /*��ȡý����Ϣ*/
	RTSP_SETUP_REQ, /*������������*/ 
    RTSP_PLAY_REQ,/*����*/
    RTSP_PAUSE_REQ,/*��ͣ*/
    RTSP_SCALE_REQ,/*���������*/
	RTSP_SPEED_REQ,/*��š�����*/
	RTSP_SEEK_REQ, /*��λ����*/
    RTSP_TEARDOWN_REQ,/*�Ͽ�����*/

	//add by TIAN  20070730  ��ͨ  ���Ӷ�֡��������
    RTSP_APPFRAME_REQ  /*��֡����*/
} cm_request_type_t;
 

typedef struct rtsp_request_info
{
	cm_request_type_t  type;
	char  URL[128];
	int  Param; 
	char User_Id[128];
	int  SocketMark;
	char Scale_N[128];
	char SeekTime[128];
	char Speed_N[128];
	//add by TIAN  20070730  ��ͨ  �洢ָ��֡��ֵ���ϴ���CU
	char SeekFrame[128];

} RTSPRequest_Info;

enum enum_rtsp_senddata_type
{
	enum_rtsp_rtcp_rr = 1,  /*rtcp���ܱ���*/

};


//add by TIAN  2007.7.18
typedef struct rtp_media_data
{

	int            MediaType;
	char           *MediaBuf;
	unsigned int   ts;
	int            MediaLen;
}cm_media_data_t;

typedef struct rtsp_sdp_info
{
	cm_reply_type_t  r_type;
	unsigned  VideoNum;
	unsigned  AudioNum;
	//add by TIAN  20070730  ��ͨ  
	unsigned  FrameRate;
	//end add
	cm_media_data_t  media_data;


	unsigned  VideoTimescale;                //DESCRIBE���ز���
	unsigned  AudioTimescale;  
	char     VideoConfig[1024];
	char     AudioConfig[1024];
	unsigned  range;
	int       VideoTrackId;
	int       AudioTrackId;
	unsigned short   Audiomode;
	int A_Config;

	int Error_Code;

	int Socketmark;
	void* pRecPlay;
	void * pCon;
	unsigned short  NRUUdp_V_Port;             //SETUP���ز���
	unsigned short  NRUUdp_A_Port;
	unsigned short  Client_V_Port;
	unsigned short  Client_A_Port;
	char      RTSPSessionId[128];
	unsigned int      VideoSSRC;
	unsigned int      AudioSSRC;
	//add by TIAN   2007.7.23
	int TranType;

	//add by lm 20080716
	unsigned int VideoWidth;
	unsigned int VideoHeight;
	//end by lm 20080716

}RSDP_info;

  
#ifdef RTSPINTERFACE_EXPORTS
#define RTSPINTERFACE_API __declspec(dllexport)
#else
#define RTSPINTERFACE_API __declspec(dllimport)
#endif

typedef int (*RNotifyHandle)(RSDP_info *RSDPInfo);


RTSPINTERFACE_API int RTSPRequest(void *rtsp,RTSPRequest_Info *RtspRequestInfo);
RTSPINTERFACE_API void* RTSPInital(RNotifyHandle RTSPNotifyHandle, int NruType);
RTSPINTERFACE_API int InitPlayer(void *rtsp,char* URL,int trans_protocol,void* pRecplay,void* pCon);
/*ʹ��rtsp������˿ڷ������ݵ��Զˣ�Ŀǰֻ��TCP��ʽ����RTCP���ܱ���, ����ֵΪ�������ݵĳ���*/
RTSPINTERFACE_API int RTSP_SendData(void *rtsp, char* SendData, int SendLength, enum_rtsp_senddata_type DataType);
RTSPINTERFACE_API float RTSP_GetTcpFlux(void *rtsp);
RTSPINTERFACE_API int RTSPDestory(void *rtsp);


#endif