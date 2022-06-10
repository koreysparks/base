#pragma once

#include "baseFun.hpp"
#include <assert.h>
#include <stdarg.h>
#include <cstdio>

#include <boost/thread/lock_types.hpp>
#include <boost/thread/shared_mutex.hpp>

#ifdef _WIN32
	#include <Windows.h>
	#include <direct.h>
#else 
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

typedef boost::shared_lock<boost::shared_mutex> readLock;
typedef boost:: unique_lock<boost::shared_mutex> writeLock;

using namespace std;

namespace pp
{	

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
	
	

	class CLog
	{
	public:
		CLog()
		{}

		CLog(const string& logName)
			:m_logName(logName)
		{
			init();
		}

		void init()
		{
			m_log.open((m_logName + "_" + CBase::getDate() + ".log").c_str(), ios::app|ios::out);
		}


		~CLog()
		{
			quit();
		}

		

		void log_info(const char* pformat, ...)
		{
			writeLock wtlock( m_wmutex );
			va_list	args;
			va_start(args, pformat);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
			va_end(args);
			assert(m_log.is_open());

			string timeNs = CBase::getDateTimeNS();
			string print = timeNs + " [info]" + m_logBuf + "\n";
			m_log <<  print;
			printf(print.c_str());
		}

		void log_debug(const char* pformat, ...)
		{
#ifdef _DEBUG
			writeLock wtlock( m_wmutex );
			va_list	args;
			va_start(args, pformat);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
			va_end(args);
			assert(m_log.is_open());

			string timeNs = CBase::getDateTimeNS();
			string print = timeNs + " [debug]" + m_logBuf + "\n";
			m_log << print;
#endif
		}

		void log_user(const char* pformat, ...)
		{
#ifdef _DEBUG
			writeLock wtlock( m_wmutex );
			va_list	args;
			va_start(args, pformat);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
			va_end(args);
			assert(m_log.is_open());

			string timeNs = CBase::getDateTimeNS();
			string print = timeNs + " [user]" + m_logBuf + "\n";
			m_log <<  print;
			printf(print.c_str());
#endif
		}

		void log_error(const char* pformat, ...)
		{
			writeLock wtlock( m_wmutex );
			va_list	args;
			va_start(args, pformat);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
			va_end(args);
			assert(m_log.is_open());

			string timeNs = CBase::getDateTimeNS();
			string print = timeNs + " [error]" + m_logBuf + "\n";
			m_log <<  print;
			printf(print.c_str());
		}


		void log_warn(const char* pformat, ...)
		{
			writeLock wtlock( m_wmutex );
			va_list	args;
			va_start(args, pformat);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
			va_end(args);
			assert(m_log.is_open());

			string timeNs = CBase::getDateTimeNS();
			string print = timeNs + " [warn]" + m_logBuf + "\n";
			m_log <<  print;
			printf(print.c_str());
		}

		void quit()
		{
			m_log.close();
		}

	private:
		string m_logName;								
		boost::shared_mutex		m_wmutex;
		fstream					m_log;					
		char					m_logBuf[_LOG_BUFF_COUNT_];
	};
}
