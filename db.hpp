#pragma once
#include "log.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>


#include "mysql/mysql.h"

#ifdef _WIN32
	#pragma comment(lib, "libmysql.lib")
#endif

using namespace std;


namespace pp
{
	typedef vector<map<string, string> > DataType;

	class CDB
	{
	public:
		CDB(string host, int port, string dbName, string user, string pwd, CLog* log)
			:m_host(host)
			,m_port(port)
			,m_dbName(dbName)
			,m_user(user)
			,m_pwd(pwd)
			,m_log(log)
		{
			if (0 == mysql_library_init(0, NULL, NULL)) 
			{
				if (NULL != mysql_init(&m_db)) 
				{
					if (0 != mysql_options(&m_db, MYSQL_SET_CHARSET_NAME, "utf8"))
					{
						m_log->log_error( "[mysql]client set options failed!" );
					}
				}
				else
				{
					m_log->log_error("[mysql]client init failed!");
				}
			}

		}

		~CDB()
		{
			mysql_close(&m_db);
			mysql_library_end();
		}

		bool init()
		{
			if (NULL != mysql_real_connect(&m_db, m_host.c_str(), m_user.c_str(), m_pwd.c_str(), m_dbName.c_str(), m_port, NULL, 0)) 
			{
				m_log->log_debug("[mysql]connect mysql database, server:%s:%d database:%s user:%s", m_host.c_str(), m_port, m_dbName.c_str(), m_user.c_str());  
				return true;
			}
			else
			{
				m_log->log_error("[mysql]connect mysql database failed! server:%s:%d, %s user:%s", m_host.c_str(), m_port, m_dbName.c_str(), m_user.c_str());  
				return false;
			}
		}

		void close()
		{
			mysql_close(&m_db);
		}

		bool query(string queryStr)
		{
			mysql_close(&m_db);
			if(init() && 0 == mysql_query(&m_db, queryStr.c_str()))
			{
				m_log->log_info("[mysql]query:%s", queryStr.c_str()); 
				return true;
			}
			else
			{
				m_log->log_error("[mysql]%s query failed", mysql_error(&m_db));
				return false;
			}
		}


		bool exec_one(string queryStr)
		{
			mysql_close(&m_db);
			if(init() && 0 == mysql_query(&m_db, queryStr.c_str()))
			{
				mysql_commit(&m_db);
				m_log->log_info("[mysql]exec:%s", queryStr.c_str()); 
				return true;
			}
			else
			{
				mysql_rollback(&m_db);
				m_log->log_error("[mysql]%s exec_one failed rollback exec sql:%s", mysql_error(&m_db), queryStr.c_str());
				return false;
			}
		}

		bool exec(string queryStr)
		{
			if(0 == mysql_query(&m_db, queryStr.c_str()))
			{
				mysql_commit(&m_db);
				m_log->log_debug("[mysql]exec:%s", queryStr.c_str()); 
				return true;
			}
			else
			{
				mysql_rollback(&m_db);
				m_log->log_error("[mysql]%s exec failed rollback, exec sql:%s", mysql_error(&m_db), queryStr.c_str());
				return false;
			}
		}

		DataType getData()
		{
			MYSQL_RES *result = mysql_store_result(&m_db);
			int dataRow = mysql_num_rows(result);
			int fieldcount = mysql_num_fields(result);
			MYSQL_FIELD *field = NULL;
			MYSQL_ROW row = mysql_fetch_row(result);

			DataType dbData;
			map<string, string> retData;
			while(NULL != row)
			{
				for(size_t i = 0; i < fieldcount; ++i)
				{
					field = mysql_fetch_field_direct(result, i);
					char* data = row[i];
					
					retData[field->name] = NULL == data ? '\0' : row[i];
				}

				dbData.push_back(retData);
				retData.clear();            
				row = mysql_fetch_row(result);
			}

			mysql_free_result(result);
			return dbData;
		}

	private:
		
		string								m_host;
		int									m_port;
		string								m_user;
		string								m_pwd;
		string								m_dbName;
		boost::shared_ptr<CLog>			    m_log;

		MYSQL           m_db;
	};

}

