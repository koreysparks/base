#include <string.h>

#include "log.hpp"

namespace pp
{

	void _sleep_(int nMilliSeconds)
	{
#ifdef _WIN32

		Sleep(nMilliSeconds);
#else

		usleep(1000* nMilliSeconds);

#endif

	}


	CLog::CLog()
	{}
	
	CLog::CLog(const string& logName, bool isPrint)
		:m_isPrint(isPrint)
		,m_logName(logName)
	{
		init();
	}

	void CLog::init()
	{
		m_log.open((m_logName + "_" + getDate() + ".log").c_str(), ios::app|ios::out);
	}
	

	CLog::~CLog()
	{
		quit();
	}

	struct tm CLog::localTime()
	{
		time_t timeNow = time(NULL);
		struct tm timeInfo;
	
	#ifdef _WIN32
		localtime_s(&timeInfo, &timeNow);
		return timeInfo;
	#else
		return *localtime(&timeNow);
	#endif
	
	}
	
#ifdef _WIN32 
#else
	struct timespec CLog::localTimeNs()
	{
		struct timespec timeNow;
		clock_gettime(CLOCK_REALTIME, &timeNow);
		return timeNow;
	}
#endif

	void CLog::log(const char* pformat, ...)
	{
		writeLock wtlock( m_wmutex );
		va_list	args;
		va_start(args, pformat);
		vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
		va_end(args);
		assert(m_log.is_open());
	
		string timeNs = logDateTimeNS();
		m_log << timeNs << m_logBuf << endl;

		if(m_isPrint)
		{
			if(strstr(m_logBuf, "error"))
			{
				printf( RED_PRINTF , (timeNs + m_logBuf).c_str());
			}

			if(strstr(m_logBuf, "warn"))
			{
				printf(YELLOW_PRINTF, (timeNs + m_logBuf).c_str());
			}

			if(strstr(m_logBuf, "info"))
			{
				cout << GREEN_PRINTF << (timeNs + m_logBuf) << endl;
			}

			if(strstr(m_logBuf, "debug"))
			{
				printf(BLUE_PRINTF, (timeNs + m_logBuf).c_str());
			}
		}
	}
	
	void CLog::quit()
	{
		m_log.close();
	}

	string CLog::logDateTimeNS()
	{
		Time t;
		getTime(t);
		return t.Date + " " + t.TimeS + "." + t.Ns + " ";
	}

	string CLog::getDateTimeNS()
	{
		Time t;
		getTime(t);
		return t.Date + " " + t.TimeS + "." + t.Ns;
	}

	string CLog::getDateTimeS()
	{
		char dateC[12];
		char timeC[12];

		time_t now		= time(NULL);
		tm* ltm			= localtime(&now);

		sprintf(dateC, "%d%02d%02d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday);
		sprintf(timeC, "%02d%02d%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

		return string(dateC) + timeC;
	}

	void CLog::getTime(Time& dateTime)
	{
		char dateC[12];
		char timeC[12];
		char nsC[10];
		struct tm timeNow;

#ifdef _WIN32
		timeNow = localTime();
		memset(nsC, 0 ,10);
		dateTime.Ns = "000";
#else
		struct timespec timeClock = localTimeNs();
		sprintf(nsC, "%09d", timeClock.tv_nsec);
		time_t localTime = (time_t)timeClock.tv_sec;
		timeNow = *localtime(&localTime);
		dateTime.Ns = nsC;
#endif	

		sprintf(dateC, "%d-%02d-%02d", timeNow.tm_year + 1900, timeNow.tm_mon + 1, timeNow.tm_mday);
		sprintf(timeC, "%02d:%02d:%02d", timeNow.tm_hour, timeNow.tm_min, timeNow.tm_sec);
		dateTime.Date = dateC;
		dateTime.TimeS = timeC;
	}
	
	string CLog::getDate()
	{
		time_t now		= time(NULL);
		tm* ltm			= localtime(&now);

		char	dateC[12];
		memset( dateC, 0, sizeof(dateC) );
		sprintf( dateC, "%04d%02d%02d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday );
		return dateC;
	}

	
	
}

