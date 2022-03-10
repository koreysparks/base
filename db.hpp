#pragma once
#include "log.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>


#include "mysql/mysql.h"

#include "libbase.hpp"


using namespace std;


namespace pp
{
	typedef vector<map<string, string> > DataType;

	class CDB
	{
	public:
		CDB(string host, int port, string dbName, string user, string pwd, boost::shared_ptr<CLog> log);
		~CDB();

	public:

	
		bool query(string queryStr);
		vector<map<string, string> >& getData();


	private:

		bool init();
		
		
		
		
		
		string								m_host;
		int									m_port;
		string								m_user;
		string								m_pwd;
		string								m_dbName;
		boost::shared_ptr<CLog>			    m_log;

		MYSQL           m_db;

		// 数据    <filed, data>
		vector<map<string, string> > m_dbData;
	};

}

