#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <assert.h>
#include <stdarg.h>
#include <cstdio>

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
	
	class CFile
	{
	public:
		CFile()
		{}

		CFile(const string& logName)
			:m_logName(logName)
		{
			init();
		}

		void init()
		{
			m_log.open(m_logName.c_str(), ios::app|ios::out);
		}


		~CFile()
		{
			quit();
		}

		void writeLine(const char* pformat, ...)
		{
			va_list	args;
			va_start(args, pformat);
			vsnprintf(m_logBuf, sizeof(m_logBuf), pformat, args);
			va_end(args);
			assert(m_log.is_open());

			m_log << m_logBuf << endl;
		}


		void quit()
		{
			m_log.close();
		}

		
	
	private:
		string m_logName;							
		fstream					m_log;					
		char					m_logBuf[4096];
	};
}
