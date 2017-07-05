 
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PUPARAMSET_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PUPARAMSET_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PUPARAMSET_EXPORTS
#define PUPARAMSET_API __declspec(dllexport)
#else
#define PUPARAMSET_API __declspec(dllimport)
#endif

#ifndef _PUPARAMSET_H_ 
#define _PUPARAMSET_H_

#define	SIP		0	/*mio���͵�sip��Ϣ*/
#define	HTTP	1	/*http��ʽ����Ϣ*/
#define	MEDIA	2	/*sipЭ��*/

#define param_type_almin	1
#define param_type_almout	2

#define param_recv_resp 1	//�յ���Ӧ
#define param_recv_req	2	//�յ�����(�¼�)

#define PLATFORM_MANUAL_REC	1	//ƽ̨�ֶ�¼��
#define PU_MANUAL_REC		2	//ǰ���ֶ�¼��

/*¼��״̬��ѯ*/
#define QUERY_PLATFORM_REC_STATE PLATFORM_MANUAL_REC
#define QUERY_PU_REC_STATE		 PU_MANUAL_REC

#define param_send_failed_resp -1
//��̨(����)����
#define param_set_ptz_resp				WM_USER + 1
#define param_get_ptz_resp				WM_USER + 2

//��Ƶ����
#define param_set_encode_resp			WM_USER + 3
#define param_get_encode_resp			WM_USER + 4

//��Ƶ����
#define param_set_audioencode_resp		WM_USER + 5
#define param_get_audioencode_resp		WM_USER + 6

//��ʾ����
#define param_set_display_resp			WM_USER + 7
#define param_get_display_resp			WM_USER + 8

//��Ļ����
#define param_set_osd_resp				WM_USER + 9
#define param_get_osd_resp				WM_USER + 10

//ǰ�˴洢��������
#define param_set_storepolicy_resp		WM_USER + 11
#define param_get_storepolicy_resp		WM_USER + 12

//�������澯
#define param_set_gpin_alm_resp			WM_USER + 13
#define param_get_gpin_alm_resp			WM_USER + 14

//Ѳ���켣
#define param_set_cruise_resp			WM_USER + 15
#define param_get_cruise_resp			WM_USER + 16

//�ƶ����ʹ��
#define param_set_alm_motion_dect_resp	WM_USER + 17
#define param_get_alm_motion_dect_resp	WM_USER + 18

//�ڵ����ʹ��
#define param_set_alm_cover_dect_resp	WM_USER + 19
#define param_get_alm_cover_dect_resp	WM_USER + 20

//��ʧ���ʹ��
#define param_set_alm_lose_dect_resp	WM_USER + 21
#define param_get_alm_lose_dect_resp	WM_USER + 22

#define param_set_alm_config_resp		WM_USER + 23
#define param_get_alm_config_resp		WM_USER + 24

//�澯ʹ��
#define param_set_alm_enable_resp		WM_USER + 25
#define param_get_alm_enable_resp		WM_USER + 26

//ǰ��¼���������
#define param_get_pu_record_resp		WM_USER + 27
#define param_set_pu_record_resp		WM_USER + 28

//�ƶ��������澯
#define param_set_motion_region_resp	WM_USER + 29
#define param_get_motion_region_resp	WM_USER + 30

//�ڵ��������澯
#define param_set_cover_region_resp		WM_USER + 31
#define param_get_cover_region_resp		WM_USER + 32

#define param_set_preset_node_resp		WM_USER + 33
#define param_get_preset_node_resp		WM_USER + 34
#define param_delete_preset_node_resp	WM_USER + 35
#define param_set_cap_resp				WM_USER + 36
#define param_get_cap_resp				WM_USER + 37

//ǰ��¼���������
#define param_set_platform_record_resp	WM_USER + 38
#define param_get_platform_record_resp	WM_USER + 39

//��Ƶ�������ز�������
#define param_set_video_hide_resp		WM_USER + 40
#define param_get_video_hide_resp		WM_USER + 41

