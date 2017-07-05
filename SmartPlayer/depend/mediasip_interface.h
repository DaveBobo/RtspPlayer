#ifndef _MEDIASIP_INTERFACE_H
#define _MEDIASIP_INTERFACE_H

#if defined(MEDIASIPDLL_EXPORTS)
#define MEDIASIP_API __declspec(dllexport)
#elif defined(MEDIASIPDLL_IMPORTS)
#define MEDIASIP_API __declspec(dllimport)
#else
#define MEDIASIP_API
#endif

#include "miointerface.h"

#define MEDIASIP_IP_MAXLEN 40
#define MEDIASIP_PUID_MAXLEN 64
#define MEDIASIP_USERID_MAXLEN 64

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * �����롣���ڻص�֪ͨ�ͷ��ʹ����Ӧ��
 */

typedef enum error_code
{
	MS_REQUEST_TIMEOUT = 1,		// ����ʱ
	MS_REQUEST_NORIGHT,			// ����û��Ȩ��
	MS_CALL_CHECK_FAIL,			// �����������ʧ��
	MS_REMOTE_SDP_NULL,			// �յ���200OK��û��Я��SDP
	MS_CALL_LIMIT,				// ���г�������
	MS_UNKNOWN_ERROR,			// δ֪����
	MS_200_OK,					// ��ȷ
	MS_ERROR_CODE_COUNT
}error_code_t;

/*
 * QUERYSTATE_REQ����ʱ�ĻỰ״̬�룬Ŀǰû��ʹ��
 */
typedef enum media_state
{
	MS_NULL_STATE,
	MS_CONNECTING_STATE,
	MS_CONNECTED_STATE,
	MS_DISCONNECTED_STATE,
	MS_STATE_COUNT
}media_state_t;

#ifndef HAVE_STRUCT_SDP_MESSAGE

typedef void sdp_message_t;

#endif


/*
 * ·�ɵĽṹ
 */
#define MS_MAX_ROUTE_IP_LEN			40
typedef struct ms_route_info	ms_route_info_t;
struct ms_route_info
{
	ms_route_info_t		*next;						// ָ����һ��·��
	char				ip[MS_MAX_ROUTE_IP_LEN+1];	// IP��ַ
	unsigned short		port;						// �˿ں�
};

/*
 * ������е���Ϣ�ṹ
 */
typedef struct call_info call_info_t;
struct call_info{
	char			puid[MEDIASIP_PUID_MAXLEN+1];       // SIP To ͷ�е�SIP��ַ���û�������
	char			nexthopip[MEDIASIP_IP_MAXLEN+1];	// SIP To ͷ�е�SIP��ַ��IP��ַ����
	int				nexthopport;						// SIP To ͷ�е�SIP��ַ�Ķ˿ڲ���
	char			usrid[MEDIASIP_USERID_MAXLEN+1];    // SIP From ͷ�е�SIP��ַ���û�������
	sdp_message_t	*sdpinfo;							// SDP��Ϣ�壬��������Ժ���Ӧ�ò��ͷ�
	ms_route_info_t	*route_info;						// ��Ҫ��ӵ�·����Ϣ�б�
														// ��������Ժ���Ӧ�ò��ͷ�
	void			*user_data;							// �ͺ�����ص�Ӧ�ò�����
	char			usrip[MEDIASIP_IP_MAXLEN+1];		// SIP From ͷ�е�SIP��ַ��IP��ַ����
}; 


/*
 * ����mediasip_indicateʱ��Ҫ���Ķ�������
 */
typedef enum ms_indicate_type
{
	QUERYSTATE_REQ,			// ��ѯ����״̬��Ŀǰû��ʵ��
	INVITE_REQ,				// �������
	S200_REQ,				// ������ȷӦ��
	BYE_REQ,				// �Ҷ��Ѿ������ĺ��л���ȡ�������ĺ���
	ERROR_REQ,				// ���ʹ���Ӧ��
	ACK_REQ,				// ����ACK
	INFO_REQ,				// ����INFO
	INFO_ANSWER_REQ,		// ����INFOӦ��
	INDICATE_TYPE_COUNT
}ms_indicate_type_t;

/*
 * ����mediasip_indicate�Ķ����ṹ
 */
typedef struct ms_indicate_info ms_indicate_info_t;
struct ms_indicate_info
{
	ms_indicate_type_t	type;		// ��������
	int					callid;		// ��Ӧ�ĻỰID
									// ��typeΪINVITE_REQʱ�����Ϊ��������������½����Ự��ID
									// ��typeΪ��������ʱ���������Ϊ�����������־֮ǰ�����ĻỰID
	void				*msgbuf;	// ������صĲ���
									// typeΪQUERYSTATE_REQʱ��Ϊָ��media_state�ṹ��ָ�룬Ŀǰû��ʵ��
									// typeΪINVITE_REQʱ��Ϊָ��call_info_t�ṹ��ָ��
									// typeΪS200_REQʱ��Ϊָ��sdp_message_t�ṹ��ָ��
									// typeΪBYE_REQʱ��Ϊ��
									// typeΪERROR_REQʱ��Ϊָ��error_code��ָ��
									// typeΪACK_REQʱ��Ϊָ��sdp_message_t�ṹ��ָ��
	miosMSG				*msg;		// ������ص� XML ��Ϣ�壨����invite,200ok,ackʱ��Ч��
									// ��������Ժ���Ӧ�ò��ͷ�
};


/*
 * ֪ͨ�ص���֪ͨ����
 */
