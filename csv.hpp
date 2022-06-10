#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <assert.h>
#include <stdarg.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>

#else 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#endif

#include"baseFun.hpp"

using namespace std;

namespace pp
{	
	class CCsvFile
	{
	public:
		CCsvFile();
		CCsvFile(const string& logName)
			:m_logName(logName)
		{
			init();
		}

		~CCsvFile()
		{
			quit();
		}


		void init()
		{
			m_log.open((m_logName + "_" + CBase::getDateTimeS() + ".csv").c_str(), ios::app|ios::out);
		}


		void writeLine(const char* pformat, ...)
		{
			va_start(m_args, pformat);
			va_end(m_args);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, m_args);
			assert(m_log.is_open());

			m_log << m_logBuf << endl;
		}

		void quit()
		{
			m_log.close();
		}



	private:
		string m_logName;

		va_list					m_args;
		fstream					m_log;					

		char					m_logBuf[_LOG_BUFF_COUNT_];
	};
}
