/**
 *  File Name                   :           miointerface.h
 *  Version                     :           1.0
 *  Project Information         :           MegaEye
 *  Copyright                   :
 *  Brief Description           :           header file for MIO interface
 *=================================================================================
 *  Revision History            :
 *
 */

#ifndef _MIOINTERFACE_H_
#define _MIOINTERFACE_H_

#include <stdarg.h>

#include "msgdef.h"
#include "iedef.h"


#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////
//	�û��Զ�����Ϣ��ز��֣�û����ȫ���
///////////////////////////////////////////////////////

/*
 * �û��Զ�����Ϣ����ṹ
 */
typedef struct miosUserMsgDef{
	MIO_CONST MIO_CHAR		*name;		// ��Ϣ��
	MIO_INT32				nameLen;	// ��Ϣ���ĳ���
	MIO_UINT32				type;		// ��Ϣ���ֵ
}miosUserMsgDef;

/*
 * �û��Զ���IE��Ա������������
 */
typedef enum mioeUserIEMemberType{
	MIO_IMT_INT8,			// for char
	MIO_IMT_UINT8,			// for byte
	MIO_IMT_INT16,			// for short
	MIO_IMT_UINT16,			// for word
	MIO_IMT_INT32,			// for int
	MIO_IMT_UINT32,			// for dword
	MIO_IMT_INT64,			// for int64
	MIO_IMT_UINT64,			// for qword

	MIO_IMT_STRING,			// for string
	MIO_IMT_TIME,			// time
	MIO_IMT_UNKNOWN
}mioeUserIEMemberType;

/*
 * �û��Զ���IE��Ա������ṹ
 */
typedef struct miosUserIEMemberDef{
	MIO_CONST MIO_CHAR		*name;				// ��Ա������
	MIO_INT32				nameLen;			// ��Ա�������ĳ���
	MIO_UINT32				offset;				// ��Ա������IE�е��ڴ�ƫ����
	mioeUserIEMemberType	type;				// ��Ա������ֵ����
	MIO_UINT32				extraParam;			// ��Ա������Ҫ�ĸ��Ӳ���
												// �ַ�������ʹ��������¼��󳤶�
	MIO_CONST MIO_CHAR		*defaultValue;		// ��Ա������Ĭ��ֵ
}miosUserIEMemberDef;

/*
 * �û��Զ���IE����ṹ
 */
typedef struct miosUserIEDef{
	MIO_CONST MIO_CHAR				*name;			// IE��
	MIO_INT32						nameLen;		// IE���ĳ���
	MIO_UINT32						type;			// IE�ı��ֵ
	MIO_UINT32						size;			// IE�ṹ�Ĵ�С
	MIO_CONST miosUserIEMemberDef	*memberDefs;	// IE�ĳ�Ա�б�
													// Ϊһ�����飬��β�ĽṹΪ0
}miosUserIEDef;

/*
 * �û��Զ�����ص�һЩ�궨�壬��ϸ�Ĳμ������ƽӿ���ϸ���˵���顷
 */
#define MIO_USER_MSG_DEFINE_NAME( suffixName )					g_MIOUserMsgDef_##suffixName
#define MIO_USER_IE_DEFINE_NAME( suffixName )					g_MIOUserIEDef_##suffixName
#define MIO_USER_IE_MEMBER_DEFINE_NAME( ieName )				g_MIOUserIEMemberDef_##ieName
#define MIO_USER_IE_MEMBER_NAME( memberName )					m_##memberName
#define MIO_USER_IE_STRUCT_NAME( ieName )						mios##ieName
#define MIO_STRUCT_MEMBER_OFFSET( structName, memberName )		MIO_PTR_TO_INT(&(((structName*)0)->memberName))
#define MIO_USER_MSG_TYPE_DEFINE_NAME( suffixName )				mioeUserMSGType_##suffixName
#define MIO_USER_IE_TYPE_DEFINE_NAME( suffixName )				mioeUserIEType_##suffixName
#define MIO_USER_MSG_TYPE_NAME( msgName )						MT_##msgName
#define MIO_USER_IE_TYPE_NAME( ieName )							IET_##ieName

#define MIO_BEGIN_USER_MSG_TYPE_DEFINE( suffixName )			typedef enum MIO_USER_MSG_TYPE_DEFINE_NAME( suffixName ){
#define MIO_DEFINE_USER_MSG_TYPE( msgName, type )				MIO_USER_MSG_TYPE_NAME( msgName ) = type,
#define MIO_END_USER_MSG_TYPE_DEFINE( suffixName )				MT_UNKNOW_USER_MSG = 0xffffffff }MIO_USER_MSG_TYPE_DEFINE_NAME( suffixName );

#define MIO_BEGIN_USER_IE_TYPE_DEFINE( suffixName )				typedef enum MIO_USER_IE_TYPE_DEFINE_NAME( suffixName ){
#define MIO_DEFINE_USER_IE_TYPE( ieName, type )					MIO_USER_IE_TYPE_NAME( ieName ) = type,
#define MIO_END_USER_IE_TYPE_DEFINE( suffixName )				IET_UNKNOW_USER_IE = 0xffffffff }MIO_USER_IE_TYPE_DEFINE_NAME( suffixName );

#define MIO_BEGIN_USER_MSG_DEFINE( suffixName )					miosUserMsgDef MIO_USER_MSG_DEFINE_NAME(suffixName)[] = {
#define MIO_DEFINE_USER_MSG( msgName, type )					{ #msgName, sizeof(#msgName)-1, type },
#define MIO_END_USER_MSG_DEFINE( suffixName )					{ MIO_NULL, 0, 0 } };

