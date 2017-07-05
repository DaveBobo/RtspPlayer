
#if !defined FHNCUCOMMON_H
#define FHNCUCOMMON_H

#define CUMSG_VERSION_2    1
#define CUMSG_VERSION_3    2

#define RECORD_STORETYPE_PU            0
#define RECORD_STORETYPE_SERVER        1/*¼���ļ��洢λ�ã�NRU*/
#define RECORD_STORETYPE_LOC		   2/*¼���ļ��洢λ�ã�LOCAL*/



#define TREE_NODE_LEVEL_GROUP         0   /*�豸��*/
#define TREE_NODE_LEVEL_PU            1   /*�豸*/
#define TREE_NODE_LEVEL_CHANNEL       2   /*ͨ��*/



#define cubm_error_sendmsg    10001
#define cubm_error_ielack     10002
#define cubm_error_picsize_too_lager    10006	/*ͼƬ̫��*/
#define cubm_error_findnotsrv	404	/*�Ҳ���������*/
#define cubm_error_findnotfile	204 /*�Ҳ���ͼƬ�ļ�*/

#define cubm_error_register_timeout  10003   /*ע����Ϣ���ͳ�ʱ*/
#define cubm_error_register_resp     10004   /*ע����Ϣ����ʧ��*/
#define cubm_error_nullmsg           10005   /*����Ϣ*/
#define cubm_error_readikey          10006   /*��ȡfhnkey����*/

enum enumpackettype
{
	PT_RTP = 1,
	PT_TS,
	PT_RTP_VERSION2,
	PT_RTP_VERSION3,

};

enum enumtranstype
{
	TT_TCP = 1,  //SOCK_STREAM
	TT_UDP,   //SOCK_DGRAM
};

enum enummediatype
{
	MT_VIDEO = 1,
	MT_SPEAK = 2,
	MT_BROAD = 3,
	MT_SUBSTREAM = 4,   //������

};

struct rtppacketport
{
	unsigned int rtpport;
	unsigned int rtcpport;
	unsigned int rtpsocket;
	unsigned int rtcpsocket;
};

struct fhnrtv2_destlist
{
	fhnrtv2_destlist *pnext;
	char              puid[32];
	int               channelno;
};

/*�Իط���Ƶ�� ��sdp�л�ȡ��Ƶ�����Ϣ 
  ���sdp��û��Я�������Ϣʱ��devtype ���12 picwidth 702 picheight 576 timescale 90000
  ͼ�񳤿���д������ܵ�����Ƶ������ʱͼ����ʾ������
  timescale ��д������ܵ���¼��ط�ʱ���Ų�����*/
struct DeviceDecInfo
{
	int devtype;
	int picwidth;
	int picheight;
	unsigned int timescale;  /*1S��ʱ������*/
	char config[512];
};


/*rtpý��������Ϣ*/
struct fhn_MediaInfo_rtp 
{
	int pt;         /*payload*/
	int TimeSpan; /*ʱ������*/
	int v_width;   /*��Ƶ��*/
	int v_height;  /*��Ƶ��*/
};

/*ý��Э�̵���Ϣ*/
struct fhn_Call_NetWork_Info
{

	char  DestIP[32];
	short DestRcvPort;
	short DestSendPort;
	short LocalRcvPort;
	short LocalSendPort;

	int   SdpCodec;
	char  SdpMap[512];

};

typedef enum rtsp_reply_type
{
	RTSP_PLAY_REPLAY = 1,     /*�������ӻ������Ӧ����Ҫ�жϴ�����*/  
	RTSP_STREAM_CUT,      /*5��û��ý������*/
	RTSP_STREAM_RECV_ERROR,  /*TCP��ʽ�������ݴ���*/
	RTSP_SERVER_SHUTUP,   /*�������Ͽ�����*/
	RTSP_RTP_DATA,         /*TCP ��ʽ�յ�ý�����ݰ�*/
	RTSP_RTCP_DATA,         /*TCP��ʽ�յ�RTCP��*/   
	RTSP_CALC_FRAMERATE  /*��ʱͳ������*/

}cm_reply_type_t;
typedef enum loc_file_reply
{
	FILE_PLAYOK,         //play video ok
	FILE_PLAYHEAD,       //back to head
    FILE_PLAYOVER,       //play over
	FILE_PLAYERROR       //play error
}loc_file_reply_type;