//��ȡǰ��io��Ϣ
#define param_get_io_para_resp			WM_USER + 42
//����Ԥ��λ
#define param_call_preset_resp			WM_USER + 43

#define param_set_base_param_resp		WM_USER + 44
#define param_get_base_param_resp		WM_USER + 45

//�Զ���λ����
#define param_set_preset_reset_resp		WM_USER + 46
#define param_get_preset_reset_resp		WM_USER + 47

#define param_start_record_pu_resp		WM_USER + 48	//ǰ�˿�ʼ¼����Ӧ
#define param_stop_record_pu_resp		WM_USER + 49	//ǰ��ֹͣ¼����Ӧ
#define param_start_record_plat_resp	WM_USER + 50	//ƽ̨��ʼ¼����Ӧ
#define param_stop_record_plat_resp		WM_USER + 51	//ƽֹ̨ͣ¼����Ӧ
#define param_query_pu_record_status_resp	WM_USER + 52	//��ѯ¼��״̬:ǰ��
#define param_query_plat_record_status_resp	WM_USER + 53	//��ѯ¼��״̬:ƽ̨

#define param_pu_report_status_req			WM_USER + 54	//ǰ���ϱ�״̬(�ֶ�¼��)
#define param_nru_report_status_req			WM_USER + 55	//nru�ϱ�״̬(�ֶ�¼��)

#define param_stop_output_resp				WM_USER + 56	//ֹͣ����������ĸ澯�����ڽӾ�
#define param_get_pu_time_resp				WM_USER + 57	//��ȡǰ��ʱ��
#define param_set_pu_time_resp				WM_USER + 58	//����ǰ��ʱ��
#define param_get_pu_input_output_resp		WM_USER + 59
#define param_set_pu_input_output_resp		WM_USER + 60	

#define param_set_pu_cap_resp			WM_USER + 61	//ǰ��ץ��ͼƬ
#define param_get_npu_resp				WM_USER + 62	//ǰ��ͼƬ������
#define param_set_npu_resp				WM_USER + 63


//����������״̬
#define param_get_pu_input_state_resp		WM_USER + 64
#define param_set_pu_input_state_resp		WM_USER + 65	

//���������״̬
#define param_get_pu_output_state_resp		WM_USER + 66
#define param_set_pu_output_state_resp		WM_USER + 67	

#define param_get_pu_version_resp		WM_USER + 68	//ǰ�˰汾��
#define param_get_cap_status_resp		WM_USER + 69	//��ȡץ��״̬
#define param_cap_begin_resp			WM_USER + 70	//��ʼץ��
#define param_cap_end_resp				WM_USER + 71	//ֹͣץ��
#define param_set_time_cap_resp			WM_USER + 72	//���ö�ʱץ��
#define param_get_time_cap_resp			WM_USER + 73	//��ȡ��ʱץ��

#define param_get_motion_alm_out_resp	WM_USER + 74	//��ȡ�澯������Ϣ(���ڽӾ�)
#define param_get_cover_alm_out_resp	WM_USER + 75	//��ȡ�澯������Ϣ(���ڽӾ�)
#define param_get_lose_alm_out_resp		WM_USER + 76	//��ȡ�澯������Ϣ(���ڽӾ�)
#define param_get_input_alm_out_resp	WM_USER + 76	//��ȡ�澯������Ϣ(���ڽӾ�)
#define param_get_pu_state_resp			WM_USER + 78	//��ȡǰ��״̬��Ϣ
#define param_reset_dispaly_resp		WM_USER + 79	//������Ƶ����


