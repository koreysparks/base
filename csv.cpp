#include <string.h>
//#include <unistd.h> 

#include "csv.hpp"

namespace pp
{
	CCsvFile::CCsvFile()
	{}

	CCsvFile::CCsvFile(const string& logName)
		:m_logName(logName)
	{
		init();
	}

	void CCsvFile::init()
	{
		m_log.open((m_logName + "_" + getDateTimeS() + ".csv").c_str(), ios::app|ios::out);
	}


	CCsvFile::~CCsvFile()
	{
		quit();
	}

	struct tm CCsvFile::localTime()
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
	struct timespec CCsvFile::localTimeNs()
	{
		struct timespec timeNow;
		clock_gettime(CLOCK_REALTIME, &timeNow);
		return timeNow;
	}
#endif


	void CCsvFile::writeLine(const char* pformat, ...)
	{
		va_start(m_args, pformat);
		va_end(m_args);
		vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, m_args);
		assert(m_log.is_open());

		m_log << m_logBuf << endl;
	}

	void CCsvFile::quit()
	{
		m_log.close();
	}

	string CCsvFile::logDateTimeNS()
	{
		Time t;
		getTime(t);
		return t.Date + " " + t.TimeS + "." + t.Ns + " ";
	}

	string CCsvFile::getDateTimeNS()
	{
		Time t;
		getTime(t);
		return t.Date + " " + t.TimeS + "." + t.Ns;
	}

	string CCsvFile::getDateTimeS()
	{
		char dateC[12];
		char timeC[12];

		time_t now		= time(NULL);
		tm* ltm			= localtime(&now);

		sprintf(dateC, "%d%02d%02d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday);
		sprintf(timeC, "%02d%02d%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

		return string(dateC) + timeC;
	}

	string CCsvFile::getDate()
	{
		time_t now		= time(NULL);
		tm* ltm			= localtime(&now);

		char	dateC[12];
		memset( dateC, 0, sizeof(dateC) );
		sprintf( dateC, "%04d%02d%02d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday );
		return dateC;
	}

	void CCsvFile::getTime(Time& dateTime)
	{
		char dateC[12];
		char timeC[12];
		char nsC[10];
		struct tm timeNow;

#ifdef _WIN32
		timeNow = localTime();
		memset(nsC, 0 ,10);
#else
		struct timespec timeClock = localTimeNs();
		sprintf(nsC, "%09d", timeClock.tv_nsec);
		time_t localTime = (time_t)timeClock.tv_sec;
		timeNow = *localtime(&localTime);
#endif	

		sprintf(dateC, "%d-%02d-%02d", timeNow.tm_year + 1900, timeNow.tm_mon + 1, timeNow.tm_mday);
		sprintf(timeC, "%02d:%02d:%02d", timeNow.tm_hour, timeNow.tm_min, timeNow.tm_sec);

		dateTime.Date = dateC;
		dateTime.TimeS = timeC;
		dateTime.Ns = nsC;
	}



	void CCsvFile::sleep(size_t us)
	{
#ifdef _WIN32
		Sleep(us);
#else
		usleep(us);
#endif
	}

}

