#include "stdafx.h"
#define KEDA_AUDIO_API  extern "C"__declspec(dllimport)

typedef void (__stdcall *CBF_GetData)(void* pAudioBuf, int nAudioLen);


//////////////����������������

KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StartPlay();//���������ţ�
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StopPlay();
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_InputAudioData(char* pAudioBuf, int nAudioLen);
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_SetAudioVolume(WORD wVolume);



////////////////////////////////////////////////////////////////
//////////////�ص���������
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StartAudioIn();//�������ɼ���
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StopAudioIn();
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_SetAudioInCallback(CBF_GetData pCbf);