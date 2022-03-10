/*!****************************************************************************
	@date	    2011/2/17   17:21
	@file       mem_db_obj.h
	@author     liu.xianwei
	
    @brief      对内存数据库sqlite的封装,包装的方式完全等同于db_obj对mysql的包装
				这样可以提供一致的操作方式，方便使用
				使用示例：
				int rows = -1;
				mem_db_obj temp_db_obj();
				if(temp_db_obj.get_status())
				{
					rows = temp_db_obj.query_sql(p_sql);
					if (rows >= 0)
					{
						string strTemp1,strTemp2,strKey;
						double dTriggerPx1 = 0,dTriggerPx2 = 0;
						while (temp_db_obj.fetch_row())
						{
							strKey = temp_db_obj.get_field_data(0);

							strTemp1 = temp_db_obj.get_field_data(1);
							strKey += strTemp1;
							strTemp1 = temp_db_obj.get_field_data(2);
							strTemp2 = temp_db_obj.get_field_data(3);
							dTriggerPx1 = atof(temp_db_obj.get_field_data(4));
							dTriggerPx2 = atof(temp_db_obj.get_field_data(5));
						}
						temp_db_obj.fetch_end();
					}
				}
				else
				{
					err("db_obj get_status:false in up_cache_clordid_dbdata");
					return false;
				}

	@brief 如果要sqlite的使用物理数据库，则：
	mem_db_obj m_temp_db;
	 : m_temp_db(false)
	m_temp_db.init("testSqlite", true);
	@note  都是二进制的00000000-11111111, 也就是十六进制的00-FF. 长度都是1字节,取值范围不同：
			char:			-128~127
			unsigned char:	0~255 
			because lxw?conversion from 'const unsigned char*' to 'const char*'
			注意的地方：
			1. 输出。不光是十进制输出，十六进制的输出也不一样。
			2. 移位。对 char 执行算术移位，对 unsigned char 执行逻辑移位。
			3. 比较。排序。
	@note  之所以本目录下需要有mysql的include目录，是因为内存数据库和它共用了一个bin_data数据类型

	
******************************************************************************/
#pragma once
#include "sqlite_db.h"

namespace SHENGLI
{
	namespace DB
	{
		/// 内存数据库接口
		/**
			@brief      对内存数据库sqlite的封装,包装的方式完全等同于db_obj对mysql的包装			
		*/
		class SHENGLI_DB_API mem_db: public sqlite_db
		{
		public:
			mem_db();
			~mem_db(void);

			/// 初始化内存数据库的连接
			/**
				@return		bool 
			*/
			bool init_memory_db();

		};

	}

}



