/****************************************************** 
		�ļ���:		ourRTSPClient.h : ͷ�ļ�

		�༭����:	Microsoft Visual Studio 2010

		����:		UESTC-PRMI

		����ʱ��:	2014-10-18

		�޸���:		
		
		�޸�ʱ��:

		��Ҫ����:	1.	ourRTSPClient����ɶ�RTSPClient
						��ļ̳�,ʵ��RTSP�ͻ���

					2.	MyUsageEnvironment����ɶ�
						BasicUsageEnvironment�ļ̳�,����
 						�������,ʹlog�ܹ�������ı��ĵ�
						��
******************************************************/ 

#pragma once
#include "stdafx.h"
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"

#pragma comment (lib, "Ws2_32.lib")  
#pragma comment (lib, "BasicUsageEnvironment.lib")
#pragma comment (lib, "groupsock.lib")
#pragma comment (lib, "liveMedia.lib")
#pragma comment (lib, "UsageEnvironment.lib")

// ourRTSPClient�ĳ�Ա��
class StreamClientState
{
public:
  StreamClientState();
  virtual ~StreamClientState();

public:
  MediaSubsessionIterator* iter;
  MediaSession* session;
  MediaSubsession* subsession;
  TaskToken streamTimerTask;
  double duration;
};

// 
class ourRTSPClient: public RTSPClient 
{
public:
  static ourRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
				  int verbosityLevel = 0,
				  char const* applicationName = NULL,
				  portNumBits tunnelOverHTTPPortNum = 0);
  virtual ~ourRTSPClient();

protected:
  ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
		int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum);
    // called only by createNew();
  

public:
	StreamClientState scs;
};

// ��BasicUsageEnvironment��ļ̳У���Ҫ��ɲ�����������

// �������Ҫ�������LOG�Ļ���ע�����漸�У�
//#define SAVE_LOG_TO_CSTRING (1)
//#define MAX_LOG_LEN (1024 * 10)
//static CString DisInfo = "\0";

//static CString *Log = &DisInfo;
//char* Log = new char[MAX_LOG_LEN];

class MyUsageEnvironment: public BasicUsageEnvironment {
public:
  static MyUsageEnvironment* createNew(TaskScheduler& taskScheduler);

  // redefined virtual functions:
  virtual int getErrno() const;

  virtual UsageEnvironment& operator<<(char const* str);
  virtual UsageEnvironment& operator<<(int i);
  virtual UsageEnvironment& operator<<(unsigned u);
  virtual UsageEnvironment& operator<<(double d);
  virtual UsageEnvironment& operator<<(void* p);


//protected:
  MyUsageEnvironment(TaskScheduler& taskScheduler);
      // called only by "createNew()" (or subclass constructors)
  virtual ~MyUsageEnvironment();
private:
	FILE* fp;
	bool isOpenfp();
};