typedef enum ms_notify_type
{
	INVITE_RCV,				// �յ���������
	S200_RCV,				// �յ�200OK
	ACK_RCV,				// �յ�ACK
	BYE_RCV,				// �յ����йҶ�����
	ERROR_RCV,				// ����֪ͨ
	INFO_RCV,				// �յ�INFO
	INFO_ANSWER_RCV,		// �յ�INFOӦ��
	NOTIFY_TYPE_COUNT
}ms_notify_type_t;

/*
 * ֪ͨ�ص���֪ͨ�ṹ������ṹ��֪ͨ�����Ժ���Ҫ����mediasip_notify_info_free�ͷ�
 */
typedef struct ms_notify_info ms_notify_info_t;
struct ms_notify_info
{
	ms_notify_type_t	type;			// ֪ͨ����
	int					callid;			// �ỰID
	void				*msgbuf;		// ��֪ͨ������صĸ�������
										// ��typeΪINVITE_RCVʱ��Ϊָ��sdp_message_t�Ľṹָ��
										// ��typeΪS200_RCVʱ��Ϊָ��sdp_message_t�Ľṹָ��
										// ��typeΪACK_RCVʱ��Ϊָ��sdp_message_t�Ľṹָ��
										// ��typeΪBYE_RCVʱ��Ϊ��
										// ��typeΪERROR_RCV��INFO_ANSWER_RCVʱ��Ϊָ��error_code_t�Ľṹָ��
															// ��typeΪS200_RCVʱ��
	miosMSG				*msg;								// XML��Ϣ�壨�յ�invite,200ok,ack,infoʱ��Ч��
	ms_route_info_t		*route_info;						// ·���б���Ϣ
	char				dstuser[MEDIASIP_PUID_MAXLEN+1];	// SIP To ͷ�е�SIP��ַ���û�������
	char				dstip[MEDIASIP_IP_MAXLEN+1];		// SIP To ͷ�е�SIP��ַ��IP��ַ����
	unsigned short		dstport;							// SIP To ͷ�е�SIP��ַ�Ķ˿ڲ���
	void				*user_data;							// �������������ĻỰ�����ǽ����Ựʱ��Ӧ�ò�����
	char				srcuser[MEDIASIP_PUID_MAXLEN+1];	// SIP From ͷ�е�SIP��ַ���û�������
	char				srcip[MEDIASIP_IP_MAXLEN+1];		// SIP From ͷ�е�SIP��ַ��IP��ַ����
	unsigned short		srcport;							// SIP From ͷ�е�SIP��ַ�Ķ˿ڲ���
};

/*
 * ֪ͨ�ص�����ԭ��
 *
 * �������壺
 *  notifyinfo: ֪ͨ�ص������ݽṹָ�롣��������Ժ���Ҫ����mediasip_notify_info_free�ͷ�
 *
 * ����ֵ��
 *  С�����ʾ����ʧ��
 *  �����ʾ�ɹ�
 *
 */
typedef int (*mediasip_notify_cb_t)(ms_notify_info_t *notifyinfo);

/*
 * ���� OSIP �¼��ܵ�����Ӧ�ò�ʹ�õ��첽֪ͨ�ص�����ԭ��
 *
 * �������壺
 *  evt: ��͸�����û�֪ͨ����
 *
 * ����ֵ��
 *  С�����ʾ����ʧ��
 *  �����ʾ�ɹ�
 *
 */
typedef int (*mediasip_ccm_evt_cb_t)(void *evt);



/*
 * mediasipģ��ĳ�ʼ���ṹ
 */
typedef struct ms_config ms_config_t;
struct ms_config
{
	mediasip_notify_cb_t	ms_notify_cb;	/* callback func for notify */
	mediasip_ccm_evt_cb_t	ms_ccm_evt_cb;	/* callback func for VTDU */

	int		family;/*AF_INET, AF_INET6*/
	int						listen_port;	/* 0 : default 5060 */
	int						protocol;		/* 1 : IPPROTO_TCP;
											 * 2 : TLS;
											 * 0 : default IPPROTO_UDP */
};

/*mediasip basic API*/

/*
 * ��ʼ�� mediasip ģ��
 *
 * �������壺
 *  msconfig: ��ʼ���ṹ
 *
 * ����ֵ��
 *  С�����ʾʧ�ܣ�����-12��ʾ�����˿ں�ʧ��
 *  �����ʾ�ɹ�
 *
 */
MEDIASIP_API int mediasip_initial( ms_config_t *msconfig );

/*
 * ���� mediasip ģ��
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_destroy( void );

/*
 * �ͷ�֪ͨ�ṹ
 *
 * �������壺
 *  notifyinfo: ֪ͨ�ṹָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_notify_info_free( ms_notify_info_t *notifyinfo );

/*
 * ���� mediasip ��������
 *
 * �������壺
 *  indicateinfo: �����ṹָ�룬�����ж��������͡���������Ժ�ṹ�����õ����ڴ涼��Ӧ�ò㸺���ͷ�
 *  param: ����������ΪINVITE_REQʱ���������������ɵĻỰID
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  �����ʾ�ɹ�
 *
 */
MEDIASIP_API int mediasip_indicate( ms_indicate_info_t *indicateinfo, void *param );

/*
 * Ӧ�ò����� OSIP �ܵ����Լ����Ͳ�͸�����첽֪ͨ��
 * ֪ͨͨ���첽֪ͨ�ص��������ء�
 *
 * �������壺
 *  evt: ��͸�����첽֪ͨ�¼�
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  �����ʾ�ɹ�
 *
 */