/*������������*/
#define	DISK_PARA				0
#define	ALARM_RECORD			1
#define CAP_PHOTO				2
#define GPIN_ALARM				3
#define VIDEO_LOSE_ALARM		4
#define VIDEO_HIDE_ALARM		5
#define	VIDEO_MOVE_ALARM		6
#define VIDEO_MOVE_ALARM_AREA	7
#define VIDEO_HIDE_ALARM_AREA	8
#define GPIN_ALARM_PLATFORM		9		//ƽ̨�������澯��ѯ
#define VIDEO_LOSE_ALARM_PLATFORM	10	//ƽ̨��ʧ�澯��ѯ
#define VIDEO_HIDE_ALARM_PLATFORM	11	//ƽ̨�ڵ��澯��ѯ
#define VIDEO_MOVE_ALARM_PLATFORM	12	//ƽ̨�ƶ��澯��ѯ
#define ALMOUT_VIDEO_MOVE			13  //��Ƶ�ƶ������澯���
#define ALMOUT_VIDEO_HIDE			14  //��Ƶ�ڵ������澯���
#define ALMOUT_VIDEO_LOSE			15  //��Ƶ��ʧ�����澯���
#define ALMOUT_GPIN					16  //���뿪���������澯���

//ǰ��״̬
#define BIT_PU_MANUAL_REC		0 // ǰ���ֶ�¼��bit��־λ
#define BIT_PLATFORM_MANUAL_REC	1 // ƽ̨�ֶ�¼��bit��־λ
#define BIT_PU_TIME_REC			2 // ǰ�˶�ʱ¼��bit��־λ
#define BIT_PLAT_TIME_REC		3 // ƽ̨��ʱ¼��bit��־λ
#define BIT_ALARM_REC			4 // �澯¼��bit��־λ

#define PARAM_ALM_MAX_NUM		16  //�澯�����������Ŀ

struct param_pu_version
{
	char hardwareVersion[33];
	char softwareVersion[33];
	char diskWithholdSize[33];
	char diskUsedSize[33];
	char diskRemainSize[33];
	char devType[33];
};

struct param_pu_time
{
	int mode;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

struct param_pu_input
{
	param_pu_input * pnext;

	int type;
	int chno;  //������ͨ����
	int state; //������״̬

	int devtype; //1: ������ 2:������
};
typedef param_pu_input param_pu_output;

struct param_chinfo
{
	char puid[20];
	int chno;
};

//video channel status
struct param_channel_record_state
{
	char puid[20];
	int chno;
	unsigned char recordStatus;	//¼��״̬
	unsigned char signalStatus;	//���ӵ���Ƶ�ź�״̬
	unsigned char hardwareStatus;	//Ӳ��״̬ 0:���� 1:�쳣
	char  rate[33];	//ʵ������

	param_channel_record_state * pnext;
};
typedef param_channel_record_state param_video_channel_state;

struct param_disk_state
{
	int  diskid;

	char totalsize[64];	//Ӳ������
	char freesize[64];	//ʣ��ռ�
	unsigned char  status; //1:���� 2:������

	param_disk_state * pnext;
};

struct param_alm_in_state
{
	int  almno;
	unsigned char status;

	param_alm_in_state * pnext;
};
typedef param_alm_in_state param_alm_out_state;

struct param_pu_dev_status
{
	char puid[20];
	unsigned char pustate; //0:���� 1:CPUռ��̫�� 2:Ӳ������
	
	param_disk_state * pdiskstate;
	param_video_channel_state * pvideochstate;
	param_alm_in_state * palminstate;
	param_alm_out_state * palmoutstate;
};

struct param_channel_base_param
{
	int m_ChannelType;
	int m_ChannelNo;
	char m_ChannelName[33];
};

struct param_pu_io_info
{
	char ID[19];
	char DomainID[7];
	char Name[33];
	char IP[41];
	int DeviceType;
	int PlatformManufactureID;
	int ManufactureID;
	int VideoInNum;
	int VideoOutNum;
	int AudioInNum;
	int AudioOutNum;
	int AlarmInNum;
	int AlarmOutNum;
	int NonStandardNum;
	int MatrixNum;
};

struct param_preset_node
{
	int index;
	char name[64];

	param_preset_node * pnext;
};

//Ѳ����
struct param_cruisepoint
{
	int presetindex;
	int dwelltime;
	int speed;
	char name[64];