#define MIO_BEGIN_USER_IE_MEMBER_DEFINE( ieName )				miosUserIEMemberDef MIO_USER_IE_MEMBER_DEFINE_NAME(ieName)[] = {
#define MIO_DEFINE_USER_IE_MEMBER( ieName, memberName, type, extraParam, defaultValue )		\
																{ #memberName, sizeof(#memberName)-1, MIO_STRUCT_MEMBER_OFFSET( MIO_USER_IE_STRUCT_NAME( ieName ), MIO_USER_IE_MEMBER_NAME(memberName) ), MIO_IMT_##type, extraParam, defaultValue },
#define MIO_END_USER_IE_MEMBER_DEFINE( ieName )					{ MIO_NULL, 0, 0, 0, 0, MIO_NULL } };

#define MIO_BEGIN_USER_IE_STRUCT_DEFINE( ieName )							typedef struct MIO_USER_IE_STRUCT_NAME( ieName ){	\
																				MIO_UINT32 type;
#define MIO_DEFINE_USER_IE_STRUCT_MEMBER( ieName, memberName, type )			MIO_##type MIO_USER_IE_MEMBER_NAME(memberName);
#define MIO_DEFINE_USER_IE_STRUCT_MEMBER_STRING( ieName, memberName, len )		MIO_CHAR MIO_USER_IE_MEMBER_NAME(memberName)[len+1];
#define MIO_END_USER_IE_STRUCT_DEFINE( ieName )								}MIO_USER_IE_STRUCT_NAME( ieName );

#define MIO_BEGIN_USER_IE_DEFINE( suffixName )			miosUserIEDef MIO_USER_IE_DEFINE_NAME(suffixName)[] = {
#define MIO_DEFINE_USER_IE( ieName, type )				{ #ieName, sizeof(#ieName)-1, type, sizeof(MIO_USER_IE_STRUCT_NAME( ieName )), MIO_USER_IE_MEMBER_DEFINE_NAME( ieName ) },
#define MIO_END_USER_IE_DEFINE( suffixName )			{ MIO_NULL, 0, 0, 0, MIO_NULL } };


/*
 * ��Ч����ϢID
 */
#define MIO_INVALID_MSGID		0

/*
 * MIO_NotifyHandler�Ļص�֪ͨ����
 */
typedef enum mioeNotiyCode
{
	MIO_NC_RECV_REQUEST,		// �յ���һ���������ݰ�
	MIO_NC_RECV_RESPONSE,		// �յ���һ��Ӧ�����ݰ�
	MIO_NC_SND_REQUEST_FAIL,	// �����������ݰ�ʧ��
	MIO_NC_RECV_REGISTER,		// �յ���һ��ע�������
	MIO_NC_RECV_REGISTER_RESP,	// �յ���һ���ɹ���ע���Ӧ��
	MIO_NC_SND_REGISTER_FAIL,	// ����ע������ʧ��
	MIO_NC_ACCEPT_REGISTER,		// ������һ������֤��ע������
	MIO_NC_REGISTER_TIMEOUT		// ����ע����Ϣ��ʱ
}mioeNotiyCode;

/*
 * linux�µ��ϲ�ģ��ʵ�ֵĻص�֪ͨ����
 * ����������ֵ���ص�����ԭ�Ͷ��崦��˵��
 */
extern MIO_VOID MIO_NotifyHandler(MIO_VOID *userData,
									mioeNotiyCode notifyCode,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_VOID *notifyExtraParam);

/*
 *	�� notifyCode Ϊ MIO_NC_RECV_REGISTER �� MIO_NC_ACCEPT_REGISTER ʱ
 *	notifyExtraParam Ϊָ�����½ṹ��ָ��
 */
typedef struct miosRegisterNotifyExtraParam{
	MIO_CONST MIO_CHAR	*ipAddr;	// ʵ�ʽ��յ� IP ��ַ
	MIO_UINT16			port;		// ʵ�ʽ��յĶ˿ں�
	MIO_CONST MIO_CHAR	*deviceid;	// ע����豸 ID ��
	MIO_CONST MIO_CHAR	*digestUserName;	// Digest��֤�е�username����
	MIO_UINT32			expires;	// ע�����ʱ��
	MIO_CONST MIO_CHAR	*regCallId;	// ע����Ϣ��Call-ID�ֶ�

	// ���µ���Щ��������������֤��Ϣ
	MIO_CONST MIO_CHAR	*digestNonce;		// SIP Authorization ͷ�ֶ��е� nonce
	MIO_CONST MIO_CHAR	*digestCNonce;		// SIP Authorization ͷ�ֶ��е� cnonce
	MIO_CONST MIO_CHAR	*digestRealm;		// SIP Authorization ͷ�ֶ��е� realm
	MIO_CONST MIO_CHAR	*digestAlg;			// SIP Authorization ͷ�ֶ��е� algorithm
	MIO_CONST MIO_CHAR	*digestNonceCount;	// SIP Authorization ͷ�ֶ��е� nc
	MIO_CONST MIO_CHAR	*digestMethod;		// SIP ��Ϣ�ķ�����
	MIO_CONST MIO_CHAR	*digestQop;			// SIP Authorization ͷ�ֶ��е� qop
	MIO_CONST MIO_CHAR	*digestURI;			// SIP Authorization ͷ�ֶ��е� uri
	MIO_CONST MIO_CHAR	*digestResponse;	// SIP Authorization ͷ�ֶ��е� response
}miosRegisterNotifyExtraParam;

/*
 * �� notifyCode Ϊ MIO_NC_RECV_REQUESTʱ
 * �յ�������Ϣ��Э������Ϊ���¼���
 */
typedef enum mioeRequestProtocol{
	MIO_RP_SIP,				// SIP ��Ϣ
	MIO_RP_HTTP,			// HTTP ��Ϣ
	MIO_RP_UNKNOWN			// ��֪��������
}mioeRequestProtocol;

/*
 * �� notifyCode Ϊ MIO_NC_RECV_REQUEST ʱ
 * notifyExtraParam Ϊָ�����½ṹ��ָ��
 */
typedef struct miosRequestNotifyExtraParam{
	MIO_CONST MIO_CHAR	*ipAddr;	// ʵ�ʽ��յ� IP ��ַ
	MIO_UINT16			port;		// ʵ�ʽ��յĶ˿ں�
	mioeRequestProtocol	protocol;	// ���յ�Э������
}miosRequestNotifyExtraParam;

/* 
 * �� notifyCode Ϊ MIO_NC_RECV_RESPONSE �� MIO_NC_SND_REQUEST_FAIL ʱ
 * notifyExtraParam Ϊ������Ϣʱ�� msgUserData
 */

/*
 * �� notifyCode Ϊ MIO_NC_RECV_REGISTER_RESP �� MIO_NC_SND_REGISTER_FAIL ʱ
 * notifyExtraParam Ϊ����ע����Ϣʱ�� regUserData
 */


/*
 * ��Ϣ֪ͨ�ص�����ԭ�Ͷ���
 *
 * �������壺
 *  userData: ��֪ͨ����SIP��Ϣʱ��Ϊ�����ӿ�ʱ����Ĳ�͸���û�����
 *            ��֪ͨ����HTTP��Ϣʱ�������ʼ�� HTTP ʱû�д���ص���������ô���Ǵ����ӿ�ʱ�Ĳ�͸���û�����
 *                                  �����ʼ�� HTTP ʱ�����˻ص���������ô���ǳ�ʼ�� HTTP ʱ����Ĳ�͸���û�����
 *  notifyCode: ֪ͨ������
 *  msgID: ��ϢID��
 *  msg: ������� XML ��Ϣ
 *  to: SIP��Ϣ To ͷ�е�SIP URL
 *  from: SIP��Ϣ From ͷ�е�SIP URL
 *  notifyExtraParam: ���ӵ�֪ͨ��������ϸ�Ĳμ������˵��
 *
 * ����ֵ��
 *  ��
 *
 */
typedef MIO_VOID (*MIO_NotifyCB)(MIO_VOID *userData,
									mioeNotiyCode notifyCode,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_VOID *notifyExtraParam);

/*
 * �����ӿ�
 *
 * �������壺
 *  listenPort: SIP �������˿ں�
 *  userData: ����֪ͨ�ص�ʱ���ص��ϲ�ģ�鲻͸��ָ��
 *  notifyCB: ��Ϣ֪ͨ�ص�����ָ�롣
 *            ����������ΪMIO_NULL����ô��ʾֻ��Ϊʹ��XML�ı���빦�ܣ���ʱ�����ʼ��ͨѶЭ��ջ���κη��ͺͽ�����Ϣ�ĺ�������Ч��
 *            ����ֻʹ�ñ���빦�ܵĳ�ʼ�����Ե��ö�Ρ�
 *            ���Ƕ����շ����ݵĳ�ʼ��Ŀǰֻ��֧��һ�Ρ�
 *
 * ����ֵ��
 *  �ӿھ��ָ��
 *
 */
MIO_API MIO_VOID* MIO_CreateCtxEx( MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB);


/*
 * �����ӿڣ��� MIO_CreateCtxEx �������������� notifyCB ������
 * �ӿڿ�����Ҫ���ûص�������ʱ��ֱ�ӵ��� MIO_NotifyHandler ��
 * �������ֻ��linux�汾����Ч��Ӧ������ʹ�������������ʹ�� MIO_CreateCtxEx �������
 *
 * �������壺
 *  listenPort: SIP �������˿ں�
 *  userData: ����֪ͨ�ص�ʱ���ص��ϲ�ģ�鲻͸��ָ��
 *
 * ����ֵ��
 *  �ӿھ��ָ��
 *
 */
MIO_API MIO_VOID* MIO_CreateCtx( MIO_UINT16 listenPort,
									MIO_VOID *userData);

/*
 * ���ٽӿ�
 *
 * �������壺
 *  mioCtx: �����ӿ�ʱ���صĽӿ�ģ����
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_DestroyCtx( MIO_VOID *mioCtx );


/*
 * ���������ϲ���Ҫ���͵���Ϣ��
 * Ŀǰ��Ϊ���������
 * �������е�msgID��Чʱ������ΪMIO_INVALID_MSGID������ô��ʾҪ����Ӧ�����ݰ���
 * �������е�msgID��Чʱ����ΪMIO_INVALID_MSGID������ô��ʾҪ�����������ݰ�����ʱ�����е�to��from��Ҫ��д��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ������Ϣ������ӦSIP��Ϣ To ͷ�е�SIP URL����ӦHTTP��Ϣ�е�Ŀ��URL������������ʱʹ�ã�
 *  from: ������Ϣ������ӦSIP��Ϣ From ͷ�е� SIP URL��HTTP��Ϣû��ʹ�ã�����������ʱʹ�ã�
 *  msgID: ��ϢID�ţ�����Ϣ֪ͨ�ص��������ɵģ�������Ӧ��ʱʹ�ã�
 *  msg: ��Ϣ����
 *  msgUserData: �ϲ�ģ���˽����Ϣ���ݡ�ֻ�ڷ���������Ϣʱ��Ч��
 *               ���������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �����յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ֪ͨ�����ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼���շ���ģ���У�
 *               ���շ���ģ�������֪ͨ�ص��Ժ����˽�����ݾ��Ѿ����շ���ģ��ļ�¼���Ƴ���
 *               ��ʱ�ϲ�ģ�������Ҫ��ʹ������Ժ��ͷŵ���Ӧ���ڴ档
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendMsg( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_UINT32 msgID,
								miosMSG *msg,
								MIO_VOID *msgUserData );

/*
 * ���������ϲ���Ҫ���͵���Ϣ��
 * ��������� MIO_SendMsg �����ڷ��� SIP ��Ϣʱʹ�õ��� INFO �����֣������� MESSAGE ������֮�⣬��ȫ��ͬ
 * Ŀǰ��Ϊ���������
 * �������е�msgID��Чʱ������ΪMIO_INVALID_MSGID������ô��ʾҪ����Ӧ�����ݰ���
 * �������е�msgID��Чʱ����ΪMIO_INVALID_MSGID������ô��ʾҪ�����������ݰ�����ʱ�����е�to��from��Ҫ��д��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ������Ϣ������ӦSIP��Ϣ To ͷ�е�SIP URL����ӦHTTP��Ϣ�е�Ŀ��URL������������ʱʹ�ã�
 *  from: ������Ϣ������ӦSIP��Ϣ From ͷ�е� SIP URL��HTTP��Ϣû��ʹ�ã�����������ʱʹ�ã�
 *  msgID: ��ϢID�ţ�����Ϣ֪ͨ�ص��������ɵģ�������Ӧ��ʱʹ�ã�
 *  msg: ��Ϣ����
 *  msgUserData: �ϲ�ģ���˽����Ϣ���ݡ�ֻ�ڷ���������Ϣʱ��Ч��
 *               ���������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �����յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ֪ͨ�����ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼���շ���ģ���У�
 *               ���շ���ģ�������֪ͨ�ص��Ժ����˽�����ݾ��Ѿ����շ���ģ��ļ�¼���Ƴ���
 *               ��ʱ�ϲ�ģ�������Ҫ��ʹ������Ժ��ͷŵ���Ӧ���ڴ档
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */MIO_API MIO_UINT32 MIO_SendMsgEs( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_UINT32 msgID,
								miosMSG *msg,
								MIO_VOID *msgUserData );

/*
 * ���������ϲ���Ҫ���͵���Ϣ��
 * ��������� MIO_SendMsg ����������������ʵ�ʵķ��͵�ַ��ip��port�������������� to �����еĽ��������ĵ�ַ
 * Ŀǰ��Ϊ���������
 * �������е�msgID��Чʱ������ΪMIO_INVALID_MSGID������ô��ʾҪ����Ӧ�����ݰ���
 * �������е�msgID��Чʱ����ΪMIO_INVALID_MSGID������ô��ʾҪ�����������ݰ�����ʱ�����е�to��from��Ҫ��д��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ������Ϣ������ӦSIP��Ϣ To ͷ�е�SIP URL����ӦHTTP��Ϣ�е�Ŀ��URL������������ʱʹ�ã�
 *  from: ������Ϣ������ӦSIP��Ϣ From ͷ�е� SIP URL��HTTP��Ϣû��ʹ�ã�����������ʱʹ�ã�
 *  msgID: ��ϢID�ţ�����Ϣ֪ͨ�ص��������ɵģ�������Ӧ��ʱʹ�ã�
 *  msg: ��Ϣ����
 *  msgUserData: �ϲ�ģ���˽����Ϣ���ݡ�ֻ�ڷ���������Ϣʱ��Ч��
 *               ���������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �����յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ֪ͨ�����ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼���շ���ģ���У�
 *               ���շ���ģ�������֪ͨ�ص��Ժ����˽�����ݾ��Ѿ����շ���ģ��ļ�¼���Ƴ���
 *               ��ʱ�ϲ�ģ�������Ҫ��ʹ������Ժ��ͷŵ���Ӧ���ڴ档
 *  ip: ���͵�ʵ�� IP ��ַ�����Ϊ�գ�ʹ�� to �н��������ĵ�ַ
 *  port: ���͵�ʵ�ʶ˿ں�
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendMsgEx( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_VOID *msgUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port );


/*
 * ���������ϲ���Ҫ���͵���Ϣ��
 * ��������� MIO_SendMsgEx �����ڷ��� SIP ��Ϣʱʹ�õ��� INFO �����֣������� MESSAGE ������֮�⣬��ȫ��ͬ
 * Ŀǰ��Ϊ���������
 * �������е�msgID��Чʱ������ΪMIO_INVALID_MSGID������ô��ʾҪ����Ӧ�����ݰ���
 * �������е�msgID��Чʱ����ΪMIO_INVALID_MSGID������ô��ʾҪ�����������ݰ�����ʱ�����е�to��from��Ҫ��д��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ������Ϣ������ӦSIP��Ϣ To ͷ�е�SIP URL����ӦHTTP��Ϣ�е�Ŀ��URL������������ʱʹ�ã�
 *  from: ������Ϣ������ӦSIP��Ϣ From ͷ�е� SIP URL��HTTP��Ϣû��ʹ�ã�����������ʱʹ�ã�
 *  msgID: ��ϢID�ţ�����Ϣ֪ͨ�ص��������ɵģ�������Ӧ��ʱʹ�ã�
 *  msg: ��Ϣ����
 *  msgUserData: �ϲ�ģ���˽����Ϣ���ݡ�ֻ�ڷ���������Ϣʱ��Ч��
 *               ���������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �����յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ֪ͨ�����ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼���շ���ģ���У�
 *               ���շ���ģ�������֪ͨ�ص��Ժ����˽�����ݾ��Ѿ����շ���ģ��ļ�¼���Ƴ���
 *               ��ʱ�ϲ�ģ�������Ҫ��ʹ������Ժ��ͷŵ���Ӧ���ڴ档
 *  ip: ���͵�ʵ�� IP ��ַ�����Ϊ�գ�ʹ�� to �н��������ĵ�ַ
 *  port: ���͵�ʵ�ʶ˿ں�
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendMsgEsEx( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_VOID *msgUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port );

/*
 * ��Ч��ע��ID
 */
#define MIO_INVALID_REGID		0

/*
 * ���������������һ��SIP��REGISTER�Ự������Ự���ֵ�����MIO_cancelRegΪֹ��
 * �����Եķ���ע����Ϣ����ʱ�ϲ�Ӧ����Ϊһ��������֤�Ŀͻ��ˡ�
 * ���͵�ע����Ϣ�Ƿ�ɹ���ͨ����Ϣ֪ͨ�ص�����֪ͨ�ϲ㡣
 * notifyCodeΪMIO_NC_RECV_REGISTER_RESPʱ����ʾһ��ע����Ϣ�Ѿ������������ܡ�
 * notifyCodeΪMIO_NC_SND_REGISTER_FAILʱ����ʾһ��ע����Ϣû�з��ͳɹ�������ע����Ϣ���������ܾ��ˡ�
 * ����ʧ�ܵ�����£�Ĭ�ϻ������һ�ε�ע������ֻ�е���MIO_cancelReg�Ż�ֹͣע�������
 * ����ͨ������MIO_enableStopRegWhenFail��MIO_disableStopRegWhenFail���ı������Ϊ���������Ϊ��μ�������������˵����
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ע���Ŀ���������ַ��
 *  from: Ҫע��ĵ�ַ����������û������֣�
 *  userName: ��������digest��֤ʱ���û�����
 *  passWord: ��������digest��֤ʱ�����롣
 *  expires: ע���ַ����Чʱ�䣬����Ϊ��λ��
 *           �ӿ�ģ����������ֵ��С�����ֵ��ʱ�������ط�ע�ᣬ�Ա���ע��ĳ�����Ч��
 *           ���ֵ������ڻ����0����ô���60�룬��ΪЭ��ջ�������ʱ���ȥ60���ʱ���ط�ע�ᣬ������ֵС��60���ͻᵼ��Э��ջ���ϵ��ط�ע����Ϣ��
 *           ����0ʱ���������;��Э��ջֻ�ᷢ��һ��ע�ᡣ
 *  regUserData: �ϲ�ģ��ͱ�ע����ص�˽����Ϣ���ݡ����������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �ӿ�ģ������յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ�ص������ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼�ڽӿ�ģ���У�ֱ������MIO_cancelRegʱ�Żᱻɾ������
 *               �ϲ�ģ�����Ҫ����֮���ͷŵ���Ӧ���ڴ档
 *  ip: ���͵�ʵ�� IP ��ַ�����Ϊ�գ���ôʹ�� to �н��������ĵ�ַ��
 *  port: ���͵�ʵ�ʶ˿ں�
 *
 * ����ֵ��
 *  ע��ID�ţ�MIO_INVALID_REGIDΪ��Ч��ע��ID�ţ����������ֵʱʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendReg( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_CHAR *userName,
								MIO_CHAR *passWord,
								MIO_INT32 expires,
								MIO_VOID *regUserData,
								MIO_CHAR *ip,
								MIO_UINT16 port );

/*
 * ��������� MIO_SendReg �Ĺ�����ͬ��ֻ������������ע��ʱ REGISTER ��Ϣͷ�е� Call-ID �ֶ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ע���Ŀ���������ַ��
 *  from: Ҫע��ĵ�ַ����������û������֣�
 *  userName: ��������digest��֤ʱ���û�����
 *  passWord: ��������digest��֤ʱ�����롣
 *  expires: ע���ַ����Чʱ�䣬����Ϊ��λ��
 *           �ӿ�ģ����������ֵ��С�����ֵ��ʱ�������ط�ע�ᣬ�Ա���ע��ĳ�����Ч��
 *           ���ֵ������ڻ����0����ô���60�룬��ΪЭ��ջ�������ʱ���ȥ60���ʱ���ط�ע�ᣬ������ֵС��60���ͻᵼ��Э��ջ���ϵ��ط�ע����Ϣ��
 *           ����0ʱ���������;��Э��ջֻ�ᷢ��һ��ע�ᡣ
 *  regUserData: �ϲ�ģ��ͱ�ע����ص�˽����Ϣ���ݡ����������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �ӿ�ģ������յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ�ص������ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼�ڽӿ�ģ���У�ֱ������MIO_cancelRegʱ�Żᱻɾ������
 *               �ϲ�ģ�����Ҫ����֮���ͷŵ���Ӧ���ڴ档
 *  ip: ���͵�ʵ�� IP ��ַ�����Ϊ�գ���ôʹ�� to �н��������ĵ�ַ��
 *  port: ���͵�ʵ�ʶ˿ں�
 *  regCallId: ���ϲ���д��Call-ID����ʹ�������ʱ����ҪС�ģ���Ϊ����SIPЭ��Ĺ涨�����ֵҪ��ȫ���ϱ���Ψһ��
 *
 * ����ֵ��
 *  ע��ID�ţ�MIO_INVALID_REGIDΪ��Ч��ע��ID�ţ����������ֵʱʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendRegEx( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId );

/*
 * ��������� MIO_SendRegEx �Ĺ�����ͬ��ֻ��������ע��ʱ����Я�� XML ��Ϣ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  to: ע���Ŀ���������ַ��
 *  from: Ҫע��ĵ�ַ����������û������֣�
 *  userName: ��������digest��֤ʱ���û�����
 *  passWord: ��������digest��֤ʱ�����롣
 *  expires: ע���ַ����Чʱ�䣬����Ϊ��λ��
 *           �ӿ�ģ����������ֵ��С�����ֵ��ʱ�������ط�ע�ᣬ�Ա���ע��ĳ�����Ч��
 *           ���ֵ������ڻ����0����ô���60�룬��ΪЭ��ջ�������ʱ���ȥ60���ʱ���ط�ע�ᣬ������ֵС��60���ͻᵼ��Э��ջ���ϵ��ط�ע����Ϣ��
 *           ����0ʱ���������;��Э��ջֻ�ᷢ��һ��ע�ᡣ
 *  regUserData: �ϲ�ģ��ͱ�ע����ص�˽����Ϣ���ݡ����������ϲ�ģ���¼�ͱ�������Ϣ��ص�˽�����ݡ�
 *               �ӿ�ģ������յ���Ӧ��Ӧ�����ʧ��ʱͨ����Ϣ�ص������ش����ϲ�ģ�顣
 *               �ϲ�ģ���ر���Ҫע��������˽�����ݵ��ڴ������ͷ����⡣
 *               ������Ϣʱ�����˽�����ݻᱻ��¼�ڽӿ�ģ���У�ֱ������MIO_cancelRegʱ�Żᱻɾ������
 *               �ϲ�ģ�����Ҫ����֮���ͷŵ���Ӧ���ڴ档
 *  ip: ���͵�ʵ�� IP ��ַ�����Ϊ�գ���ôʹ�� to �н��������ĵ�ַ��
 *  port: ���͵�ʵ�ʶ˿ں�
 *  regCallId: ���ϲ���д��Call-ID����ʹ�������ʱ����ҪС�ģ���Ϊ����SIPЭ��Ĺ涨�����ֵҪ��ȫ���ϱ���Ψһ��
 *  msg: ע��ʱЯ���� XML ��Ϣ��
 *
 * ����ֵ��
 *  ע��ID�ţ�MIO_INVALID_REGIDΪ��Ч��ע��ID�ţ����������ֵʱʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendRegEx2( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId,
									miosMSG *msg );


/*
 * �����������ȡ��һ����MIO_SendReg��MIO_SendRegEx��MIO_SendRegEx2�����ע��Ự��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  regID: ��MIO_SendReg��MIO_SendRegEx��MIO_SendRegEx2���ص�ע��ỰID��
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾȡ���ɹ�
 *  MIO_FALSE ��ʾȡ��ʧ��
 *
 */
MIO_API MIO_BOOL MIO_cancelReg( MIO_VOID *mioCtx,
								MIO_UINT32 regID );

/*
 * ��������SIP��REGISTER��Ӧ����ʱ�ϲ�Ӧ����Ϊһ����֤��������
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msgID: Ϊ�ص�֪ͨnotifyCodeΪMIO_NC_RECV_REGISTERʱЯ����msgID��
 *  respCode��ע���Ӧ��״̬�롣200��ʾ�ɹ���403��ʾ��֤ʧ�ܡ�
 *  passWord: ��respCodeΪ200ʱ������������digest��֤����ô�շ���ģ��ʹ���������ֵ������digest��
 *            ������ֵΪ�գ���ôҲ��������֤���㡣
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendRegResp( MIO_VOID *mioCtx,
									MIO_UINT32 msgID,
									MIO_INT32 respCode,
									MIO_CHAR *passWord );

/*
 * ��������� MIO_SendRegResp �Ĺ�����ͬ��ֻ������������SIP��Ӧ��Ϣͷ�Ļ�Ӧ˵��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msgID: Ϊ�ص�֪ͨnotifyCodeΪMIO_NC_RECV_REGISTERʱЯ����msgID��
 *  respCode��ע���Ӧ��״̬�롣200��ʾ�ɹ���403��ʾ��֤ʧ�ܡ�
 *  passWord: ��respCodeΪ200ʱ������������digest��֤����ô�շ���ģ��ʹ���������ֵ������digest��
 *            ������ֵΪ�գ���ôҲ��������֤���㡣
 *  respReasonPhrase��SIP��Ӧͷ�еĻ�Ӧ˵��
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendRegRespEx( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase );

/*
 * ��������� MIO_SendRegRespEx �Ĺ�����ͬ��ֻ�������˷���ע���Ӧʱ����Я�� XML ��Ϣ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msgID: Ϊ�ص�֪ͨnotifyCodeΪMIO_NC_RECV_REGISTERʱЯ����msgID��
 *  respCode��ע���Ӧ��״̬�롣200��ʾ�ɹ���403��ʾ��֤ʧ�ܡ�
 *  passWord: ��respCodeΪ200ʱ������������digest��֤����ô�շ���ģ��ʹ���������ֵ������digest��
 *            ������ֵΪ�գ���ôҲ��������֤���㡣
 *  respReasonPhrase��SIP��Ӧͷ�еĻ�Ӧ˵��
 *  msg: ע��ʱЯ���� XML ��Ϣ��
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendRegRespEx2( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase,
										miosMSG *msg );


/*
 * ���������֤��Ϣ����������Ԥ�����һЩ��֤��Ϣ�����������ڵ���MIO_SendRegʱ�����ṩuserName��passWord��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  deviceid: Ҫע����豸�ţ���Ӧ��MIO_SendReg��from�����е�SIP��ַ��username���֣�
 *  digestUserName: digest�����е��û���
 *  password: digest�����е�����
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾ��ӳɹ�
 *  MIO_FALSE ��ʾ���ʧ��
 *
 */
MIO_API MIO_BOOL MIO_addAuthInfo( MIO_VOID *mioCtx,
									MIO_CONST MIO_CHAR *deviceid,
									MIO_CONST MIO_CHAR *digestUserName,
									MIO_CONST MIO_CHAR *password );


/*
 * ����������Ϣ���ݵ�ͷ�ṹ(miosMSG)���ڴ�û�б����0�����ϲ�ģ����ѡ����
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *
 * ����ֵ��
 *  ָ��ͷ�ṹ��ָ�루MIO_NULL��ʾ����ʧ�ܣ�
 *
 */
MIO_API miosMSG* MIO_mallocMsgHeader( MIO_VOID *mioCtx );

/*
 * �����ͷ���Ϣ���ݵ�ͷ�ṹ(miosMSG)��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msg: ��Ҫ���ͷŵ���Ϣͷ�ṹָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_freeMsgHeader( MIO_VOID *mioCtx, miosMSG* msg );

/*
 * ����������Ϣ�����е���ϢԪ�ؽṹ���ڴ�û�б����0�����ϲ�ģ����ѡ����
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  size: ��Ҫ��IE��С
 *
 * ����ֵ��
 *  ָ����ϢԪ�ؽṹ��ָ�루MIO_NULL��ʾ����ʧ�ܣ�
 *
 */
MIO_API MIO_VOID* MIO_mallocIE( MIO_VOID *mioCtx, MIO_UINT32 size );

/*
 * �����ͷ���Ϣ�����е���ϢԪ�ؽṹ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  ie: ��Ҫ���ͷŵ���ϢԪ�ؽṹָ��
 *  size: ��Ҫ���ͷŵ���ϢԪ�ؽṹ�Ĵ�С
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_freeIE( MIO_VOID *mioCtx, MIO_VOID *ie, MIO_UINT32 size);

/*
 * ����������Ϣ�����е��б�ڵ㣬�ڴ�û�б����0�����ϲ�ģ����ѡ����
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *
 * ����ֵ��
 *  ָ���б�ڵ��ָ�루MIO_NULL��ʾ����ʧ�ܣ�
 *
 */
MIO_API miosList* MIO_mallocListNode( MIO_VOID *mioCtx );

/*
 * �����ͷ���Ϣ�����е��б�ڵ㡣
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  listNode: ��Ҫ���ͷŵ��б�ڵ�ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_freeListNode( MIO_VOID *mioCtx, miosList *listNode );

/*
 * �����ͷ���Ϣ�����е�IE�б�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  ieList: ��Ҫ���ͷŵ�IE�б�
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_freeIEList( MIO_VOID *mioCtx, miosList *ieList );

/*
 * �����ͷ�������Ϣ���ݣ�����ͷ�ṹ(miosMSG)�����е��б�ڵ�(miosList)�����е���ϢԪ�ؽṹ
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msg: ��Ҫ���ͷŵ���Ϣ����ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_freeWholeMsg( MIO_VOID *mioCtx, miosMSG* msg );

#define IPV4 0
#define IPV6 1
/*
 * �����²Ȿ�ص�IP��ַ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  family: IPV4:0,IPV6:1
 *  ipAddr: �������IP��ַ�Ļ�����
 *  len: ���õĻ������ĳ���
 *  dest: ���ݽ�Ҫ���͵�Ŀ�ĵ�ַ������������������ж�������ַʱ������ѡ��һ������ʵĵ�ַ��
 *
 * ����ֵ��
 *  MIO_FALSE��ʾ�²�ʧ��
 *  MIO_TRUE��ʾ�ɹ���
 *
 */
MIO_API MIO_BOOL MIO_guessLocalIP( MIO_VOID *mioCtx, MIO_INT32 family, MIO_CHAR *ipAddr, MIO_INT32 len, MIO_CHAR *dest );

/*
 * ��Ϣ��ı���ģʽ����ͬ�ı����ʽ�в�ͬ����ʽ������˵�����£�
 * ��ʹ����������Ҫ����һ����Ϣ����Ϣ��Ϊ"MSG_CMS_REG_REQ"����ҪЯ�����½ṹ��IE
 *  typedef struct miosIEX_DCS_INFO{
 *      MIO_UINT32 type;
 *
 *      MIO_UINT8 m_PTZmode;
 *      MIO_UINT8 m_Vtdumode;
 *      MIO_UINT16 m_CallNum;
 *  }miosIEX_DCS_INFO;
 *
 * ������Ϊ MIOC_CM_TELECOM ʱ�����ɵ���Ϣ������
 *  <?xml version="1.0" encoding="UTF-8" ?><Message Version="1.0">
 *  <IE_HEADER MessageType="MSG_CMS_REG_REQ" SequenceNumber="0" SessionID="3241" SourceID="123456789012345678" DestinationID="123456789012345678" />
 *  <IEX_DCS_INFO PTZmode="0" Vtdumode="1" CallNum="4" />
 *  </Message>
 *
 * ������Ϊ MIOC_CM_CNC_REQ ʱ�����ɵ���Ϣ������
 *  <?xml version="1.0" encoding="UTF-8" ?><request command="MSG_CMS_REG_REQ"><parameters>
 *  <IEX_DCS_INFO>
 *      <PTZmode>0</PTZmode>
 *      <Vtdumode>1</Vtdumode>
 *      <CallNum>4</CallNum>
 *  </IEX_DCS_INFO>
 *  </parameters></request>
 *
 * ������Ϊ MIOC_CM_CNC_RESP ʱ�����ɵ���Ϣ������
 *  <?xml version="1.0" encoding="UTF-8" ?><response command="MSG_CMS_REG_REQ">
 *  <result code="0"></result>
 *  <parameters>
 *  <IEX_DCS_INFO>
 *      <PTZmode>0</PTZmode>
 *      <Vtdumode>1</Vtdumode>
 *      <CallNum>4</CallNum>
 *  </IEX_DCS_INFO>
 *  </parameters>
 *  </response>
 *
 * ������Ϊ MIOC_CM_CNC_URLENCODED ʱ�����ɵ���Ϣ������
 *  MSG_CMS_REG_REQ?IEX_DCS_INFO=0%2c1%2c4
 *
 */
typedef enum mioeCodeMode
{
	MIOC_CM_TELECOM,
	MIOC_CM_CNC_REQ,
	MIOC_CM_CNC_RESP,
	MIOC_CM_CNC_URLENCODED,
	MIOC_CM_UNKNOWN
}mioeCodeMode;

/*
 * ������XML��Ϣ�ı�������miosMSG����Ϣ�ṹ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  buf: XML��ʽ����Ϣ�ı�
 *  len: ��Ϣ�ı��ĳ���
 *  codeMode: ����ģʽ����ϸ�μ�mioeCodeMode��˵��
 *
 * ����ֵ��
 *  ���ؽ��������ɵ���Ϣ�ṹ�����ΪMIO_NULL����ʾ����ʧ�ܡ�
 *  ��Ҫʹ��MIO_freeWholeMsg�����ͷţ����ߴ��ݸ�MIO_SendMsg���͡�
 *
 */
MIO_API miosMSG* MIO_decodeMSG( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

/*
 * ������miosMSG�ṹ����Ϣת������Ϣ�ı���
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msg: ��Ҫת�����ı�����Ϣ
 *  buf: ����Ļ��档���ΪMIO_NULL������ֻ�Ǽ�����Ҫ��������ȡ�
 *  len: ����Ļ��泤�ȡ�
 *  codeMode: ����ģʽ����ϸ�μ�mioeCodeMode��˵��
 *
 * ����ֵ��
 *  ����ת�����ı�֮��ĳ��ȡ����buf��ΪMIO_NULL������lenС��ʵ����Ҫ�ĳ��ȣ�����ֵΪ����Ҫ�ĳ��ȵ��෴����
 *
 */
MIO_API MIO_INT32 MIO_encodeMSG( MIO_VOID *mioCtx, miosMSG *msg, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

/*
 * �����е���Ϣ�ṹ�����ĸ���һ�ݡ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  msg: ��Ҫ�����Ƶ���Ϣ�ṹ
 *
 * ����ֵ��
 *  ���Ƶ���Ϣ�ṹ�����ΪMIO_NULL��ʾ����ʧ�ܡ�
 *  ��Ҫʹ��MIO_freeWholeMsg�����ͷţ����ߴ��ݸ�MIO_SendMsg���͡�
 *
 */
MIO_API miosMSG* MIO_cloneWholeMsg( MIO_VOID *mioCtx, miosMSG* msg );


/*
 * �������ýӿ�ģ���Ƿ��Զ��ӽ��ܵ���������Ϣ�л�ȡ������IP��ַ�Ͷ˿ںš�
 * ������Ϊʹ�ܵ�����£��ӿ�ģ��Ὣ�յ���������Ϣ�е�SourceID���������յ�����ԴIP��ַ�Ͷ˿ں���ӵ�һ�Ŷ�Ӧ���С�
 * ֮����������Ϣʱ�����DestinationID���������Ŷ�Ӧ���в鵽����ô��ʹ�ñ��еĵ�ַ������Ϣ��������from������
 * Ĭ���ڴ����շ���ģ��ʱ�����������ʹ�ܵġ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  bEnable: �Ƿ�ʹ��ID�͵�ַ��ӳ�䡣
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_selfLearnDeviceIP( MIO_VOID *mioCtx, MIO_BOOL bEnable );

/*
 * MIO_checkLearnDeviceIPCB�ص������ķ���ֵ
*/
#define MIO_LEARN_DEVICE_IP_NO			0
#define MIO_LEARN_DEVICE_IP_YES			1
#define MIO_LEARN_DEVICE_IP_DEL			2
#define MIO_LEARN_DEVICE_IP_DEFAULT		3

/*
 * ����Ƿ�Ҫ��¼ID��IP��ַӳ��Ļص�����
 * ������������������ӿ�ģ���ڽ��յ���Ϣʱ�����������������ݷ���ֵ������ͬ�Ĵ���
 *
 * �������壺
 *  userData: �����ӿ�ʱ���ϲ�ģ�鴫��Ĳ�͸��ָ�롣
 *  msg: ���յ���������Ϣ��
 *
 * ����ֵ��
 *  MIO_LEARN_DEVICE_IP_NO: ��ʾ����¼��
 *  MIO_LEARN_DEVICE_IP_YES: ��ʾ��Ҫ��¼��
 *  MIO_LEARN_DEVICE_IP_DEL: ��ʾҪɾ���Ѿ���¼�ĵ�ַ��
 *  MIO_LEARN_DEVICE_IP_DEFAULT: ��ʾ��ͬû����������ص�����һ��
 *
 */
typedef MIO_INT32 (*MIO_checkLearnDeviceIPCB)( MIO_VOID *userData, miosMSG *msg );

/*
 * ��Ϊ MIO_selfLearnDeviceIP ��������е���Ϣ�������Ƿ���Ҫ�Զ���ȡ����¼���յ�������IP��ַ�Ͷ˿ںš�
 * ���������ѡ���ԵĻ�ȡ�������������������������ϲ�ʹ��ģ������һ�������ж��Ƿ���Ҫ��ȡ�Ļص�������
 * ������������жϻص�ʱ���ӿ�ģ�����Ȼ��������ص���Ȼ����ݻص��ķ���ֵ������ͬ�Ķ�����
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  checkLearnDeviceIPCB: �������жϵĻص�������
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setCheckLearnDeviceIPCallBack( MIO_VOID *mioCtx, MIO_checkLearnDeviceIPCB checkLearnDeviceIPCB );

/*
 * ������ID�͵�ַ��ӳ��������һ����¼��
 * ����Զ���ȡ�Ĺ��ܱ�ʹ��ʱ����ô������¼���ܻᱻ�����Զ���ȡ���ĵ�ַ�����ǡ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  deviceID: ID��
 *  ip: IP��ַ
 *  port: �˿ں�
 *
 * ����ֵ��
 *  MIO_FALSE ��ʾ���ʧ�ܡ�
 *  MIO_TRUE ��ʾ��ӳɹ���
 *
 */
MIO_API MIO_BOOL MIO_addDeviceAddr( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

/*
 * ������ID�͵�ַ��ӳ�����ɾ��һ����¼��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ����
 *  deviceID: ID��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_removeDeviceAddr( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID );

/*
 * ���������շ���ģ��LOG�ļ��Ĵ�С���ơ��շ���ģ���LOG���ö���ļ��ķ�ʽ��
 * ÿ��LOG�ļ�Ĭ�����Ϊ��Լ 16M��Ĭ�ϵ��ܴ�С����Ϊ1G��
 * һ���ļ��Ĵ�С�ﵽ�����Ժ������һ���µ��ļ�����Щ�ļ���ǰ׺����һ���Ա�鿴��
 * �����LOG��Ϣ��С�ﵽ���������ơ���ô����ѭ�����ǵķ�ʽ�����ǵ�������Ǹ��ļ���
 * ����ʹ������������޸�Ĭ��ֵ��
 *
 * �������壺
 *  totalBytes: �ܵ�LOG��С���ơ�������ֵС�� bytesPerFile����ô��ȡ�����ܴ�С�����ơ�Ĭ��ֵΪ1G��
 *  bytesPerFile: ����LOG�ļ��Ĵ�С���ơ�С��512K��ֵ�ͱ����� 512K��Ĭ��ֵΪ16M��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setLogLimit( MIO_UINT32 totalBytes, MIO_UINT32 bytesPerFile );

/*
 * ����ȡ�����ڷ��͵���Ϣ��������ֻ�ǽ���Ϣ��Э��ջ��ɾ�������Ҳ��ٽ������Ϣ�Ļ�Ӧ���ݸ�Ӧ�ò㡣
 * �����Ѿ����ͳ�ȥ�����ݰ����Լ�����Щ���ݰ����µĽ��շ��������ܲ���Ӱ�졣
 *
 * �������壺
 *  mioCtx: �շ���ģ��������ָ��
 *  msgID: Ҫȡ������ϢID��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_cancelSendingMsg( MIO_VOID *mioCtx, MIO_UINT32 msgID );

/*
 * ���������ϲ��Զ������Ϣ��IE����ϸ����μ������ƽӿ���ϸ���˵���顷�е��Զ��巢����Ϣ��IE��
 *
 * �������壺
 *  userMsgList: �ϲ��Զ������Ϣ�����б�Ϊһ�����飬��β�Ľṹ����Ϊ0
 *  userIEList: �ϲ��Զ����IE�����б�Ϊһ�����飬��β�Ľṹ����Ϊ0
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setUserMsgAndIE( MIO_CONST miosUserMsgDef *userMsgList, MIO_CONST miosUserIEDef *userIEList );


/*
 * ������ýӿ�ģ��İ汾�š�
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ����һ����־�ӿ�ģ��汾���ַ�����
 *
 */
MIO_API MIO_CONST MIO_CHAR* MIO_getVersionStr( MIO_VOID );

/*
 * ��miosMSG��Ϣ�Զ����Ƶ���ʽ��д��һ�λ����С�
 * ��д�������е����ݣ�����ʹ����ͬһ��ܹ�CPU�Ļ�����ʹ��MIO_deserializeMsg��ԭ��miosMSG��Ϣ��
 *
 * �������壺
 *  mioCtx: �շ���ģ��������ָ��
 *  msg: Ҫת������Ϣ
 *  buf: �������
 *  len: �������ĳ���
 *
 * ����ֵ��
 *  ���buf��ΪMIO_NULL��������д�ĳ��ȣ�lenС����Ҫ�ĳ��ȣ�����ֵС���㣬��ʾ��дʧ�ܡ�
 *  ���bufΪMIO_NULL��������Ҫ�ĳ��ȡ�
 *
 */
MIO_API MIO_INT32 MIO_serializeMsg( MIO_VOID *mioCtx, miosMSG* msg, MIO_BYTE *buf, MIO_INT32 len );

/*
 * ������MIO_serializeMsg���������ƻ������ݻ�ԭΪmiosMSG��Ϣ��
 *
 * �������壺
 *  mioCtx: �շ���ģ��������ָ��
 *  buf: ����������
 *  len: ���������ݳ���
 *
 * ����ֵ��
 *  ��ԭ����Ϣ����Ҫ��MIO_freeWholeMsg�ͷš�
 *
 */
MIO_API miosMSG* MIO_deserializeMsg( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len );



/*
 * ������ʼ��HTTP��ϢЭ��ջ��
 *
 * �������壺
 *  mioCtx: �շ���ģ��������ָ��
 *  listenIpFamily: AF_INET;AF_INET6
 *  listenPort: �����Ķ˿ں�
 *  userData: �ϲ��û��Ĳ�͸��ָ�룬�ڵ��ûص���ʱ��ش����ϲ�
 *  notifyCB: ���յ���Ϣ��֪ͨ�ص�����MIO_CreateCtxEx�����Ļص���ͬ��
 *            ����������Ϊ�գ���ô��ʹ�ô����շ���ģ��ʱ��userData��notifyCB
 *
 * ����ֵ��
 *  MIO_TRUE��ʾ��ʼ���ɹ���
 *  MIO_FALSE��ʾ��ʼ��ʧ�ܡ�
 *
 */
MIO_API MIO_BOOL MIO_initHTTPCtx( MIO_VOID *mioCtx,
									MIO_INT32 listenIpFamily,
									MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB );

/*
 * �����ر�HTTPЭ��ջ��һ�����ӡ�
 * HTTPЭ��ջ�Ĺ���ģʽ�ǲ������رնԷ����������ӡ�
 * �ϲ�ģ����Ը�����Ҫѡ���ԵĹر�ĳһ�����ӡ�
 * ���ӵ�Զ�˵�ַ�����Դӽ��յ�������Ϣ�Ļص�֪ͨ�����л�á�
 *
 * �������壺
 *  mioCtx: �շ���ģ��������ָ��
 *  ip: ���ӵ�Զ��ip��ַ
 *  port: ���ӵ�Զ�˶˿ں�
 *
 * ����ֵ��
 *  MIO_TRUE��ʾ�ر����ӳɹ�
 *  MIO_FALSE��ʾ�ر�����ʧ��
 *
 */
MIO_API MIO_BOOL MIO_closeHTTPConnection( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

/*
 * ��������HTTP���ӵĳ�ʱʱ�䡣
 * ����������ʱʱ�䵽��ʱHTTP�����϶�û���κε����ݣ���ô�ͻ��Զ��ر�������ӡ�
 * ���������ʱʱ���Ŀ��������������Ѿ������ڵ��쳣���ӡ�
 *
 * �������壺
 *  mioCtx: �շ���ģ��������ָ��
 *  timeout: ��ʱʱ�䣬����Ϊ��λ��Ĭ��Ϊ1800�루��Сʱ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setHTTPConnectionTimeout( MIO_VOID *mioCtx, MIO_UINT32 timeout );
											


/*
 * ��ip��ַ�Ͷ˿ں�ƴװ��HTTP URL����ʽΪ http://ip:port/
 *
 * �������壺
 *  retURL: URL���������
 *  len: �������ĳ���
 *  ip: ip��ַ
 *  port: �˿ں�
 *
 * ����ֵ��
 *  MIO_TRUE��ʾƴװ�ɹ���
 *  MIO_FALSE��ʾƴװʧ�ܣ�ͨ������Ϊ�������ĳ��Ȳ�����
 *
 */
MIO_API MIO_BOOL MIO_fillHTTPUrl( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *ip,
									MIO_UINT16 port );

/*
 * ����ƴװSIP URL����ʽΪ sip:[username@]ip:port ��[]�����Ĳ���Ϊ��ѡ�ģ�
 *
 * �������壺
 *  retURL: URL���������
 *  len: �������ĳ���
 *  username: SIP��ַ���û������֣����Ϊ�գ���û�е�ַ���û�������
 *  ip: SIP��ַ����������
 *  port: SIP��ַ�Ķ˿ں�
 *
 * ����ֵ��
 *  MIO_TRUE��ʾƴװ�ɹ���
 *  MIO_FALSE��ʾƴװʧ�ܣ�ͨ������Ϊ�������ĳ��Ȳ�����
 *
 */
MIO_API MIO_BOOL MIO_fillSIPUrl( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *username,
									MIO_CHAR *ip,
									MIO_UINT16 port );
/*
 * ��HTTPЭ��ͨѶʱ����ϢЯ����ʽ
 */
typedef enum mioeHTTPEncodeMode{
	MIO_HTTP_EM_POST_XML,			// ʹ�� POST ����Я�� XML ��ʽ����Ϣ��
	MIO_HTTP_EM_POST_URLENCODED,	// ʹ�� POST ����Я�� application/x-www-form-urlencoded ��ʽ����Ϣ��
	MIO_HTTP_EM_GET					// ʹ�� GET ����������Ϣ��Я�������� URL �� 
}mioeHTTPEncodeMode;

/*
 * ��ΪHTTP�������ʽ�ж��ַ�ʽ�����������������HTTP�ڷ��������ʱ��ʹ��ʲô��ʽ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  encodeMode: �����ģʽ������ mioeHTTPEncodeMode ��˵��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setHTTPEncodeMode( MIO_VOID *mioCtx, mioeHTTPEncodeMode encodeMode );

/*
 * ��������HTTP������Ϣ��
 * �ر��ṩ�������������ʹӦ���߿��Զ�ÿһ����Ϣ�����ò�ͬ����Ϣ��װ��ʽ��
 * ���������ʹ��MIO_SendMsg��MIO_SendMsgEx�Ϳ�������Ҫ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  url: Ŀ��URL
 *  msg: ��Ϣ����
 *  msgUserData: �ϲ�ģ���˽����Ϣ���ݡ��μ�MIO_SendMsg�е�˵��
 *  ip: ���͵�Ŀ���ַ�����Ϊ�գ���ôʹ��url�н��������ĵ�ַ
 *  port: ���͵�Ŀ��˿ں�
 *  httpEncodeMode: �����ģʽ���μ�MIO_setHTTPEncodeMode
 *
 * ����ֵ��
 *  ��ϢID�ţ�MIO_INVALID_MSGIDΪ��Ч����ϢID�ţ����������ֵʱʱ��ʾ��������ʧ�ܣ�
 *
 */
MIO_API MIO_UINT32 MIO_SendHttpReq( MIO_VOID *mioCtx,
										MIO_CHAR *url,
										miosMSG *msg,
										MIO_VOID *msgUserData,
										MIO_CHAR *ip,
										MIO_UINT16 port,
										mioeHTTPEncodeMode httpEncodeMode );

/*
 * ���ϲ�Ӧ����Ϊ REGISTER������ʱ������ʹ��digest��֤��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  realm: digest��֤ʱ��ʾ���ͻ��˵�������
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_enableDigest( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *realm );

/*
 * ���ϲ�Ӧ����Ϊ REGISTER������ʱ������ȡ��digest��֤��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_disableDigest( MIO_VOID *mioCtx );

/*
 * ����������־���ܡ�
 * �ӿ�ģ�����־�ļ���Windowsƽ̨�´洢��"c:\miolog\"Ŀ¼�£�
 * ��linuxƽ̨�´洢��"��ǰ����Ŀ¼/miolog"Ŀ¼�С�
 * �����Ӧ��Ŀ¼�����ڣ��Ͳ��Ὠ����־�ļ���
 * ʹ����־����Ժ󣬻����ݼ��ʱ��ȥ���Խ�����־�ļ���
 * Ĭ���������־�����ǿ����ġ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  logCheckInterval: ����Ƿ�����־�ļ��ļ��ʱ�䣬Ĭ��ֵΪ10�롣
 *                    ������ֵΪ0��ʾ����ԭ����ֵ�����ֵС��5����Ϊָ������Сֵ5��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_enableLog( MIO_VOID *mioCtx, MIO_UINT32 logCheckInterval );

/*
 * �ر���־���ܡ�
 * �������������ȥ�ر���־�ļ����ر��ļ��Ķ������ܲ���������Ч����Լ��һ��50�������ʱ��
 * ������������������ŵ��� MIO_enableLog ����ô��������п��ܲ����κ����á�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_disableLog( MIO_VOID *mioCtx );

/*
 * ��ӿ�ģ�����־�ļ���д��һ�����ݡ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  buf: ���������ָ��
 *  len: ��������ݳ���
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_logWrite( MIO_VOID *mioCtx, MIO_CONST MIO_BYTE *buf, MIO_INT32 len );

/*
 * ��ӿ�ģ�����־�ļ���д��һ�θ�ʽ�������ݡ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  format: ������ݵĸ�ʽ�������ʽ��μ�printf�ĸ�ʽ��
 *  ...: ��Ҫ��ʽ�����������
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_logVaWrite( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, ... );

/*
 * ���շ���ģ�����־�ļ���д��һ�θ�ʽ�������ݡ�
 * �����������һ���������������ڸ�ÿһ��Ҫ��ʽ��������ı��ṩ�˸��ӵĸ�ʽ�����ǰ׺��
 * Ŀǰ��Ҫ����mediasipģ���ж�osip��־���������
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  format: ������ݵĸ�ʽ�������ʽ��μ�printf�ĸ�ʽ��
 *  args: ����Ŀɱ����ݲ����б�
 *  preformat: ���ǰ׺�ĸ�ʽ�������ʽ��μ�printf�ĸ�ʽ��
 *  ...: ��Ҫ��ʽ�������ǰ׺
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_logVaWriteEx( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, va_list args, MIO_CONST MIO_CHAR *preformat, ... );

/*
 * ���������յ�������Ϣ�󣬵ȴ��ϲ�ģ�鷢�ͻ�Ӧ�����ĵȴ�ʱ�䡣
 * ���������ʱʱ���Ŀ�����ڣ����ϲ�ģ�鲻���ͻ�Ӧʱ����������շ���ģ���һЩ��ص���Դ��
 * �����ʱʱ���HTTP��Ϣ�������ã���ΪHTTP������õ��������Ȼ�Ӧ��ģʽ��
 * ���һ����Ϣ����Ӧ���ᵼ�º�������ϢҲû�а취��Ӧ��
 * ����ʱʱ�䵽��ʱ������HTTP��Ϣ���շ���ģ����Զ�����һ������Ļ�Ӧ��
 * ��Ϊ��ʱʱ����һ����ʱ��������HTTP��Ϣ������ϲ�ģ�鲻��Ӧ��
 * ֻ�е���ǰ��Ϣ��ʱ�Ժ�ſ��ܷ��ͺ�������Ӧ��Ч���ϻ��кܴ�Ľ��ͣ��������ϲ�ģ��ȷ��ÿһ����Ϣ���ᷢ�ͻ�Ӧ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  timeout: ��ʱʱ�䣬��λΪ�롣Ĭ��Ϊ64�롣
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setRespWaitTimeout( MIO_VOID *mioCtx, MIO_UINT32 timeout );

/*
 * ������ʼ���շ���ģ�顣�����������MIO_CreateCtx��MIO_CreateCtxEx�е��ã�
 * ��������ж���߳�ͬʱ����MIO_CreateCtx��MIO_CreateCtxExʱ����Ϊ��ʼ������������û����ɣ�
 * ���¿��ܳ������벻���Ĵ�����������ж���̵߳��û����MIO_CreateCtx��MIO_CreateCtxExʱ��
 * ��ȷ��������Ψһ��һ���ط����������������ʼ���շ���ģ�顣
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾ��ʼ���ɹ���
 *  MIO_FALSE ��ʾ��ʼ��ʧ�ܡ�
 *
 */
MIO_API MIO_BOOL MIO_initMIOModule( MIO_VOID );

/*
 * ����ж���շ���ģ�顣
 * �����ṩMIO_initMIOModuleͬ����ԭ��Ԥ������߳�ͬʱ����MIO_DestroyCtxʱ���ܲ����Ĵ���
 * ����ж���̵߳���MIO_DestroyCtxʱ����ȷ����Ψһ��һ���ط��������������ж���շ���ģ�顣
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_exitMIOModule( MIO_VOID );

/*
 * ������UTF-8�ַ�ת����GB2312�ַ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  utf8Str: ��Ҫ��ת����UTF-8�ַ���
 *  utf8StrLen: UTF-8�ַ����ĳ���
 *  gb2312Str: GB2312�ַ��������������
 *  gb2312StrLen: GB2312����������ĳ���
 *
 * ����ֵ��
 *  ת������д��GB2312�������е��ַ�����
 *
 */
MIO_API MIO_INT32 MIO_convUTF8ToGB2312( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen,
										MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen );

/*
 * ������GB2312�ַ�ת����UTF-8�ַ�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  gb2312Str: ��Ҫ��ת����GB2312�ַ���
 *  gb2312StrLen: GB2312�ַ����ĳ���
 *  utf8Str: UTF-8�ַ��������������
 *  utf8StrLen: UTF-8����������ĳ���
 *
 * ����ֵ��
 *  ת������д��UTF-8�������е��ַ�����
 *
 */
MIO_API MIO_INT32 MIO_convGB2312ToUTF8( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen,
										MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen );

/*
 * �������߽ӿ�ģ�飬�ϲ�Ӧ���ڷ�����Ϣ�ṹ��Я�����ַ�����GB2312����UTF-8��
 * ���ΪGB2312ʱ���ӿ�ģ����Ҫ����ת����UTF-8��
 * ���ΪUTF-8����ô�ӿ�ģ���ֱ�ӽ��������Ĭ�Ͻӿ�ģ����Ϊ��Ϣ�ṹ�е��ַ���ΪGB2312��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  bUseUTF8: ����ָʾ��Ϣ�ṹ��ʹ�õ��ַ����Ƿ�ΪUTF-8�ַ�
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setStrIOFlag( MIO_VOID *mioCtx, MIO_BOOL bUseUTF8 );

/*
 * ��������ʱ��ѹ��ģʽ
 */
typedef enum mioeDeflateMode{
	MIO_DM_NO_DEFLATE,		// ���Է��͵���Ϣ����ѹ��
	MIO_DM_DEFLATE,			// ��������Ϣ��ѹ������
	MIO_DM_AUTO_DEFLATE		// �ж�Ŀ���Ƿ���Խ���ѹ��
							// ������Խ���ѹ������ѹ��
							// ����ѹ����
							// �ж�Ŀ���Ƿ���Խ���ѹ���ķ����Ǹ���Ŀ��֮ǰ�����������ݰ��Ƿ������ѹ����
							// ���������ѹ�����ͱ�ʾ���Խ���ѹ������֮���ܡ�
							// �����û���յ���Ŀ���κ����ݰ�����ôĬ���ǲ�ѹ����
}mioeDeflateMode;

/*
 * �����������������Ϣ��ѹ������ģʽ��
 * ��Ϊ��ʱ����Ϣ���̫�󣬵���SIP��װ��UDP�����󣬵��³���IP��Ƭ������Ӱ�췢��Ч�ʡ�
 * ����ĳЩ�Ͷ˵�·��������NATת��ʱ�Ὣ��Ƭ�ĺ�����������
 * �������������������Ϣ�����һ����ѹ��������ѹ���ı���Ҳ�����ߡ�
 * ��ֻ�ܻ������⣬���ǲ��ܸ���������⡣
 * ��Ϊѹ����Ҫ�õ����з���Ԫ��һ�´�������ᵼ����Ϣ�޷�������
 * ����Ŀǰ����SIP��Content-Encodingͷ�ֶ���ָʾ��Ϣ�����Ƿ������ѹ����
 * ��Content-EncodingΪdeflateʱ����ʾ��Ϣ��ʹ����deflateѹ��������û�С�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  deflateMode: ������Ϣʱѹ���Ĵ���ģʽ
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setDeflateMode( MIO_VOID *mioCtx, mioeDeflateMode deflateMode );

/*
 * ��������Digest��֤��
 * ���ڻص��������յ�MIO_NC_RECV_REGISTER֪ͨʱ��
 * ���Խ�miosRegisterNotifyExtraParam�ṹ�еļ�������Լ��û������봫�����������������֤��
 *
 * �������壺
 *  nonce: SIP Authorization ͷ�ֶ��е� nonce
 *  cNonce: SIP Authorization ͷ�ֶ��е� cnonce
 *  user: SIP Authorization ͷ�ֶ��е� username
 *  realm: SIP Authorization ͷ�ֶ��е� realm
 *  pass: �������������
 *  alg: SIP Authorization ͷ�ֶ��е� algorithm
 *  nonceCount: SIP Authorization ͷ�ֶ��е� nc
 *  method: SIP ��Ϣ�ķ�����
 *  qop: SIP Authorization ͷ�ֶ��е� qop
 *  uri: SIP Authorization ͷ�ֶ��е� uri
 *  response: SIP Authorization ͷ�ֶ��е� response
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾ��֤�ɹ�
 *  MIO_FALSE ��ʾ��֤ʧ��
 *
 */
MIO_API MIO_BOOL MIO_calcAuthorization( MIO_CONST MIO_CHAR *nonce,
										MIO_CONST MIO_CHAR *cNonce,
										MIO_CONST MIO_CHAR *user,
										MIO_CONST MIO_CHAR *realm,
										MIO_CONST MIO_CHAR *pass,
										MIO_CONST MIO_CHAR *alg,
										MIO_CONST MIO_CHAR *nonceCount,
										MIO_CONST MIO_CHAR *method,
										MIO_CONST MIO_CHAR *qop,
										MIO_CONST MIO_CHAR *uri,
										MIO_CONST MIO_CHAR *response );

/*
 * �������IE�ṹ���ڴ��С
 *
 * �������壺
 *  type: IE�ı��ֵ
 *
 * ����ֵ��
 *  IE�ṹ���ڴ��С
 *
 */
MIO_API MIO_UINT32 MIO_getIESizeByType( mioeIEType type );

/*
 * ��������ʹ��HTTPͨѶ��ʱ���Ƿ�ʹ�ó����ӷ�ʽ��
 * ʹ�ó����ӵĿ�����Ҫ�������NAT�ڵ��豸������NAT�Ĵ�Խ��
 * Ĭ�����������HTTPЭ��ջ��ʹ�ö����ӵķ�ʽ�����ͻ�������Ӧ�Ժ�ͽ����ӶϿ���
 * �����ӵķ�ʽ���ǲ������Ͽ����ӣ���ͨѶ����һ�����ơ�
 * �����ķ�ʽ��һ���ȱ�ݣ��Ǿ��ǲ�������Ӧ�ĶϿ����ӡ�
 * ��HTTPЭ������һЩͷ�ֶ��������������ӵı��ֵģ���������İ汾����ʹ��������������Ӧ��
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  bEnableLongConn: �Ƿ�ʹ�ܳ�����
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_setHttpConnMode( MIO_VOID *mioCtx, MIO_BOOL bEnableLongConn );

/*
 * ������"YYYY-MM-DD hh:mm:ss"��ʽ��ʱ���ַ���ת������1970��1��1��������������
 *
 * �������壺
 *  time: �������1970��1��1������������
 *  srcStr: "YYYY-MM-DD hh:mm:ss"��ʽ��ʱ���ַ���
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾת���ɹ�
 *  MIO_FALSE ��ʾת��ʧ��
 *
 */
MIO_API MIO_BOOL MIO_decodeTime( MIO_TIME *time, MIO_CONST MIO_CHAR *srcStr );

/*
 * ����1970��1��1������������ת��������"YYYY-MM-DD hh:mm:ss"��ʽ��ʱ���ַ�����
 *
 * �������壺
 *  time: ������1970��1��1������������
 *  dstStr: ����"YYYY-MM-DD hh:mm:ss"��ʽ�����ʱ���ַ����Ļ�����
 *  avaLen: �������ĳ���
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾת���ɹ�
 *  MIO_FALSE ��ʾת��ʧ��
 *
 */
MIO_API MIO_BOOL MIO_encodeTime( MIO_TIME *time, MIO_CHAR *dstStr, MIO_INT32 avaLen );

/*
 * ����һ�������������
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  �����������
 *
 */
MIO_API MIO_UINT32 MIO_random( MIO_VOID );

/*
 * ����һ���ڴ棬
 * ���������Ҫ�������ӵĲ������ļ������кš���C����Ԥ����ĺ�__FILE__��__LINE__���Եõ���
 *
 * �������壺
 *  size: ��Ҫ������ڴ��С
 *  fileName: ���÷��亯�����ļ���
 *  lineNumber: ���÷��亯�����к�
 *
 * ����ֵ��
 *  ������ڴ�ָ��
 *
 */
MIO_API MIO_VOID* MIO_mallocDebug( MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );

/*
 * ���·���һ���ڴ棬
 * ���������Ҫ�������ӵĲ������ļ������кš���C����Ԥ����ĺ�__FILE__��__LINE__���Եõ���
 *
 * �������壺
 *  memblock: ԭ�����ڴ�ָ��
 *  size: �µķ����С
 *  fileName: ���÷��亯�����ļ���
 *  lineNumber: ���÷��亯�����к�
 *
 * ����ֵ��
 *  ������ڴ�ָ��
 *
 */
MIO_API MIO_VOID* MIO_reallocDebug( MIO_VOID *memblock, MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );

/*
 * �ͷ�һ���ڴ棬
 * ���������Ҫ�������ӵĲ������ļ������кš���C����Ԥ����ĺ�__FILE__��__LINE__���Եõ���
 *
 * �������壺
 *  memblock: ��Ҫ���ͷŵ��ڴ�ָ��
 *  fileName: �����ͷź������ļ���
 *  lineNumber: �����ͷź������к�
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_freeDebug( MIO_VOID *memblock, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );


/*
 * ����һ���ڴ档
 *
 * �������壺
 *  memblock: ��Ҫ���ͷŵ��ڴ�ָ��
 *
 * ����ֵ��
 *  ������ڴ�ָ��
 *
 */
MIO_API MIO_VOID* MIO_malloc( MIO_UINT32 size );

/*
 * ���·���һ���ڴ档
 *
 * �������壺
 *  memblock: ԭ�����ڴ�ָ��
 *  size: �µķ����С
 *
 * ����ֵ��
 *  ������ڴ�ָ��
 *
 */
MIO_API MIO_VOID* MIO_realloc( MIO_VOID *memblock, MIO_UINT32 size );

/*
 * �ͷ�һ���ڴ档
 *
 * �������壺
 *  memblock: ��Ҫ���ͷŵ��ڴ�ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_free( MIO_VOID *memblock );

/*
 * �������ýӿ�ģ����ڴ����ģʽ��
 * �����Ժ󣬽ӿ��˳�ʱ������־�ļ�������Ƿ����ڴ��Լ������ڴ�й©���ļ����кš�
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_enableMemDebug();

/*
 * �����رսӿ�ģ����ڴ����ģʽ��
 *
 * �������壺
 *  ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_disableMemDebug();

/*
 * �������������Ŀͻ��˽ӿ�ģ�飬����Ҫ�ṩ���ص������˿ڡ�
 * ��ʱֻ��ʹ��HTTP�Ŀͻ���ģʽȥ��������
 *
 * �������壺
 *  sipUserData: SIP�ص���Ϣ�лش����û���͸������
 *  sipNotifyCB: SIP֪ͨ�ص�
 *  httpUserData: HTTP�ص���Ϣ�лش����û���͸������
 *  httpNotifyCB: HTTP֪ͨ�ص������Ϊ�գ���ô��ʹ��sipNotifyCB��sipUserData��
 *
 * ����ֵ��
 *  ģ��������ָ�루MIO_NULL��ʾ����ʧ�ܣ�
 *
 */
MIO_API MIO_VOID* MIO_CreateCtxForClient( MIO_VOID *sipUserData,
											MIO_NotifyCB sipNotifyCB,
											MIO_VOID *httpUserData,
											MIO_NotifyCB httpNotifyCB );

/*
 * ��������SIP�������˿ںš�
 * ����Ѿ����ù��ˣ���ô����ú������á�
 * ������ʹ��MIO_CreateCtxForClient�����ӿ��Ժ������ö˿ںš�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  sipPort: SIP�������˿ں�
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾ���óɹ�
 *  MIO_FALSE ��ʾ����ʧ��
 *
 */
MIO_API MIO_BOOL MIO_setSipPort( MIO_VOID *mioCtx, MIO_UINT16 sipPort );

/*
 * ��������HTTP�������˿ںš�
 * ����Ѿ����ù��ˣ���ô����ú������á�
 * ������ʹ��MIO_CreateCtxForClient�����ӿ��Ժ������ö˿ںš�
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  httpPort: HTTP�������˿ں�
 *
 * ����ֵ��
 *  MIO_TRUE ��ʾ���óɹ�
 *  MIO_FALSE ��ʾ����ʧ��
 *
 */
MIO_API MIO_BOOL MIO_setHttpPort( MIO_VOID *mioCtx, MIO_UINT16 httpPort );


/*
 * ������������Ժ��������ע��ʧ�ܵ�ʱ�򣬲��ټ������������ע�ᡣ
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_enableStopRegWhenFail( MIO_VOID *mioCtx );

/*
 * ������������Ժ��������ע��ʧ�ܵ�ʱ�򣬻�������������ע�ᡣ
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_VOID MIO_disableStopRegWhenFail( MIO_VOID *mioCtx );

/*
 * ������ȥ��HTTP��Ϣ�Զ�����IEX_HEADER
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  msg: ��Ҫ�Զ�����IEX_HEADER����Ϣ
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_BOOL MIO_patchOutHttpMsg( MIO_VOID *mioCtx, miosMSG *msg );

/*
 * �����յ���HTTP��Ϣ�Զ���ȡIEX_HEADER�е�����
 *
 * �������壺
 *  mioCtx: �ӿ�ģ��������ָ��
 *  msg: ��Ҫ�Զ���ȡIEX_HEADER���ݵ���Ϣ
 *
 * ����ֵ��
 *  ��
 *
 */
MIO_API MIO_BOOL MIO_patchInHttpMsg( MIO_VOID *mioCtx, miosMSG *msg );



/////////////////////////////////////////////////////////////////////////////////
//	Ϊ�˺�mediasip��ͬ��windows��������ӵĺ���
//	�����Ϻ������ṩ�Ľӿں���һһ��Ӧ
//
//	ΪʲôҪ�����������ظ�������
//		����mediasip��windowsһ������ʱ���ǽ� MIO ģ������һ����̬�⣨staticmsgio.lib����
//	mediasip������dll��ʱ�����ӣ����ֱ��ʹ�þ�̬�����ӣ���ô��̬���ڵĺ���û�а취��dll�е�����
//	��˾���Ҫmediasip�ڱ����ʱ�򲻽����� staticmsgio.lib ����Ҫ���ӱ���һЩ������������̬���еĺ�����
//	��д�����ʵ�־��� miointerface.c �ļ�������ļ�������ֻ�����þ�̬���к����Ķ�����
//	��mediasip�ڱ����ʱ�򸽼ӱ�������ļ��Ϳ����ˡ�
//
//	������Щ�����ǽӿ�ģ����ڲ�����ʵ�ֺ���
//	�����ṩ������ʹ�õĽӿں��������϶����� miointerface.c ��ʵ��
/////////////////////////////////////////////////////////////////////////////////


MIO_VOID* MIO_CreateCtxExInternal( MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB);


MIO_VOID* MIO_CreateCtxInternal( MIO_UINT16 listenPort,
									MIO_VOID *userData);

MIO_VOID MIO_DestroyCtxInternal( MIO_VOID *mioCtx );


MIO_UINT32 MIO_SendMsgInternal( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_UINT32 msgID,
								miosMSG *msg,
								MIO_VOID *msgUserData,
								MIO_BOOL bEsRequest,
								MIO_CHAR *ip,
								MIO_UINT16 port );

MIO_UINT32 MIO_SendRegInternal( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_CHAR *userName,
								MIO_CHAR *passWord,
								MIO_INT32 expires,
								MIO_VOID *regUserData,
								MIO_CHAR *ip,
								MIO_UINT16 port );

MIO_UINT32 MIO_SendRegExInternal( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId );

MIO_BOOL MIO_cancelRegInternal( MIO_VOID *mioCtx,
								MIO_UINT32 regID );


MIO_UINT32 MIO_SendRegRespInternal( MIO_VOID *mioCtx,
									MIO_UINT32 msgID,
									MIO_INT32 respCode,
									MIO_CHAR *passWord );

MIO_UINT32 MIO_SendRegRespExInternal( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase );




miosMSG* MIO_mallocMsgHeaderInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_freeMsgHeaderInternal( MIO_VOID *mioCtx, miosMSG* msg );

MIO_VOID* MIO_mallocIEInternal( MIO_VOID *mioCtx, MIO_UINT32 size );

MIO_VOID MIO_freeIEInternal( MIO_VOID *mioCtx, MIO_VOID *ie, MIO_UINT32 size);

miosList* MIO_mallocListNodeInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_freeListNodeInternal( MIO_VOID *mioCtx, miosList *listNode );

MIO_VOID MIO_freeIEListInternal( MIO_VOID *mioCtx, miosList *ieList );

MIO_VOID MIO_freeWholeMsgInternal( MIO_VOID *mioCtx, miosMSG* msg );

MIO_BOOL MIO_guessLocalIPInternal( MIO_VOID *mioCtx, MIO_INT32 family, MIO_CHAR *ipAddr, MIO_INT32 len, MIO_CHAR *dest );

MIO_VOID MIO_handleExosipEvent( MIO_VOID *mioCtx, MIO_VOID *eXosipEvent );

miosMSG* MIO_decodeMSGInternal( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

MIO_INT32 MIO_encodeMSGInternal( MIO_VOID *mioCtx, miosMSG *msg, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

miosMSG* MIO_cloneWholeMsgInternal( MIO_VOID *mioCtx, miosMSG* msg );

MIO_VOID MIO_selfLearnDeviceIPInternal( MIO_VOID *mioCtx, MIO_BOOL bEnable );

MIO_VOID MIO_setCheckLearnDeviceIPCallBackInternal( MIO_VOID *mioCtx, MIO_checkLearnDeviceIPCB checkLearnDeviceIPCB );

MIO_BOOL MIO_addDeviceAddrInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

MIO_VOID MIO_removeDeviceAddrInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID );

MIO_VOID MIO_setLogLimitInternal( MIO_UINT32 totalBytes, MIO_UINT32 bytesPerFile );

MIO_VOID MIO_cancelSendingMsgInternal( MIO_VOID *mioCtx, MIO_UINT32 msgID );

MIO_VOID MIO_setUserMsgAndIEInternal( MIO_CONST miosUserMsgDef *userMsgList, MIO_CONST miosUserIEDef *userIEList );

MIO_CONST MIO_CHAR* MIO_getVersionStrInternal( MIO_VOID );

MIO_INT32 MIO_serializeMsgInternal( MIO_VOID *mioCtx, miosMSG* msg, MIO_BYTE *buf, MIO_INT32 len );

miosMSG* MIO_deserializeMsgInternal( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len );


MIO_BOOL MIO_initHTTPCtxInternal( MIO_VOID *mioCtx,
									MIO_INT32 listenIpFamily,
									MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB );

MIO_BOOL MIO_closeHTTPConnectionInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

MIO_VOID MIO_setHTTPConnectionTimeoutInternal( MIO_VOID *mioCtx, MIO_UINT32 timeout );


MIO_BOOL MIO_fillHTTPUrlInternal( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *ip,
									MIO_UINT16 port );

MIO_BOOL MIO_fillSIPUrlInternal( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *username,
									MIO_CHAR *ip,
									MIO_UINT16 port );


MIO_VOID MIO_setHTTPEncodeModeInternal( MIO_VOID *mioCtx, mioeHTTPEncodeMode encodeMode );

MIO_UINT32 MIO_SendHttpReqInternal( MIO_VOID *mioCtx,
									MIO_CHAR *url,
									miosMSG *msg,
									MIO_VOID *msgUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									mioeHTTPEncodeMode httpEncodeMode );

MIO_VOID MIO_enableDigestInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *realm );

MIO_VOID MIO_disableDigestInternal( MIO_VOID *mioCtx );

MIO_BOOL MIO_addAuthInfoInternal( MIO_VOID *mioCtx,
									MIO_CONST MIO_CHAR *deviceid,
									MIO_CONST MIO_CHAR *digestUserName,
									MIO_CONST MIO_CHAR *password );

MIO_VOID MIO_enableLogInternal( MIO_VOID *mioCtx, MIO_UINT32 logCheckInterval );

MIO_VOID MIO_disableLogInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_logWriteInternal( MIO_VOID *mioCtx, MIO_CONST MIO_BYTE *buf, MIO_INT32 len );

MIO_VOID MIO_logVaWriteInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, va_list args );

MIO_VOID MIO_logVaWriteExInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, va_list args, MIO_CONST MIO_CHAR *preformat, va_list preargs );

MIO_VOID MIO_setRespWaitTimeoutInternal( MIO_VOID *mioCtx, MIO_UINT32 timeout );

MIO_BOOL MIO_initMIOModuleInternal( MIO_VOID );

MIO_VOID MIO_exitMIOModuleInternal( MIO_VOID );


MIO_INT32 MIO_convUTF8ToGB2312Internal( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen,
										MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen );

MIO_INT32 MIO_convGB2312ToUTF8Internal( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen,
										MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen );

MIO_VOID MIO_setStrIOFlagInternal( MIO_VOID *mioCtx, MIO_BOOL bUseUTF8 );


MIO_VOID MIO_setDeflateModeInternal( MIO_VOID *mioCtx, mioeDeflateMode deflateMode );


MIO_BOOL MIO_calcAuthorizationInternal( MIO_CONST MIO_CHAR *nonce,
										MIO_CONST MIO_CHAR *cNonce,
										MIO_CONST MIO_CHAR *user,
										MIO_CONST MIO_CHAR *realm,
										MIO_CONST MIO_CHAR *pass,
										MIO_CONST MIO_CHAR *alg,
										MIO_CONST MIO_CHAR *nonceCount,
										MIO_CONST MIO_CHAR *method,
										MIO_CONST MIO_CHAR *qop,
										MIO_CONST MIO_CHAR *uri,
										MIO_CONST MIO_CHAR *response );

MIO_UINT32 MIO_getIESizeByTypeInternal( mioeIEType type );

MIO_VOID MIO_setHttpConnModeInternal( MIO_VOID *mioCtx, MIO_BOOL bEnableLongConn );

MIO_BOOL MIO_decodeTimeInternal( MIO_TIME *time, MIO_CONST MIO_CHAR *srcStr );
MIO_BOOL MIO_encodeTimeInternal( MIO_TIME *time, MIO_CHAR *dstStr, MIO_INT32 avaLen );

MIO_UINT32 MIO_randomInternal( MIO_VOID );

MIO_VOID* MIO_mallocDebugInternal( MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );
MIO_VOID* MIO_reallocDebugInternal( MIO_VOID *memblock, MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );
MIO_VOID MIO_freeDebugInternal( MIO_VOID *memblock, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );
MIO_VOID* MIO_mallocInternal( MIO_UINT32 size );
MIO_VOID* MIO_reallocInternal( MIO_VOID *memblock, MIO_UINT32 size );
MIO_VOID MIO_freeInternal( MIO_VOID *memblock );

MIO_VOID MIO_enableMemDebugInternal();
MIO_VOID MIO_disableMemDebugInternal();

MIO_VOID* MIO_CreateCtxForClientInternal( MIO_VOID *sipUserData,
											MIO_NotifyCB sipNotifyCB,
											MIO_VOID *httpUserData,
											MIO_NotifyCB httpNotifyCB );

MIO_BOOL MIO_setSipPortInternal( MIO_VOID *mioCtx, MIO_UINT16 sipPort );
MIO_BOOL MIO_setHttpPortInternal( MIO_VOID *mioCtx, MIO_UINT16 httpPort );


MIO_UINT32 MIO_SendRegEx2Internal( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId,
									miosMSG *msg );

MIO_UINT32 MIO_SendRegRespEx2Internal( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase,
										miosMSG *msg );

MIO_VOID MIO_enableStopRegWhenFailInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_disableStopRegWhenFailInternal( MIO_VOID *mioCtx );

MIO_BOOL MIO_patchOutHttpMsgInternal( MIO_VOID *mioCtx, miosMSG *msg );

MIO_BOOL MIO_patchInHttpMsgInternal( MIO_VOID *mioCtx, miosMSG *msg );

#ifdef __cplusplus
}
#endif



#endif