MEDIASIP_API int fcm_to_ccm_evt_add( void *evt );


/*
 * Ŀǰû��ʵ��
 */
MEDIASIP_API char *mediasip_get_call_caller( int callid );

/*
 * Ŀǰû��ʵ��
 */
MEDIASIP_API char *mediasip_get_call_callee( int callid );

/*
 * �жϸûỰ�Ƿ�ͨ����NAT������ж�δ��׼ȷ
 *
 * �������壺
 *  callid: �ỰID
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  �������ʾû��ͨ��NAT
 *  �������ʾͨ����NAT
 *
 */
MEDIASIP_API int mediasip_if_call_through_nat( int callid );

/*API for operating SDP*/

/*
 * SDP�еķ�������
 */
// ֻ����
#define MEDIASIP_SDP_DIRECTION_SENDONLY		0
// ֻ����
#define MEDIASIP_SDP_DIRECTION_RECVONLY		1
// ͬʱ���ͺͽ���
#define MEDIASIP_SDP_DIRECTION_SENDRECV		2
// û�����÷���
#define MEDIASIP_SDP_DIRECTION_UNKNOWN		3
// ��ȡ�����ʱ��������
#define MEDIASIP_SDP_DIRECTION_ERROR		4

/*
 * ����һ���������SDP�ṹ��ֻ����һЩ�������SDP��Ϣ��û���κ�ý����Ϣ
 *
 * �������壺
 *  sdp: ���������ɵ�sdp��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_build_sdp_message( sdp_message_t **sdp );

/*
 * �ͷ�sdp�ṹʹ�õ��ڴ�
 *
 * �������壺
 *  sdp: ���������ɵ�sdp��
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_sdp_message_free( sdp_message_t *sdp );

/*
 * ����sdp�ṹ
 *
 * �������壺
 *  sdp: ��Ҫ�����Ƶ�sdp
 *  dest: ���������ɵ�sdp��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_clone( sdp_message_t *sdp, sdp_message_t **dest );

/*
 * ��ӡsdp�ṹ
 *
 * �������壺
 *  sdp: ��Ҫ�����Ƶ�sdp
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_dump( sdp_message_t *sdp );

/*
 * ����SDP�� o �ֶε�sessionid��mediasip_build_sdp_message���ɵ�Ĭ��sessionid�� "123456"
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  sessionid: �µ�sessionid
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_session_id( sdp_message_t *sdp, const char *sessionid );

/*
 * ����SDP�� o �ֶκ� c �ֶ� ��ip��
 * �����Щý�����Լ��� c �ֶΣ���ô��Щ�ֶλᱻɾ��
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaip: �µĵ�IP��ַ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_session_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * ����ĳһ��ý��� c �ֶε�ַ�����ý����ڶ�� c �ֶε�ַ���Ὣ���е��ֶζ�ɾ��
 * �� pos_media ���ڻ������ʱ����ʾҪ����ĳһ��ý��ĵ�ַ
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ���������������ý��ĵ�ַ
 * �� pos_media С���㣬����mediaformatҲΪ�գ��ͺ�mediasip_sdp_message_set_session_ipЧ����ͬ
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  mediaip: �µĵ�IP��ַ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_ip_ex( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *mediaip );

/*
 * �������ֻ��Ϊ�˼�����ǰ�Ľӿڣ������Ƽ�ʹ�á�
 * Ч����mediasip_sdp_message_set_session_ip��ͬ
 *
 */
// deprecated interface, please use mediasip_sdp_message_set_session_ip
MEDIASIP_API int mediasip_sdp_message_set_media_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * ��ĳһ��ý����ӵ� c �ֶε�ַ
 * ����SDP����һ���������µ��У�����%֮��Ϊ������Ӧ�Ĳ���ֵ��
 *
 *  c=IN IP4 %mediaip%
 *
 * �� pos_media ���ڻ������ʱ����ʾҪ��ĳһ��ý����� c �ֶε�ַ
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ�������������ý����� c �ֶε�ַ
 * �� pos_media С���㣬����mediaformatҲΪ�գ��ͺ�mediasip_sdp_message_set_session_ipЧ����ͬ
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  mediaip: �µĵ�IP��ַ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_media_ip( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *mediaip );