	param_cruisepoint * pnext;
};

//Ѳ���켣
struct param_cruise
{
	int ptzid;
	int cruiseid;

	param_cruisepoint * plist;
};

struct param_image_encode
{
	int Type; /*δʹ��*/
	unsigned EncodeMode;
	unsigned PicQuality;
	unsigned BitRate;
	unsigned BitRateType;
	unsigned FrameRate;
	unsigned ImageSize;
	unsigned StreamType;
	unsigned IFrameInterval;

	unsigned EncodeModeA;
	unsigned PicQualityA;
	unsigned BitRateA;
	unsigned BitRateTypeA;
	unsigned FrameRateA;
	unsigned ImageSizeA;
	unsigned StreamTypeA;
	unsigned IFrameIntervalA;

	int ChannelMode;	//��ʽ
};

//��ʾ����
struct param_display
{
	int Contrast;
	int Bright;
	int Hue;
	int Saturation;	
	int Whiteness;
};

//��Ƶ����������
struct param_video_in_encode
{
	param_image_encode ImageEncode;
	param_display Display;
};

//��Ƶ����������
struct param_audio_in_encode
{
	int EncodeMode;
	int Sample;
	int TrackNo;
	int EncodeBitRate;
	int QuanBitRate;
};

//osd����
struct param_osd
{
	int  bitmapX;
	int  bitmapY;
	BOOL bitmapTimeEnable;
	BOOL bitmapTextEnable;
	char bitmapText[129];
	int  bitmapTextX;
	int  bitmapTextY;
};

//��̨���ڲ���
struct param_ptz
{
	unsigned BaudRate;
	unsigned DataBit;
	unsigned Parity;
	unsigned StopBit;
	unsigned Mode;
	unsigned FlowControl;
	char  DecoderType[33];
	char  DecoderAddress[33];
};

struct param_alm_output
{
	int AlmNo;
	int AlmState;
};


//ʱ�����Ϣ
struct param_time_section
{
	int StartHour;
	int StartMinute;
	int EndHour;
	int EndMinute;
};

//��3��ʱ���
struct param_time
{
	param_time_section Time[3];
};

//��8���ʱ�����Ϣ������ÿ��
struct param_period
{
	int errorcode; //0����ʾ���������򣬱�ʾʱ���ַ����Ƿ�
	param_time DayTime[8];
};

struct param_camera_track
{
	char PuID[20];
	int Chno;
	char name[64];

	int preset;
};

struct param_camera
{
	char PuID[20];
	int Chno;
	char name[64];
};

//�ƶ��������
struct param_motion_detection_region
{
	unsigned Sensitivity;
	char Blocks[512];	
};

struct param_almout
{
	int AlmOutputNo;
	int State;
};

struct param_alm_audio_out
{
	int audioOutId;
	BOOL audioAlmEnable;
	int almType;
	char almFile[256];
};

//�澯���ò���
struct param_alarm_enable
{
	char AlmName[64];
	unsigned char almEnable;	//�Ƿ񲼷� 
	param_period period;   	//����ʱ��

	BOOL bReadSecond;	//�澯����ʹ�ܣ�û��
	int ReadSecond;		//�澯���룺û�� 

	BOOL bPuCap;		//ǰ�˱�ͨ���澯ץ��ʹ��
	BOOL bUpload;		//ͼƬ�ϴ���û��
	BOOL bOtherCameraCap;	//��������ͷ����ץ��ʹ�ܣ���������ͨ����
	int CapCameraCount;	//����ץ������ͷ����Ŀ
	param_camera CapCamera[PARAM_ALM_MAX_NUM];	//����ץ������ͷ����ϸ��Ϣ

	BOOL bPuRec;	//ǰ�˱�ͨ���澯¼��ʹ��

	BOOL bOtherCameraPuRec;	//ǰ��������������ͷ¼��ʹ�ܣ���������ͨ����
	int PuRecCameraCount;		//ǰ������¼������ͷ����Ŀ
	param_camera PuRecCamera[PARAM_ALM_MAX_NUM];//ǰ������¼������ͷ����ϸ��Ϣ