#define RTSP_RESP_SUCCESS          0   /*�ɹ�*/
#define RTSP_RESP_ERROR_TIMEOUT    1   /*��Ӧ��ʱ 5��*/
#define RTSP_RESP_ERROR_NOFILE     2   /*�Ҳ����ļ�*/
#define RTSP_RESP_ERROR_OTHER      3   /*��������*/
#define RTSP_RESP_ERROR_RECEIVE    4   /*�������ݴ���*/
#define RTSP_RESP_ERROR_SOCKET     5   /*����socket����*/
#define RTSP_RESP_FINISH		   6   /*�ļ��������*/


enum ePlayOption
{
	PLAY_FAST,
	PLAY_FASTSEEK,
	PLAY_SLOW,
	PLAY_SLOWSEEK,
	PLAY_FWOD,
	PLAY_FWODSEEK,
	PLAY_BACK,
	PLAY_BACKSEEK,
	PLAY_PAUSE,
	PLAY_PAUSESEEK,
	PLAY_CONT,
	PLAY_SETPOS,
	PLAY_GETFRAMERATE,
	PLAY_SETTIME,      /*ָ������ʱ���(����)*/
};



/*rtsp ������Ϣ*/
enum ERecPlayType
{
	VOD_CONURL_FAIL,           //�ط�socket����ʧ��
	VOD_CONURL_TIMEOUT,        //�طŹ��������ӳ�ʱ

	VOD_RTSP_UNKNOW_RESP,       //δ֪��Ӧ
	VOD_START_RTSP_RESP,        //start vod rtsp��Ӧ
	VOD_STOP_RTSP_RESP,         //stop vod rtsp ��Ӧ
	VOD_SPEED_RTSP_RESP,        //������rtsp��Ӧ
	VOD_SCALE_RTSP_RESP,        //�������rtsp��Ӧ
	VOD_PAUSE_RTSP_RESP,        //��ͣrtsp��Ӧ
	VOD_CONPLAY_RTSP_RESP,      //��������rtsp��Ӧ
	VOD_SPOTPLAY_RTSP_RESP,     //��λ����rtsp��Ӧ
	VOD_PLAY_STREAM_CUT,        //����ʱ���ӳ���
	VOD_PLAY_OVER,              //�������

	DOWN_CONURL_FAIL,           //����socket����ʧ��
	DOWN_CONURL_TIMEOUT,        //���ع��������ӳ�ʱ

	DOWN_RTSP_UNKNOW_RESP,      //δ֪��Ӧ
	DOWN_STRAT_RTSP_RESP,       //����rtsp�����Ӧ
	DOWN_STOP_RTSP_RESP,        //ֹͣ����rtsp�����Ӧ
	DOWN_SPEED_RTSP_RESP,       //���ر���rtsp��Ӧ
	DOWN_STREAM_CUT,            //����ʱ���ӳ���
	DOWN_OVER,                  //�������

	OPEN_FILE_RET,           //open file success
	OPEN_FILE_FAIL,           //open file failed
	PLAY_FILE_RET,           //play file error
	PLAY_FILE_END,            //the end of the playing file
	PLAY_FILE_HEAD,           //back to the head of the playing file
};

#define CHANNEL_TYPE_NULL    0
#define CHANNEL_TYPE_VIDEO_IN  1
#define CHANNEL_TYPE_ALARM_IN  5

#define STORE_POS_PU 						0 /*ǰ��*/
#define STORE_POS_NPC   					1 /*ͼ�������*/
#define STORE_POS_LOC						2 /*����*/