/*
 * ������Ƶý��ĵ�ַ
 * �൱�ڵ���mediasip_sdp_message_set_media_ip_exʱ��mediaformatΪ"audio"��pos_mediaΪ -1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaip: �µĵ�IP��ַ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * ������Ƶý��ĵ�ַ
 * �൱�ڵ���mediasip_sdp_message_set_media_ip_exʱ��mediaformatΪ"video"��pos_mediaΪ -1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaip: �µĵ�IP��ַ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * ɾ��ĳ��ý��� a �ֶ�
 * �� pos_media ���ڻ������ʱ����ʾҪ��ĳһ��ý����ɾ����Ӧ�� a �ֶ�
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ������������͵�ý����ɾ����Ӧ�� a �ֶ�
 * �� pos_media С���㣬����mediaformatҲΪ�գ�����Ҫ��ȫ���б���ɾ����Ӧ�� a �ֶ�
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  att_field: Ҫ��ɾ���� a �ֶ�������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_attribute_del( sdp_message_t * sdp, const char *mediaformat, int pos_media, const char *att_field );

/*
 * ���ĳ��ý��� a �ֶ�
 * ����SDP����һ���������µ��У�����%֮��Ϊ������Ӧ�Ĳ���ֵ��
 *
 *  a=%att_field%:%att_value%
 *
 * �� pos_media ���ڻ������ʱ����ʾҪ��ĳһ��ý������Ӷ�Ӧ�� a �ֶ�
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ������������͵�ý������Ӷ�Ӧ�� a �ֶ�
 * �� pos_media С���㣬����mediaformatҲΪ�գ�����Ҫ��ȫ���б�����Ӷ�Ӧ�� a �ֶ�
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  att_field: Ҫ����ӵ� a �ֶ�������
 *  att_value: Ҫ����ӵ� a �ֶ�����ֵ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_attribute_add( sdp_message_t * sdp, const char *mediaformat, int pos_media, const char *att_field, const char *att_value );

/*
 * ����ĳ��ý��� a �ֶΣ�����Ѿ�������ͬ�������ֶΣ��Ὣ������ɾ����Ȼ�������
 * �� pos_media ���ڻ������ʱ����ʾҪ����ĳһ��ý���Ӧ�� a �ֶ�
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ���������������ý��� a �ֶ�
 * �� pos_media С���㣬����mediaformatҲΪ�գ�����Ҫ����ȫ���б��ж�Ӧ�� a �ֶ�
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  att_field: Ҫ�����õ� a �ֶ�������
 *  att_value: Ҫ�����õ� a �ֶ�����ֵ
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_attribute_set( sdp_message_t * sdp, const char *mediaformat, int pos_media, const char *att_field, const char *att_value );

/*
 * ����ĳ��ý������ݷ��ͷ���
 * �������������ʱ����Ƚ����е�ָʾ�����ֶ�ɾ����Ȼ������µ��ֶ�
 *
 * ��directionΪMEDIASIP_SDP_DIRECTION_SENDONLYʱ����������ֶ�
 *
 *  a=sendonly
 *
 * ��directionΪMEDIASIP_SDP_DIRECTION_RECVONLYʱ����������ֶ�
 *
 *  a=recvonly
 *
 * ��directionΪMEDIASIP_SDP_DIRECTION_SENDRECVʱ����������ֶ�
 *
 *  a=sendrecv
 *
 * ��directionΪMEDIASIP_SDP_DIRECTION_UNKNOWNʱ��ָʾ�����еķ����ֶ�ɾ�����������
 *
 *
 * �� pos_media ���ڻ������ʱ����ʾҪ����ĳһ��ý������ݷ��ͷ���
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ���������������ý������ݷ��ͷ���
 * �� pos_media С���㣬����mediaformatҲΪ�գ�����Ҫ����ȫ�ֵ����ݷ��ͷ���
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  direction: ý�����ݵķ��ͷ���
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_direction( sdp_message_t *sdp, const char *mediaformat, int pos_media, int direction );

/*
 * ������Ƶ���ݵķ��ͷ���
 * �൱�ڵ���mediasip_sdp_message_set_media_directionʱ��meidaformatΪ"audio"��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  direction: ý�����ݵķ��ͷ���
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_direction( sdp_message_t *sdp, int direction );

/*
 * ������Ƶ���ݵķ��ͷ���
 * �൱�ڵ���mediasip_sdp_message_set_media_directionʱ��meidaformatΪ"video"��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  direction: ý�����ݵķ��ͷ���
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_direction( sdp_message_t *sdp, int direction );

/*
 * ����ĳ��ý������ݵĶ˿ں�
 * �����������ֻ�Ǹ��������ֶ��еĶ˿ں�ֵ��%port%���֣�
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list%
 *
 * �� pos_media ���ڻ������ʱ����ʾҪ����ĳһ��ý��Ķ˿ں�
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ���������������ý��Ķ˿ں�
 * �� pos_media С���㣬����mediaformatҲΪ�գ��᷵��ʧ��
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  port: ý�����ݵĶ˿ں�
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_port( sdp_message_t *sdp, const char *mediaformat, int pos_media, int port );

/*
 * ������Ƶ�����ݶ˿ں�
 * �൱�ڵ���mediasip_sdp_message_set_media_portʱ��meidaformatΪ"audio"��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ý�����ݵĶ˿ں�
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_port( sdp_message_t *sdp, int port );

/*
 * ������Ƶ�����ݶ˿ں�
 * �൱�ڵ���mediasip_sdp_message_set_media_portʱ��meidaformatΪ"video"��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ý�����ݵĶ˿ں�
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_port( sdp_message_t *sdp, int port );

/*
 * ����ĳ��ý������ݵĳ���Э��
 * �����������ֻ�Ǹ��������ֶ��е�Э���ֶΣ�%protocol%���֣�
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list%
 *
 * �� pos_media ���ڻ������ʱ����ʾҪ����ĳһ��ý���Э���ֶ�
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ���������������ý���Э���ֶ�
 * �� pos_media С���㣬����mediaformatҲΪ�գ��᷵��ʧ��
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  protocol: Ҫ���õ�Э��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_protocol( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *protocol );

/*
 * ������Ƶ�ĳ���Э��
 * �൱�ڵ���mediasip_sdp_message_set_media_protocolʱ��meidaformatΪ"audio"��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  protocol: Ҫ���õ�Э��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_protocol( sdp_message_t *sdp, const char *protocol );

/*
 * ������Ƶ�ĳ���Э��
 * �൱�ڵ���mediasip_sdp_message_set_media_protocolʱ��meidaformatΪ"video"��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  protocol: Ҫ���õ�Э��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_protocol( sdp_message_t *sdp, const char *protocol );

/*
 * ��ĳ��ý������ӵ����ݰ�����
 * �����������Ҫ��m�ֶ�������һ��%payload_type%���������Ӻ����payload_type��ص����Ա�
 *
 * ��
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list%
 * ���
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list% %payload_type%
 * ��������attrs�е�ֵ��������µ��ֶ�
 *   a=%attrs[0]%:%attrs[1]%
 *   a=%attrs[2]%:%attrs[3]%
 *   ...
 *
 * �� pos_media ���ڻ������ʱ����ʾҪ��ĳһ��ý����������ݰ�����
 * �� pos_media С���㣬��mediaformat��Ϊ�գ���ʾҪ������������͵�ý����������ݰ�����
 * �� pos_media С���㣬����mediaformatҲΪ�գ��᷵��ʧ��
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  payload_type: Ҫ��ӵ����ݰ�����
 *  attrs: �����payload_type��صĸ�������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_media_payload( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *payload_type, const char **attrs );

/*
 * ���һ����Ƶ���ݰ�����
 *
 * ��
 *   m=audio %port% %protocol% %old_payload_type_list%
 * ���
 *   m=audio %port% %protocol% %old_payload_type_list% %payload_type%
 * ��������µ��ֶ�
 *   a=rtpmap:%a_rtpmap%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  payload_type: Ҫ��ӵ����ݰ�����
 *  a_rtpmap: rtpmap����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_payload( sdp_message_t *sdp, const char *payload_type, const char *a_rtpmap );

/*
 * ���һ����Ƶ���ݰ�����
 *
 * ��
 *   m=video %port% %protocol% %old_payload_type_list%
 * ���
 *   m=video %port% %protocol% %old_payload_type_list% %payload_type%
 * ��������µ��ֶ�
 *   a=rtpmap:%a_rtpmap%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  payload_type: Ҫ��ӵ����ݰ�����
 *  a_rtpmap: rtpmap����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_payload( sdp_message_t *sdp, const char *payload_type, const char *a_rtpmap, const char *a_fmtp );

/*
 * ���һ��ý��
 * ����������ֶ�
 *
 *   m=%mediaformat% %port% %protocol%
 *   a=%attrs[0]%:%attrs[1]%
 *   a=%attrs[2]%:%attrs[3]%
 *   ...
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  port: ý������ʹ�õĶ˿ں�
 *  protocol: ý������ʹ�õ�Э������
 *  attrs: ���ӵ�ý���������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_media( sdp_message_t *sdp, const char *mediaformat, int port, const char *protocol, const char **attrs );

/*
 * ���һ����Ƶ
 * ����������ֶ�
 *
 *   m=audio %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=( sendonly �� recvonly �� sendrecv )
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ʹ�õĶ˿ں�
 *  payload_type: ���ݰ���ʽ
 *  a_rtpmap: rtpmap ����
 *  protocol: ʹ�õ�Э������
 *  direction: ���͵ķ���
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_media_ex2( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *protocol, int direction );

/*
 * ���һ����Ƶ
 * ����������ֶ�
 *
 *   m=audio %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ʹ�õĶ˿ں�
 *  payload_type: ���ݰ���ʽ
 *  a_rtpmap: rtpmap ����
 *  protocol: ʹ�õ�Э������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_media_ex( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *protocol );

/*
 * ���һ����Ƶ
 * ����������ֶ�
 *
 *   m=audio %port% RTP/AVP %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ʹ�õĶ˿ں�
 *  payload_type: ���ݰ���ʽ
 *  a_rtpmap: rtpmap ����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_media( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap );

/*
 * ���һ����Ƶ
 * ����������ֶ�
 *
 *   m=video %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=fmtp:%a_fmtp%
 *   a=framerate:%framerate%
 *   a=( sendonly �� recvonly �� sendrecv )
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ʹ�õĶ˿ں�
 *  payload_type: ���ݰ���ʽ
 *  a_rtpmap: rtpmap ����
 *  a_fmtp: fmtp ����
 *  protocol: ʹ�õ�Э������
 *  framerate: ֡��
 *  direction: ���͵ķ���
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_media_ex2( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *a_fmtp, const char *protocol, const char *framerate, int direction );

/*
 * ���һ����Ƶ
 * ����������ֶ�
 *
 *   m=video %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=fmtp:%a_fmtp%
 *   a=framerate:%framerate%
 *   a=( sendonly �� recvonly �� sendrecv )
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ʹ�õĶ˿ں�
 *  payload_type: ���ݰ���ʽ
 *  a_rtpmap: rtpmap ����
 *  a_fmtp: fmtp ����
 *  protocol: ʹ�õ�Э������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_media_ex( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *a_fmtp, const char *protocol );

/*
 * ���һ����Ƶ
 * ����������ֶ�
 *
 *   m=video %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=fmtp:%a_fmtp%
 *   a=framerate:%framerate%
 *   a=( sendonly �� recvonly �� sendrecv )
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  port: ʹ�õĶ˿ں�
 *  payload_type: ���ݰ���ʽ
 *  a_rtpmap: rtpmap ����
 *  a_fmtp: fmtp ����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_media( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *a_fmtp );




/*
 * ��� SDP �е� sessionid����Ӧ�� O �ֶ��е� %sessionid%
 *
 *   o=MediaSIP %sessionid% 0 IN IP4 10.18.34.75
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص�sessionid
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_session_id( sdp_message_t *sdp );

/*
 * ��� SDP �е� ip����Ӧ��ȫ�ֵ�c�ֶ��е� %ip%
 *
 *   c=IN IP4 %ip%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص� ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_session_ip( sdp_message_t *sdp );

/*
 * ���ĳ��ý����ص� c �ֶ��е� %ip%
 * �����Ӧ�� c �ֶ�û���ҵ�����ô�᷵��ȫ�ֵ� c �ֶ��е� %ip%
 *
 *   c=IN IP4 %ip%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  pos_conn: c �ֶε����
 *
 * ����ֵ��
 *  ���ص� ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_media_ip_ex( sdp_message_t *sdp, const char *mediaformat, int pos_media, int pos_conn );


/*
 * ��ͬ�� mediasip_sdp_message_get_session_ip�����Ƽ�ʹ���������
 * ��� SDP �е� ip����Ӧ��ȫ�ֵ�c�ֶ��е� %ip%
 *
 *   c=IN IP4 %ip%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص� ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_media_ip( sdp_message_t *sdp );

/*
 * �����Ƶý��� ip
 * �൱�ڵ��� mediasip_sdp_message_get_media_ip_ex ʱ mediaformatΪ"audio"��pos_media��pos_conn��Ϊ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص� ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_audio_ip( sdp_message_t *sdp );

/*
 * �����Ƶý��� ip
 * �൱�ڵ��� mediasip_sdp_message_get_media_ip_ex ʱ mediaformatΪ"video"��pos_media��pos_conn��Ϊ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص� ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_video_ip( sdp_message_t *sdp );

/*
 * ���ĳ��ý��Ķ˿ںţ���Ӧ�����ֶε� %port% ����
 *
 *   m=%mediaformat% %port% %protocol% %payload_type_list%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *
 * ����ֵ��
 *  ���صĶ˿ں�
 *  С�����ʾ��ȡʧ��
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_media_port( sdp_message_t *sdp, const char *mediaformat, int pos_media );

/*
 * �����Ƶ�˿ں�
 * �൱�ڵ��� mediasip_sdp_message_get_media_port ʱ��mediaformatΪ"audio"��pos_mediaΪ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���صĶ˿ں�
 *  С�����ʾ��ȡʧ��
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_port( sdp_message_t *sdp );

/*
 * �����Ƶ�˿ں�
 * �൱�ڵ��� mediasip_sdp_message_get_media_port ʱ��mediaformatΪ"video"��pos_mediaΪ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���صĶ˿ں�
 *  С�����ʾ��ȡʧ��
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_port( sdp_message_t *sdp );

/*
 * ���ĳ��ý���Э�����ͣ���Ӧ�����ֶε� %protocol% ����
 *
 *   m=%mediaformat% %port% %protocol% %payload_type_list%
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý���ʽ����"audio"��"video"�ȵ�
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *
 * ����ֵ��
 *  ���ص�Э������
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_media_protocol( sdp_message_t *sdp, const char *mediaformat, int pos_media );

/*
 * �����ƵЭ������
 * �൱�ڵ��� mediasip_sdp_message_get_media_protocol ʱ��mediaformatΪ"audio"��pos_mediaΪ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص�Э������
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_audio_protocol( sdp_message_t *sdp );

/*
 * �����ƵЭ������
 * �൱�ڵ��� mediasip_sdp_message_get_media_protocol ʱ��mediaformatΪ"video"��pos_mediaΪ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص�Э������
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_video_protocol( sdp_message_t *sdp );

/*
 * ���ĳ��ý�����ݰ���ص�����ֵ
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý������
 *  pos_media: ý�����š��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  payload_index: ���ݰ�������ţ��������mediaformat��pos_media�޶���ý�塣
 *                 ���pos_media���ڻ����0����ô����������ý������ݰ��������
 *                 ���pos_mediaС��0������mediaformat��Ϊ�գ���ô���������һ��ý������ݰ��������
 *                 ���pos_mediaС��0������mediaformatҲΪ�գ���ô�ͱ�ʾ������ý���е����ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  att_field: Ҫ��õ����ݰ�������ԣ��� rtpmap��fmtp�ȵ�
 *
 * ����ֵ��
 *  ���ص�����ֵ
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_payload_attribute_ex( sdp_message_t *sdp, const char *mediaformat, int pos_media, int payload_index, const char **payload_type, const char *att_field );

/*
 * ���ĳ��ý�����ݰ���ص�����ֵ
 * ��������൱�ڵ���mediasip_sdp_message_get_payload_attribute_exʱ��pos_mediaΪ-1
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý������
 *  payload_index: ���ݰ�������ţ��������mediaformat�޶���ý�塣
 *                 ���mediaformat��Ϊ�գ���ô���������һ��ý������ݰ��������
 *                 ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  att_field: Ҫ��õ����ݰ�������ԣ��� rtpmap��fmtp�ȵ�
 *
 * ����ֵ��
 *  ���ص�����ֵ
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_payload_attribute( sdp_message_t *sdp, const char *mediaformat, int payload_index, const char **payload_type, const char *att_field );

/*
 * �����Ƶ�������
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  pos_audio: ��Ƶý�����ţ�������ڻ�����㣬��ô��ʾpayload_index�������ý���е����
 *  payload_index: ��Ƶ���ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  a_rtpmap: ���ص�rtpmap����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_codec_ex( sdp_message_t *sdp, int pos_audio, int payload_index, const char **payload_type, const char **a_rtpmap );

/*
 * �����Ƶ�������
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  payload_index: ��Ƶ���ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  a_rtpmap: ���ص�rtpmap����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_codec( sdp_message_t *sdp, int payload_index, const char **payload_type, const char **a_rtpmap );

/*
 * �����Ƶ�������
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  pos_video: ��Ƶý�����ţ�������ڻ�����㣬��ô��ʾpayload_index�������ý���е����
 *  payload_index: ��Ƶ���ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  a_rtpmap: ���ص� rtpmap ����
 *  a_fmtp: ���ص� fmtp ����
 *  a_framerate: ���ص�֡��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_codec_ex2( sdp_message_t *sdp, int pos_video, int payload_index, const char **payload_type, const char **a_rtpmap, const char **a_fmtp, const char **a_framerate );

/*
 * �����Ƶ�������
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  payload_index: ��Ƶ���ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  a_rtpmap: ���ص� rtpmap ����
 *  a_fmtp: ���ص� fmtp ����
 *  a_framerate: ���ص�֡��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_codec_ex( sdp_message_t *sdp, int payload_index, const char **payload_type, const char **a_rtpmap, const char **a_fmtp, const char **a_framerate );

/*
 * �����Ƶ�������
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  payload_index: ��Ƶ���ݰ��������
 *  payload_type: ���ص����ݰ�����
 *  a_rtpmap: ���ص� rtpmap ����
 *  a_fmtp: ���ص� fmtp ����
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_codec( sdp_message_t *sdp, int payload_index, const char **payload_type, const char **a_rtpmap, const char **a_fmtp );

/*
 * ���ĳ��ý������ֵ
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý������
 *  pos_media: ������ţ��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *  att_field: Ҫ��õ����ݰ�������ԣ��� rtpmap��fmtp�ȵ�
 *  pos: ���Ե���ţ�������Կ���Я���Ķ����ͬ������������
 *
 * ����ֵ��
 *  ���ص�����ֵ
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_attribute_get_value( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *att_field, int pos );

/*
 * ���ȫ�ֵ�ý�崫�ͷ���
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���صķ���ֵ
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_session_direction( sdp_message_t *sdp );

/*
 * ���ĳ��ý��Ĵ��ͷ���
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  mediaformat: ý������
 *  pos_media: ������ţ��������mediaformat��ý�塣
 *             ���mediaformatΪ�գ���ô�ͱ�ʾ������ý���е����
 *
 * ����ֵ��
 *  ���صķ���ֵ
 *  MEDIASIP_SDP_DIRECTION_SENDONLY��ʾֻ����
 *  MEDIASIP_SDP_DIRECTION_RECVONLY��ʾֻ����
 *  MEDIASIP_SDP_DIRECTION_SENDRECV��ʾͬʱ���ͺͽ���
 *  MEDIASIP_SDP_DIRECTION_UNKNOWN��ʾû�����÷���
 *  MEDIASIP_SDP_DIRECTION_ERROR��ʾ��ȡ�����ʱ��������ͨ������Ϊָ����ý�岻����
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_media_direction( sdp_message_t *sdp, const char *mediaformat, int pos_media );

/*
 * �����Ƶ�Ĵ��ͷ���
 * �൱�ڵ��� mediasip_sdp_message_get_media_direction ʱ��mediaformatΪ"audio"��pos_mediaΪ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���صķ���ֵ
 *  MEDIASIP_SDP_DIRECTION_SENDONLY��ʾֻ����
 *  MEDIASIP_SDP_DIRECTION_RECVONLY��ʾֻ����
 *  MEDIASIP_SDP_DIRECTION_SENDRECV��ʾͬʱ���ͺͽ���
 *  MEDIASIP_SDP_DIRECTION_UNKNOWN��ʾû�����÷���
 *  MEDIASIP_SDP_DIRECTION_ERROR��ʾ��ȡ�����ʱ��������ͨ������Ϊָ����ý�岻����
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_direction( sdp_message_t *sdp );

/*
 * �����Ƶ�Ĵ��ͷ���
 * �൱�ڵ��� mediasip_sdp_message_get_media_direction ʱ��mediaformatΪ"video"��pos_mediaΪ0
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���صķ���ֵ
 *  MEDIASIP_SDP_DIRECTION_SENDONLY��ʾֻ����
 *  MEDIASIP_SDP_DIRECTION_RECVONLY��ʾֻ����
 *  MEDIASIP_SDP_DIRECTION_SENDRECV��ʾͬʱ���ͺͽ���
 *  MEDIASIP_SDP_DIRECTION_UNKNOWN��ʾû�����÷���
 *  MEDIASIP_SDP_DIRECTION_ERROR��ʾ��ȡ�����ʱ��������ͨ������Ϊָ����ý�岻����
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_direction( sdp_message_t *sdp );


/*
 * ��SDP�ṹת����ԭʼ�ı�
 * 
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  buf: ���sdp�ı��Ļ��������ṩ�Ļ������Ĵ�С������ڻ����sdp���ı����ȼ�һ
 *  buf_len: �������ĳ���
 *
 * ����ֵ��
 *  С�����ʾ���������Ȳ�����ȡ���෴��Ϊsdp�ı��ĳ��ȣ���������ȼ�һ������Ҫ�����ٻ���������
 *  �������ʾ�ɹ�������sdp�ı��ĳ���
 *  �������ʾsdp�ı��ĳ���Ϊ0��������ζ��ĳ��ʧ��
 *
 */