	BOOL bPlatformRec;	//ƽ̨��ͨ���澯¼��ʹ��

	BOOL bOtherCameraPlatRec;	//ƽ̨������������ͷ¼��ʹ�ܣ���������ͨ����
	int PlatformRecCameraCount;	//ƽ̨����¼������ͷ����Ŀ
	param_camera PlatformRecCamera[PARAM_ALM_MAX_NUM];//ƽ̨����¼������ͷ����ϸ��Ϣ

	BOOL bAlmOut;	//�澯���ʹ��
	int  AlmOutCount;	//�澯�����Ŀ
	param_almout AlmOutput[PARAM_ALM_MAX_NUM]; //�澯�����ϸ��Ϣ

	BOOL bTrack;	//��ͨ��׷�ٸ澯ʹ��
	int  TrackPreset;	//��ͨ��׷�ٸ澯Ԥ��λ

	BOOL bOtherTrack;	//��������ͷ׷�ٸ澯
	int  OtherTrackCount;	//��������ͷ׷�ٸ澯��Ŀ
	param_camera_track OtherTrack[PARAM_ALM_MAX_NUM];	//����׷�ٸ澯����ͷ��ϸ��Ϣ

	BOOL bIpMatrix;	//�澯����ʹ�ܣ�û��
	char IpMatrix;	//������Ϣ��û��
	int  MatrixNo;	//����ͨ���ţ�û��

	param_alm_audio_out almAudioOut;
};

//����
struct param_region
{
	int x;
	int y;
	int cx;
	int cy;
};

//�ڵ��������
struct param_cover_detection_region
{
	unsigned Sensitivity;
	int RegionCount;
	param_region  Region[16];
};

typedef param_cover_detection_region param_video_hide_region;

//�ڵ��������
struct param_cover_detection
{
	BOOL bEnable;
	char AlmTime[256];
	int x;
	int y;
	int width;
	int height;
	param_alm_output AlmOut[256];   //��һ��Ԫ�ش�����ĳ��ȣ�������Ԫ��
	int AlmRec[256];		//��һ��Ԫ�ش�����ĳ��ȣ�������Ԫ��
};

struct param_lose_detection
{
	BOOL bEnable;
	param_alm_output AlmOut[256];   //��һ��Ԫ�ش�����ĳ��ȣ�������Ԫ��
};

//ץ�Ĳ���
struct param_cap
{
	int capResolution;
	int capQuality;	//ץ������
	int capTimes;	//ץ������(Ƶ��)

	BOOL bTimeCap;
	BOOL bPeriodCap;
	int interval;			//ץ�ļ��
	param_period period;		//����ץ��ʱ��
	char beginTime[32]; 
	char endTime[32];	
};

//ǰ��¼�����
struct param_record
{
	char taskName[32];
	int taskPolicy;
	char mediaFormat[32];
	int mediaType;
	//�� �� �� Сʱ �� �м��ÿո����
	char beginTime[32]; 
	char endTime[32];	
	BOOL bRecAudio;
	BOOL bAlmPreRec;
	int preRecTime;
	BOOL bIframeRec;
	int FrameInterval;
	//�澯�ָ���¼��ʱ��
	unsigned int recTime;  
	char capacityStr[33];
	BOOL bTimeRec;
	BOOL bPeriodRec;
	//����¼��ʱ��
	param_period period;   

	int timespan;
};

struct param_default_preset
{
	int index;
	int interval;
};

struct param_error
{
	int value;
	int errcode;
	int puerr;		//�澯ר��
	int platerr;	//�澯ר��
};

struct param_param
{
	int type;
	
	void * pparam;
	void * plogdata;

