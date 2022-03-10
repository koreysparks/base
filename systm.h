#pragma once


#ifdef _WIN32
	#include <stdio.h>
	#include <time.h>
	#include <windows.h>
//	#ifndef _DEBUG
		#pragma warning(disable : 4996)
//	#endif

#else
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <sys/time.h> 
#endif


/**
win32/linux system time.
*/
namespace pp
{

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
















