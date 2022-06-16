#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <map>
#include <assert.h>
#include <stdarg.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#ifdef _WIN32
	#include <windows.h>
//	#ifndef _DEBUG
		#pragma warning(disable : 4996)
//	#endif

#else

	#define __USE_GNU
	#include <sched.h>
	#include <pthread.h>
	#include <sys/time.h> 
	#include <unistd.h>
	#include <linux/unistd.h>
	#include <linux/kernel.h>

#endif

using namespace std;

#define _MAX_DOUBLE_PRICE_VALUE_				1e+8
#define _MIN_DOUBLE_PRICE_VALUE_				1e-8

#define _MAX_DOUBLE_VALUE_						1e+30
#define _MIN_DOUBLE_VALUE_						1e-30


namespace pp
{

#define _TIME_S_				(1000 * 1000 )
#define _TIME_MS_				(1000) 
#define _TIME_US_				(1)

//g++  -g -ggdb3 -Wall -fPIC -o  pricetest priceTest.cpp 
struct Price6
{
protected:
	char m_val[6] ; 

public:
	Price6()
	{
		m_val[0] = 
			m_val[1] = 
			m_val[2] = 
			m_val[3] = 
			m_val[4] = 
			m_val[5] = 0 ;
	}

	Price6& operator = (double val)
	{
		long long l_val = (val + 0.00001) * 10000 ;
		memcpy(m_val, &l_val, 6) ;
		return *this ;
	}

	operator double ()
	{
		unsigned long long val = 0 ; 
		memcpy( &val, m_val, 6) ;
		return val * 1.0/ 10000 ;
	}
};

struct Time
{
	Time& operator=(const Time& t)
	{
		Date = t.Date;
		TimeS = t.TimeS;
		Ns = t.Ns;

		return *this;
	}

	bool empty()
	{
		if(Date.empty() || TimeS.empty() || Ns.empty())
		{
			return true;
		}

		return false;
	}
	
	string Date;
	string TimeS;
	string Ns;
};


class CBase
{
public:

