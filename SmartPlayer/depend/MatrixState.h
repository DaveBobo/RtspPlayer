#ifndef _MATRIX_STATE_H_
#define _MATRIX_STATE_H_

#include "stdafx.h"
#include "MatrixDll.h"
#include <string>
#include "msgdef.h"
#include "iedef.h"

#define CONTENT_LEN		1024

#define MASK_PLAY_STATE_ZERO			(0x00)
#define MASK_PLAY_STATE					(0x01)		
#define MASK_PLAY_STATE_ALM_ENABLE		(MASK_PLAY_STATE << 0)
#define MASK_PLAY_STATE_ALM_KEEPTIME	(MASK_PLAY_STATE << 1)
#define MASK_PLAY_STATE_VIDEO_SIZE		(MASK_PLAY_STATE << 2)
#define MASK_PLAY_STATE_ALL				(MASK_PLAY_STATE_ALM_ENABLE | MASK_PLAY_STATE_ALM_KEEPTIME | MASK_PLAY_STATE_VIDEO_SIZE)

/*add by lxf*/
enum CHANNEL_STATE
{
	CHANNEL_FREE = 0,
	
	//��·ʵʱ��Ƶ����״̬
	RTV_SET,
	RTV_START,
	RTV_PLAY,

	//��·��Ѳ����״̬
	POLL_SET,
	POLL_START,
	POLL_PLAY,

	COMPOUND_READY,
	EMPTY_VALUE = 1000,
};

enum COMPOUND_STATE
{
	COMPOUND_FREE = 100,

	COMPOUND_RTV_SET,
	COMPOUND_RTV_START,
	COMPOUND_RTV_PLAY,

	COMPOUND_POLL_SET,
	COMPOUND_POLL_START,
	COMPOUND_POLL_PLAY,
};

//�ϳ�ͨ��״̬(���ڼ���2.0�汾,���²��ŵ���Ƶͨ��״̬)
struct ChDetailState
{
	unsigned long mask;			//����

	char puid[20];
	int  chno;
	int  compno;
	int  almenable;		//����ʹ�ܱ�־
	int  almkeeptime;	//��������ʱ��
	int  videosize;		//��Ƶ��С��Ŀǰ֧�֣�ԭʼ��С��ȫ������
};

//ǰ�����ò���ʱ״̬(���ڼ���2.0�汾)
struct PuChPlayState
{
	int almenable;
	int  almkeeptime;	
	int  videosize;		
	char name[128]; /*��Ƶͨ������*/
};

//��Ѳ�б�,����puid, chno, ����Ƶͨ����״̬
struct PollPlayList
{
	PollPlayList * pnext;

	char puid[20];
	int  chno;
	int  interval;
	PuChPlayState chstate;
};

//����ͨ���ϳɲ��Ų��Ե�״̬��Ϣ
struct ComPlayState
{
	int  compno;		//�ϳ�ͨ����
	ComPlayState * pnext;
	PollPlayList * planlist;	//����ϳɵ���Ѳ�б�
	char name[128];
	COMPOUND_STATE state;
};

//����ͨ��״̬
struct ChannelState
{
	ChannelState * pnext;

	PollPlayList * planlist;	//��Ѳ�б�
	ComPlayState * comlist;		//�ϳ��б�

	int chno;
	CHANNEL_STATE playstate;	//��Ѳor�ϳ�
	int compoundNum;
	char name[1024]; /*��Ѳ����Ƶ����*/
};

//��������״̬
struct DuState
{
	DuState * pnext;

	ChannelState * pchannellist;
	char duid[32];
	BOOL baudio;
	BOOL bspeak;
	//�ж��Ƿ��Ѿ���ȡ�����ǰ����Ϣ
	BOOL bpuinfo;
};

MATRIXDLL_API DuState * SetDuState(char * duid, BOOL baudio = EMPTY_VALUE, BOOL bspeak = EMPTY_VALUE);
MATRIXDLL_API void SetDuChState(char * duid, int duchno, CHANNEL_STATE state, char * name = NULL, PuChannel * playlist = NULL);
MATRIXDLL_API void SetDuChReadyState(char * duid, int duchno, int comnum);
MATRIXDLL_API void SetDuCompChState(char * duid, int duchno, int comno, COMPOUND_STATE state, char * name = NULL, PuChannel * playlist = NULL);
/*����*/
MATRIXDLL_API DuState * FindDustate(char * duid);
MATRIXDLL_API ChannelState * FindChannelState(char * duid, int chno);
MATRIXDLL_API ComPlayState * FindCompoundState(char * duid, int chno, int compoundno);
/*ɾ������du״̬*/
MATRIXDLL_API void RemoveAllDuState();

/*��дDU״̬*/
MATRIXDLL_API void WriteDuState(char * username);
MATRIXDLL_API void ReadDuState(char * filepath);

#endif