MEDIASIP_API int mediasip_sdp_message_to_str( sdp_message_t *sdp, char *buf, int buf_len );

/*
 * ����SDP�ı�
 *
 * �������壺
 *  sdp_buf: Ҫ�������� sdp �ı�
 *
 * ����ֵ��
 *  �����õ���sdp�ṹ
 *
 */
MEDIASIP_API sdp_message_t* mediasip_sdp_message_parse( const char *sdp_buf );


/*
 * ����֡�ʡ���Ϊ�ӿڲ���ȷ��Ϊ����֮ǰ�汾�������ģ����Ƽ�ʹ��
 * �������ú󣬻�����е���Ƶý�����framerate����
 * 
 *
 * �������壺
 *  sdp: sdp�ṹ
 *  framerate: �µ�֡��
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
// deprecated interface
MEDIASIP_API int mediasip_sdp_message_set_a_framerate( sdp_message_t *sdp, const char *framerate );

/*
 * ���֡�ʡ���Ϊ�ӿڲ���ȷ��Ϊ����֮ǰ�汾�������ģ����Ƽ�ʹ��
 * �������ú󣬷��ص��ǵ�һ����Ƶý���framerate����
 *
 * �������壺
 *  sdp: sdp�ṹ
 *
 * ����ֵ��
 *  ���ص�framerate����ֵ
 *
 */