	param_error err;
};

typedef int (*moduleparamsetcallback)(int notifycode, int paramtype, void * pparam, long userdata);

PUPARAMSET_API void OutPutString(char * str);
/*��ʼ����������ģ��*/
PUPARAMSET_API int ParamInitial(long * phandle, moduleparamsetcallback callbackfunc, int family);
/*���ٲ�������ģ��*/
PUPARAMSET_API void ParamDestory(long * phandle);

/*��ȡǰ�˸澯���������Ϣ*/
PUPARAMSET_API int ParamGetPuIoInfo(long handle, char * puid, void * userdata, void * plogdata = NULL);

/*�ͻ�ID, name, Ŀ��IP, Э������, Ŀ��ID,ԴID, �ỰID,���,д��dll�б���*/
PUPARAMSET_API void ParamSetInitial(char * cid, char * cname, char * destID, char * sessID, unsigned int seqNum, char * ip, int port, int protocol);

/*puid,chno,chtype, �豸ID��name д��dll�б���*/
PUPARAMSET_API void ParamSetMsgChannel(char * puid, char * name, short chno, unsigned char chtype);

/*���ʹ��ڲ�����������*/
PUPARAMSET_API int ParamSetPuSerialPortReq(long handle,void * lparam , void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPuSerialPortReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*�����������������*/
PUPARAMSET_API int ParamSetInputOutputReq(long handle, void * lparam, int count, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetInputOutputReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*��ȡ�澯�������(�Ӿ�)
almtype:������: 1, 2; ��Ƶ��ʧ: 3, 4; ��Ƶ�ƶ�: 5, 6; ��Ƶ�ڵ�: 101, 102;
*/
PUPARAMSET_API int ParamGetOpAlmOut(long handle,char * puid, int chno, int almtype/*�澯֪ͨ����*/, void * userdata, void * plogdata = NULL);
/*ֹͣ�澯���(�Ӿ�)*/
PUPARAMSET_API int ParamStopAlmOutReq(long handle, void * lparam, int count, void * userdata, void * plogdata = NULL);

/*����������״̬��ѯ*/
PUPARAMSET_API int ParamGetAlmInStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamSetAlmInStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*���������״̬��ѯ*/
PUPARAMSET_API int ParamGetAlmOutStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamSetAlmOutStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*ʱ���������*/
PUPARAMSET_API int ParamSetTimeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetTimeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*��Ƶͼ���������*/
PUPARAMSET_API int ParamSetVideoEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetVideoEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*��Ƶ������������*/
PUPARAMSET_API int ParamSetVideoHideReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetVideoHideReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*��Ƶ��������*/
PUPARAMSET_API int ParamSetAudioEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetAudioEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*��ʾ��������*/
PUPARAMSET_API int ParamSetDisplayReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetDisplayReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ�˴洢����*/
PUPARAMSET_API int ParamSetPuStoreReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPuStoreReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ��¼���������*/
PUPARAMSET_API int ParamSetPuRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPuRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ��¼���������*/
PUPARAMSET_API int ParamSetPlateformRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPlateformRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*������Ļ����*/
PUPARAMSET_API int ParamSetImageTextReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetImageTextReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*�ƶ����������������*/
PUPARAMSET_API int ParamSetMotionRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetMotionRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*�ƶ����澯��������(��������)*/
PUPARAMSET_API int ParamSetMotionAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetMotionAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*�ڵ����������������*/
PUPARAMSET_API int ParamSetCoverRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCoverRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*��Ƶ�ڵ����澯��������(��������)*/
PUPARAMSET_API int ParamSetCoverAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCoverAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*��Ƶ��ʧ���澯��������*/
PUPARAMSET_API int ParamSetLoseAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetLoseAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*�������澯����������*/
PUPARAMSET_API int ParamSetGpinAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetGpinAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*�澯����ץ�Ĳ�����������*/
PUPARAMSET_API int ParamSetCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*Ԥ�õ����� ����ָ��ͨ����Ԥ�õ�*/
PUPARAMSET_API int ParamSetPresetNodeReq(long handle,  char * puid, int chno, int index, char * presetname, char * puname, void * userdata, void * plogdata = NULL);

/*��ȡָ��ͨ��������Ԥ�õ�Ԥ�õ�*/
PUPARAMSET_API int ParamGetPresetNodeReq(long handle,  char * puid, int chno, void * userdata, void * plogdata = NULL);

/*ɾ��ָ��ͨ����ָ��Ԥ�õ�*/
PUPARAMSET_API int ParamDeletePresetNodeReq(long handle,  char * puid, int chno, int index, void * userdata, void * plogdata = NULL);

/*����ͷԤ��λ�Զ���λ*/
PUPARAMSET_API int ParamSetResetReq(long handle, char * puid, int chno, int index, int interval, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetResetReq(long handle, char * puid, int chno, void * userdata, void * plogdata = NULL);

/*Ѳ���켣��������*/
PUPARAMSET_API int ParamSetCruiseReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCruiseReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamDeleteCruiseReq(long handle, int cruiseno, void * userdata, void * plogdata = NULL);

/*ǰ����־����*/
PUPARAMSET_API int ParamGetPuLogReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ�����ò�������*/
PUPARAMSET_API int ParamSetAlmActionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetAlmActionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ�����ø澯����*/
PUPARAMSET_API int ParamSetAlmOpReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetAlmOpReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ʱ��ͬ��*/
PUPARAMSET_API int ParamClockSynchReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*͸��ͨ������*/
PUPARAMSET_API int ParamComTransparentReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ��ץ��(����)*/
PUPARAMSET_API int ParamPuCapPicReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
//PUPARAMSET_API int ParamGetCapPicReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*ǰ��ץ��(����)*/
PUPARAMSET_API int ParamPuCapPicBeginReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamPuCapPicEndReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*��ѯץ��״̬*/
PUPARAMSET_API int ParamGetPuCapPicStatusReq(long handle,  void * lparam, BOOL bManual, void * userdata, void * plogdata = NULL);

/*��ʱץ��*/
PUPARAMSET_API int ParamSetTimeCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetTimeCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);


/*��ѯ�豸״̬*/
PUPARAMSET_API int ParamGetPuDeviceStatusReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
/*Ѳ���켣����*/
PUPARAMSET_API int ParamPtzCallControl(long handle, char* puid, int channelno,int ptztype, int param1, int param2, void * userdata, void * plogdata = NULL);

PUPARAMSET_API bool PeriodIsValid(param_time * pday);

/*ͨ��������������*/
PUPARAMSET_API int ParamSetChannelBaseInfo(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetChannelBaseInfo(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*�ֶ�: ǰ�˺�ƽ̨¼��
#define PLATFORM_MANUAL_REC	//ƽ̨�ֶ�¼��
#define PU_MANUAL_REC			//ǰ���ֶ�¼��
*/
PUPARAMSET_API int ParamManualStartRecordReq(long handle, int type, char * puid, int chno, char * cuid, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamManualStopRecordReq(long handle, int type, char * puid, int chno, char * cuid, void * userdata, void * plogdata = NULL);

/*��ѯ¼��״̬:pu �� platform
#define QUERY_PLATFORM_REC_STATE
#define QUERY_PU_REC_STATE
*/
PUPARAMSET_API int ParamQueryRecordState(long handle, int type, char * puid, char * cuid, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamSendEventResp(long handle, int errcode, void * plogdata = NULL);

/*ǰ���豸�汾�Ų�ѯ*/
PUPARAMSET_API int ParamPuVersionReq(long handle,  char * puid, void * userdata, void * plogdata = NULL);

/*��ȡǰ��״̬*/
PUPARAMSET_API int ParamGetPuStatus(long handle, char * puid, void * userdata, void * plogdata = NULL);

/*������Ƶ��ʾ�����ָ�Ĭ��*/
PUPARAMSET_API int ParamReSetDisplay(long handle, char * puid, int chno, void * userdata, void * plogdata = NULL);

#endif

