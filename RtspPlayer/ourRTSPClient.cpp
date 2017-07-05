/*********************************************************** 
		�ļ���:		ourRTSPClient.cpp

		�༭����:	Microsoft Visual Studio 2010

		����:		UESTC-PRMI

		����ʱ��:	2014-10-18

		�޸���:		
		
		�޸�ʱ��:

		��Ҫ����:	Rtsp�ͻ�����,�̳�Live555��RTSPClient��
***********************************************************/ 

#include "ourRTSPClient.h"
#include "StaticData.h"

// StreamClientState���Ա������ʵ��
StreamClientState::StreamClientState()
  : iter(NULL), session(NULL), subsession(NULL), streamTimerTask(NULL), duration(0.0) {
}

StreamClientState::~StreamClientState() {
  delete iter;
  if (session != NULL) {
    // We also need to delete "session", and unschedule "streamTimerTask" (if set)
    UsageEnvironment& env = session->envir(); // alias

    env.taskScheduler().unscheduleDelayedTask(streamTimerTask);
    Medium::close(session);
  }
}

// ourRTSPClient���Ա������ʵ��
ourRTSPClient* ourRTSPClient::createNew(UsageEnvironment& env, char const* rtspURL,
					int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum) 
{
  return new ourRTSPClient(env, rtspURL, verbosityLevel, applicationName, tunnelOverHTTPPortNum);
}

ourRTSPClient::ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
			     int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum)
  : RTSPClient(env,rtspURL, verbosityLevel, applicationName, tunnelOverHTTPPortNum, -1) 
{
}

ourRTSPClient::~ourRTSPClient()
{
}


// MyUsageEnvironment��Ա������ʵ��
MyUsageEnvironment::MyUsageEnvironment(TaskScheduler& taskScheduler):BasicUsageEnvironment(taskScheduler)
{
	fp = fopen(LOGFILE, "w");
}

int MyUsageEnvironment::getErrno() const
{
	int Re = BasicUsageEnvironment::getErrno();
	return Re;
}

UsageEnvironment&  MyUsageEnvironment::operator<<(char const* str)
{
	if(isOpenfp())
		fwrite(str, strlen(str), 1, fp);

#ifdef SAVE_LOG_TO_CSTRING
	DisInfo += str;
#endif
	return *this;
}

UsageEnvironment&  MyUsageEnvironment::operator<<(int i)
{
	if(isOpenfp())
		fprintf(fp, "%d", i);

#ifdef SAVE_LOG_TO_CSTRING
	CString Temp = "\0";
	Temp.Format("%d", i);
	DisInfo += Temp;
#endif
	return *this;
}

UsageEnvironment&  MyUsageEnvironment::operator<<(unsigned u)
{
	//fwrite(&u, sizeof(unsigned), 1, fp);
	if(isOpenfp())
		fprintf(fp, "%u", u);

#ifdef SAVE_LOG_TO_CSTRING
	CString Temp = "\0";
	Temp.Format("%u", u);
	DisInfo += Temp;
#endif

	return *this;
}

UsageEnvironment&  MyUsageEnvironment::operator<<(double d)
{
	//fwrite(&d, sizeof(double), 1, fp);
	if(isOpenfp())
		fprintf(fp, "%f", d);

#ifdef SAVE_LOG_TO_CSTRING
	CString Temp = "\0";
	Temp.Format("%f", d);
	DisInfo += Temp;
#endif
	return *this;
}

UsageEnvironment&  MyUsageEnvironment::operator<<(void* p)
{
	if(isOpenfp())
		fwrite(p, 1, 1, fp);

#ifdef SAVE_LOG_TO_CSTRING
	DisInfo += (char*)p;
#endif
	return *this;
}

MyUsageEnvironment* MyUsageEnvironment::createNew(TaskScheduler& taskScheduler)
{
	return new MyUsageEnvironment(taskScheduler);
}

bool MyUsageEnvironment::isOpenfp()
{
	if(NULL == fp)
		return false;
	else
		return true;
}


MyUsageEnvironment::~MyUsageEnvironment()
{
	BasicUsageEnvironment::~BasicUsageEnvironment();
	fclose(fp);
	fp = NULL;
}