// deprecated interface
MEDIASIP_API const char* mediasip_sdp_message_get_a_framerate( sdp_message_t *sdp );


/*API for setting mediasip profile*/

/*
 * ���ÿɽ��յ����ý���������Ĭ��Ϊ500
 *
 * �������壺
 *  num: �ɽ��յ����ý�������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_set_max_incoming_calls(int num);

/*
 * ���ÿɷ��͵����ý���������Ĭ��Ϊ500
 *
 * �������壺
 *  num: �ɽ��յ����ý�������
 *
 * ����ֵ��
 *  С�����ʾʧ��
 *  ����Ϊ�ɹ�
 *
 */
MEDIASIP_API int mediasip_set_max_outgoing_calls(int num);

/*
 * ����NAT�˿ڵ�ˢ��ʱ�䡣
 * �����ֺ��д�Խ��NAT���������ʱ�����ڷ������ݰ�ˢ��NAT��
 * Ĭ��û��ʹ�ܡ�
 *
 * �������壺
 *  interval: NAT��ˢ�¼��������Ϊ��λ��С��30����Ϊ��30
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_set_nat_port_refresh_interval(int interval); /*interval: s */

/*
 * ���ú�������������ʱ�䡣
 * �����͵�3����������û�л�Ӧʱ���ͱ�ʾ�Ự�Ѿ��Ͽ������ͷŲ�֪ͨӦ�ò㡣
 * Ĭ��û��ʹ�ܡ�
 *
 * �������壺
 *  interval: ������ˢ��ʱ����
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_set_call_keep_alive_interval(int interval);   /*interval: s */

