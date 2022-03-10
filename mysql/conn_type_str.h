#pragma  once 

#include "shengli_db.h"

namespace SHENGLI
{
	namespace DB
	{
		/// 数据库连接字符串的类型标识
		struct SHENGLI_DB_API conn_str_type
		{
			static const char* mysql_type ;	///< mysql 
			static const char* memory_type ;	///< memory 
			static const char* sqlite_type ;	///< sqlite	  			
		};

	}
}

