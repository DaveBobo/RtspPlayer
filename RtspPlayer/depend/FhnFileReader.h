
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNFILEREADER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNFILEREADER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.


#ifdef FHNFILEREADER_EXPORTS
#define FHNFILEREADER_API __declspec(dllexport)
#else
#define FHNFILEREADER_API __declspec(dllimport)
#endif


#define  MEDIATYPE_VIDEO    1
#define  MEDIATYPE_AUDIO    2

enum filePlayMode
{
	FILE_NOINIT = 0,
	FILE_NOPLAY ,          /*����Ƶ״̬*/
	FILE_PLAYING,         /*��ͨ����״̬*/
	FILE_PAUSE,           /*��ͣ״̬*/
	FILE_FWORD,		   /*���*/
	FILE_BACK,			   /*����*/
	FILE_SLOW,            /*����*/
	FILE_FAST,            /*���*/

	FILE_PLAYSEEK,             /*���ֲ���״̬�µĶ�λ����*/
	FILE_FWORDSEEK,
	FILE_BACKSEEK,
	FILE_FASTSEEK,
	FILE_SLOWSEEK,

	FILE_SOLE,
	FILE_SOLESEEK

};


typedef struct _playctl_info
{
   	filePlayMode playmode;
	long speed;
	long scale;
	long seektime;
		
}playctl_info;

typedef struct file_info
{
	unsigned int		totalFrameNum;
	unsigned int		keyFrameNum;
	int					fileType ;		//�ļ����ͣ�mpg4 ��H264
	enumCoFileType		manufType;		//��������

}file_info;

typedef struct play_info
{
	loc_file_reply_type fileevent;
	void* pPlayFile;
	int errorcode;
}play_info;

typedef void(*fileplaycallback)(long filereader, long fileplayhandle, play_info *ppinfo);


FHNFILEREADER_API void* InitialFileReader(fileplaycallback proc);
FHNFILEREADER_API long StartPlayFile(void* fReader, char* filename, long position, long hplaywnd,long playhandle);
FHNFILEREADER_API int StopPlayFile(void* fReader,long playhandle);
FHNFILEREADER_API enumCoFileType GetManufType(void * fReader,long playhandle);
//�ļ����Ų�����������˿����ŵ�
FHNFILEREADER_API int PlayFileControl(void* fReader,long playhandle,playctl_info* playinfo);
FHNFILEREADER_API int GetFileState(void* fReader,long playhandle);
FHNFILEREADER_API long GetFileTotalTime(void* fReader,long playhandle);
FHNFILEREADER_API long GetFileCurTime(void* fReader,long playhandle);
FHNFILEREADER_API int GetFileInfo(void* fReader,long playhandle, file_info* fileinfo);
FHNFILEREADER_API int  CapPic(void* fReader,long playhandle,char* filepath);
FHNFILEREADER_API BOOL RefSurface(void* fReader,long playhandle);
FHNFILEREADER_API int CloseFileReader(void* fReader);