	static string itoa(const int& t)
	{
		char buf[16];
		sprintf(buf, "%d", t);
		return buf;
	}

static long long int stol(const string& str)
{
	unsigned long long int res;
	istringstream is(str.c_str());
	is >> res;
	return res;
}

static string ltos(long long int longData)
{
	char buf[32];
	sprintf(buf, "%lld", longData);
	return string(buf);
}

static double stof(const string& str)
{
	double res;
	istringstream is(str.c_str());
	is >> res;
	return res;
}

static string ftos(double fData)
{
	if (!isValidDouble(fData))
	{
		return "0";
	}

	char buf[32];
	sprintf(buf, "%f", fData);
	
	return string(buf);
}

static string point0ftos(double fData)
{
	if (!isValidDouble(fData))
	{
		return "0";
	}

	char buf[32];
	sprintf(buf, "%.0f", fData);

	return string(buf);
}

static string point4ftos(double fData)
{
	if (!isValidDouble(fData))
	{
		return "0.0000";
	}

	char buf[500];
	sprintf(buf, "%.4f", fData);

	return string(buf);
}

static string point4Priceftos(double fData)
{
	if (!isValidPrice(fData))
	{
		return "0.0000";
	}

	char buf[500];
	sprintf(buf, "%.4f", fData);

	return string(buf);
}


static bool isValidPrice(double value)
{
	return ( value > _MIN_DOUBLE_PRICE_VALUE_ && value < _MAX_DOUBLE_PRICE_VALUE_);
}

static bool isValidDouble(double value)
{
	return (abs(value) > _MIN_DOUBLE_VALUE_ || abs(value) > _MAX_DOUBLE_VALUE_);
}

static bool bind_cpu(int cpu_id)
{
#ifndef _WIN32
		int	cpu = (int)sysconf(_SC_NPROCESSORS_ONLN);
		cpu_set_t	cpu_info;

		if(cpu < cpu_id)
		{
			return false;
		}

		CPU_ZERO(&cpu_info);
		CPU_SET(cpu_id, &cpu_info);

		int ret = pthread_setaffinity_np( pthread_self(), sizeof(cpu_set_t), &cpu_info );
		if(0 != ret)
		{
			printf("bind cpu failed  cpu id:%d  thread id:%d,  ret:%d\n", cpu_id, pthread_self(), ret);
			return false;
		}

		printf("bind cpu success  cpu id:%d thread id:%d\n", cpu_id, pthread_self());
#endif

		return true;
} 

static void converTimeStamp(unsigned long long int timeStamp, tm& tmResult, unsigned int& nanoSec)
{
	unsigned int sec;
	char* p = (char*)(&timeStamp);
	memcpy(&sec, p + 4, 4);
	memcpy(&nanoSec, p, 4);

#ifdef _WIN32
	time_t tt32 = (time_t)sec;
	localtime_s(&tmResult, &tt32);
#else
	time_t tt32 = (time_t)sec;
	localtime_r(&tt32, &tmResult);
#endif
	return;
}

static string converTimeStampToTimeNs(const string& timeStamp)
{
	long long int timeStampLong = stol(timeStamp);
	tm tmResult;
	unsigned int nanoSec;
	converTimeStamp(timeStampLong, tmResult, nanoSec);
	char realTime[19]; 
	sprintf(realTime, "%d-%02d-%02d %02d:%02d:%02d", 
			tmResult.tm_year + 1900, 
			tmResult.tm_mon + 1, 
			tmResult.tm_mday, 
			tmResult.tm_hour,
			tmResult.tm_min,
			tmResult.tm_sec);

	return realTime;
}

static void splitStr(vector<string>& children, const string& str, char splitchar)
{
	children.clear();
	string::size_type preplace = 0, curplace = 0;
	string substr;
	while(1)
	{
		curplace = str.find(splitchar, preplace);
		if(string::npos == curplace)
		{
			substr = str.substr(preplace, str.size() - preplace);
			children.push_back(substr);
			break;
		}
		else
		{
			substr = str.substr(preplace, curplace - preplace);
			children.push_back(substr);
			preplace = curplace + 1;
		}
	}
}

static void price6Test()
{
	double price8 = 0;
	while(1)
	{
		printf("%s", "please input your double price:");
		cin >> price8;
		printf("%f\n", price8);

		char* p = (char*)&price8;
		for(size_t i = 0; i < 8; ++i)
		{
			printf("%d ", *(p + i));
		}

		printf("\n");

		Price6 price6;
		long long l_val = (price8 + 0.00001) * 10000 ;
		memcpy(&price6, &l_val, 6) ;
		price8 = price6;
		for(size_t i = 0; i < 8; ++i)
		{
			printf("%d ", *(p + i));
		}

		printf("\n");
	}
}

static struct tm localTime()
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

#ifndef _WIN32 
static struct timespec localTimeNs()
{
	struct timespec timeNow;
	clock_gettime(CLOCK_REALTIME, &timeNow);
	return timeNow;
}
#endif

static string getDate()
{
	time_t now		= time(NULL);
	tm* ltm			= localtime(&now);

	char	dateC[12];
	memset( dateC, 0, sizeof(dateC) );
	sprintf( dateC, "%04d%02d%02d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday );
	return dateC;
}

static void _sleep_(int nMilliSeconds)
{
#ifdef _WIN32

	Sleep(nMilliSeconds);
#else

	usleep(1000 * nMilliSeconds);
#endif
}


static string getDateTimeNS()
{
	Time t;
	getTime(t);
	return t.Date + " " + t.TimeS + " " + t.Ns;
}

static string getDateTimeS()
{
	char dateC[12];
	char timeC[12];
	time_t now		= time(NULL);
	tm* ltm			= localtime(&now);
	sprintf(dateC, "%d%02d%02d", ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday);
	sprintf(timeC, "%02d%02d%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	return string(dateC) + timeC;
}

static void getTime(Time& dateTime)
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

static long timeDiffNS(const Time& a, const Time& b)
{
	if(a.Date == b.Date && a.TimeS == b.TimeS && a.Ns == b.Ns)
	{
		return 0;
	}

	vector<string> aResult, bResult;
	splitStr(aResult, a.TimeS, ':');
	splitStr(bResult, b.TimeS, ':');
	if(aResult.size() != 3 || bResult.size() != 3)
	{
		return 0;
	}

	return ((atoi(bResult[0].c_str()) - atoi(aResult[0].c_str())) 					 * 3600 * 1000000000 +
			(atoi(bResult[1].c_str()) - atoi(bResult[1].c_str())) 					 * 60   * 1000000000 +
			(atoi(bResult[2].c_str()) - atoi(aResult[2].c_str()))							* 1000000000 +
			(atoi(b.Ns.c_str()) 	  - atoi(a.Ns.c_str())) 		);
}

static vector<string> getTradingDates(string fileName)
{
	ifstream file;
	file.open(fileName.c_str());
	vector<string> tradingDates;
	if (!file.is_open())
	{
		printf("[error] can not open %s", fileName.c_str());
		return tradingDates;
	}

	string data;
	while (!file.eof())
	{
		getline(file, data);
#ifndef _WIN32
		size_t len = data.length();
		data = string(data.c_str(), data.c_str() + len - 1);
#endif  

		tradingDates.push_back(data);
	}

	return tradingDates;
}

static string getPreTradingDate(vector<string> tradingDates, string tradingDate)
{
	if(tradingDate == tradingDates[0])
	{
		printf("[warn] trading date is the first date in tradeing dates");
		return "";
	}

	int pos = 0;
	for(size_t i = 1; i < tradingDates.size(); ++i)
	{	
		if(tradingDate == tradingDates[i])
		{
			return tradingDates[pos];
		}
		else
		{
			pos = i;
		}
	}

	return "";
}

};


#ifdef _WIN32
	typedef struct tm T_TIME;
	inline long clock()
	{
		return ::clock();
	}
	inline long tick()
	{
		return GetTickCount();
	}
	inline void sleep(int ms)
	{
		Sleep(ms);
	}
	inline void now(T_TIME & time)
	{
		SYSTEMTIME ct;
		GetLocalTime(&ct);
		time.tm_mday = ct.wDay;
		time.tm_wday = ct.wDayOfWeek;
		time.tm_hour = ct.wHour;
		time.tm_min = ct.wMinute;
		time.tm_mon = ct.wMonth;
		time.tm_sec = ct.wSecond;
		time.tm_year = ct.wYear;
	}
	inline void utcnow(T_TIME & time)
	{
		SYSTEMTIME ct;
		GetSystemTime(&ct);
		time.tm_mday = ct.wDay;
		time.tm_wday = ct.wDayOfWeek;
		time.tm_hour = ct.wHour;
		time.tm_min = ct.wMinute;
		time.tm_mon = ct.wMonth;
		time.tm_sec = ct.wSecond;
		time.tm_year = ct.wYear;
	}


#else
	typedef struct tm T_TIME;
	inline long clock()
	{
		return ::clock()/1000;
	}
	inline long tick()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return tv.tv_sec*1000+tv.tv_usec/1000;
	}
	inline void sleep(int ms)
	{
		struct timespec req;
		req.tv_nsec = ms%1000;
		req.tv_sec = (ms-req.tv_nsec)/1000;
		req.tv_nsec = req.tv_nsec*1000000;
		struct timespec rem;
		nanosleep(&req, &rem);
	}
	inline void now(T_TIME & time)
	{
		time_t ct = ::time(NULL);
		localtime_r(&ct, &time);
		time.tm_year += 1900;
	}
	inline void utcnow(T_TIME & time)
	{
		time_t ct = ::time(NULL);
		gmtime_r(&ct, &time);
		time.tm_year += 1900;
	}



#endif

inline char * format(char * buff, const T_TIME & time)
{
	sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d",
			time.tm_year, time.tm_mon, time.tm_mday, 
			time.tm_hour, time.tm_min, time.tm_sec);
	return buff;
}
inline char * format(char * buff, int len, const char * fmt, const T_TIME & time)
{
	strftime(buff, len, fmt, &time);
	return buff;
}
inline char * fmttime(char * buff, const T_TIME & time)
{
	sprintf(buff, "%02d:%02d:%02d",
			time.tm_hour, time.tm_min, time.tm_sec);
	return buff;
}
inline char * fmtdate(char * buff, const T_TIME & time)
{
	sprintf(buff, "%04d-%02d-%02d",
			time.tm_year, time.tm_mon, time.tm_mday);
	return buff;
}



}