/*API for pinrting mediasip info*/

/*
 * ���õ��Ը��ټ���
 *
 * �������壺
 *  level: ���Ը��ټ���
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_set_trace_level(int level);

/*
 * ����Ļ�ϴ�ӡ�ڴ���Ϣ��Ŀǰû����
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_print_mem_info();

/*
 * ����Ļ�ϴ�ӡ�ڴ���ϸ��Ϣ��Ŀǰû����
 *
 */
MEDIASIP_API void mediasip_print_mem_detail_info(int n,int start, int num);

/*
 * ����Ļ�ϴ�ӡmediasipЭ��ջ��ʹ�õ�һЩ��Դ���
 * ��Ϊû��ά����Ŀǰ��Ҳ�������ӡ��һЩʲô��:)
 *
 * �������壺
 *  level: ��ӡ����
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_resource_print(int level);

#ifdef MEDIASIP_DEBUG

MEDIASIP_API void mediasip_event_static_print();

MEDIASIP_API void mediasip_event_static_clean();

#endif

/*api for route info */

/*
 * ����һ��route�ڵ�
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  �����ɵ�route�ڵ�
 *
 */
MEDIASIP_API ms_route_info_t* mediasip_new_route_info( void );

/*
 * �ͷ�һ��route�ڵ�
 *
 * �������壺
 *  route_info: ��Ҫ���ͷŵ�route�ڵ�
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_free_route_info( ms_route_info_t *route_info );

/*
 * �ͷ�route�ڵ��б�
 *
 * �������壺
 *  route_info_list: ��Ҫ���ͷŵ�route�ڵ��б�
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_free_route_info_list( ms_route_info_t *route_info_list );

/*
 * ����route�ڵ�
 *
 * �������壺
 *  src: ��Ҫ�����Ƶ�route�ڵ��б�
 *
 * ����ֵ��
 *  �����ɵ�route�ڵ��б�
 *
 */
MEDIASIP_API ms_route_info_t* mediasip_clone_route_info( ms_route_info_t *src );

/*
 * ����route�ڵ��б�
 *
 * �������壺
 *  src: ��Ҫ�����Ƶ�route�ڵ��б�
 *
 * ����ֵ��
 *  �����ɵ�route�ڵ��б�
 *
 */
MEDIASIP_API ms_route_info_t* mediasip_clone_route_info_list( ms_route_info_t *src );

/* for disable auto ack */
/*
 * ȡ��mediasip�Զ���Ӧ ACK �Ĺ��ܣ���Ҫ������Ҫ�� ACK ��Я��SDP�ĻỰ
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ��
 *
 */
MEDIASIP_API void mediasip_disable_auto_ack( void );

#ifdef __cplusplus
}
#endif

#endif


