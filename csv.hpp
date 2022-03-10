#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <assert.h>
#include <stdarg.h>

#include "log.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>

#else 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#endif

using namespace std;

namespace pp
{	
	class CCsvFile
	{
	public:
		CCsvFile();
		CCsvFile(const string& logName);
		~CCsvFile();

	public:
		void init();

	public:
		void writeLine(const char* pformat, ...);
		void quit();
		static string getDate();
		static string getDateTimeS();
		static string getDateTimeNS();
		static void sleep(size_t us);

	private:
		static void getTime(Time& dateTime);
		static struct tm localTime();
		string logDateTimeNS();

#ifdef _WIN32
#else
		static struct timespec localTimeNs();
#endif

	private:
		string m_logName;

		va_list					m_args;
		fstream					m_log;					// 普通日志

		char					m_logBuf[_LOG_BUFF_COUNT_];
	};
}
