#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <assert.h>
#include <stdarg.h>
#include <cstdio>

#include <boost/thread/lock_types.hpp>
#include <boost/thread/shared_mutex.hpp>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>

#define RED_PRINTF				"%s\n"	//"\033[31m"
#define GREEN_PRINTF			"%s\n"	//"\033[32m"
#define YELLOW_PRINTF			"%s\n"	//"\033[33m"
#define BLUE_PRINTF				"%s\n"	//"\033[34m"
#define PINK_PRINTF				"%s\n"	//"\033[35m"
#define CYAN_PRINTF				"%s\n"	//"\033[36m"


#else 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define RED_PRINTF				"\033[31m%s\n"
#define GREEN_PRINTF			"\033[32m%s\n"
#define YELLOW_PRINTF			"\033[33m%s\n"
#define BLUE_PRINTF				"\033[34m%s\n"
#define PINK_PRINTF				"\033[35m%s\n"
#define CYAN_PRINTF				"\033[36m%s\n"
#endif





typedef boost::shared_lock<boost::shared_mutex> readLock;
typedef boost:: unique_lock<boost::shared_mutex> writeLock;

using namespace std;

namespace pp
{	

#define _TIME_S_				(1000 * 1000 )
#define _TIME_MS_				1000 
#define _TIME_US_				1

#define	_LOG_BUFF_COUNT_		2048 

	enum LogLevel
	{
		_LOG_NONE_ = 0,
		_LOG_INFO_ ,
		_LOG_DEBUG_ ,
		_LOG_WARN_ ,
		_LOG_USER_ ,
		_LOG_ERROR_
	};
	
	struct Time
	{
		string Date;
		string TimeS;
		string Ns;
	};
	
	void _sleep_(int nMilliSeconds);

	class CLog
	{
	public:
		CLog();
		CLog(const string& logName, bool isPrint = false);
		~CLog();
	
	public:
		void init();
	
	public:
		void log(const char* pformat, ...);
		void quit();
		static string getDate();
		static string getDateTimeS();
		static string getDateTimeNS();

		static void getTime(Time& dateTime);
		static struct tm localTime();
		string logDateTimeNS();

#ifdef _WIN32
#else
		static struct timespec localTimeNs();
#endif
	
	private:
		string m_logName;
		bool m_isPrint;									// 是否打印
		boost::shared_mutex		m_wmutex;
		fstream					m_log;					// 普通日志
		char					m_logBuf[_LOG_BUFF_COUNT_];
	};
}