#define Media_FileType_PIC					1 /*ͼƬ�ļ�*/
#define Media_FileType_RECORD				2 /*¼���ļ�*/

#define RECORD_REASON_MANUAL				0 /*�ֹ�*/
#define RECORD_REASON_ALM					1 /*����*/
#define RECORD_REASON_TIME					2 /*��ʱ*/
#define RECORD_REASON_ALL					3 /*����*/
#define RECORD_REASON_DOWNLOAD				4 /*����*/

#define MAX_LOG_PUID_LEN            32
#define MAX_LOG_CHANNELNAME_LEN     64
#define MAX_LOG_DATA_LEN            32
#define MAX_LOG_EXTRA_LEN		    1024

#include <stdlib.h>

typedef struct LocalMedia_FileInfo    LocalMedia_FileInfo;
struct LocalMedia_FileInfo
{
	int  RecordType;                               //��¼���ͣ�ͼƬ��¼��
	char FilePath[_MAX_PATH] ;                     //�ļ�����·�������ļ���
	int  RecordReason;                             //��¼ԭ��һ�㡢�澯���ֹ�
	char PuId[MAX_LOG_PUID_LEN];                   //ͨ��ID
	int  ChannelNo;                                //ͨ����
	char ChannelName[MAX_LOG_CHANNELNAME_LEN];     //ͨ������
	char Createtime[MAX_LOG_DATA_LEN];             //�ļ�����ʱ��
    char Endtime[MAX_LOG_DATA_LEN];                //¼���ļ�����ʱ�䣬�����ͼƬ��ΪNULL 
	char extra[MAX_LOG_EXTRA_LEN];                 //������Ϣ��������չ
};


typedef struct LocalMedia_FileList    LocalMedia_FileList;    
struct LocalMedia_FileList
{
	LocalMedia_FileList	*next;
	LocalMedia_FileInfo	*obj;
};


typedef struct LocalMedia_QueryInfo    LocalMedia_QueryInfo;
struct LocalMedia_QueryInfo
{
	int   RecordType;                     //ͼƬ��¼������
	int   RecordReason;                   //��¼ԭ��һ�㡢�������ֹ�������
	char  PuId[MAX_LOG_PUID_LEN];         //ͨ��ID
	int   ChannelNo;                      //ͨ����
	char  BeginTime[MAX_LOG_DATA_LEN];    //��ѯ��ʼʱ��
	char  EndTime[MAX_LOG_DATA_LEN];      //��ѯ����ʱ��
	char  extra[MAX_LOG_EXTRA_LEN];       //������Ϣ,������չ
};

enum enumCoFileType{
	COFILE_UNKOW = 0,
	COFILE_DAHU = 1,      /*��*/
	COFILE_HIKA ,         /*����*/
	COFILE_FHN,           /*���*/
	COFILE_LC,            /*�ʳ�*/
	COFILE_HB,            /*����*/
	COFILE_TOPSEE,        /*����ͨ*/
	COFILE_STC,           /*����*/
};


/*RTP payload ý�����Ͷ���*/
#define PAYLOAD_AUDIO_FHN_G711    8        
#define PAYLOAD_AUDIO_FHN_ADPCM   36
#define PAYLOAD_AUDIO_FHN_PCM     42
#define PAYLOAD_AUDIO_DAHUA       38
#define PAYLOAD_AUDIO_STC         41
#define PAYLOAD_AUDIO_HIKI        43
#define PAYLOAD_AUDIO_LC          45
#define PAYLOAD_AUDIO_HB          51


#define PAYLOAD_MEDIA_FHN_H264    99
#define PAYLOAD_MEDIA_FHN_MPEG4   96
#define PAYLOAD_MEDIA_FHN_MPEG4_1 35
#define PAYLOAD_MEDIA_DAHUA       37
#define PAYLOAD_MEDIA_STC         40
#define PAYLOAD_MEDIA_HIKI        53
#define PAYLOAD_MEDIA_LC          44
#define PAYLOAD_MEDIA_HB          50
#endif