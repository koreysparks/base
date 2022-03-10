/*!****************************************************************************
	@date	    2011/2/17   17:21
	@file       mem_db_obj.h
	@author     liu.xianwei
	
    @brief      ���ڴ����ݿ�sqlite�ķ�װ,��װ�ķ�ʽ��ȫ��ͬ��db_obj��mysql�İ�װ
				���������ṩһ�µĲ�����ʽ������ʹ��
				ʹ��ʾ����
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

	@brief ���Ҫsqlite��ʹ���������ݿ⣬��
	mem_db_obj m_temp_db;
	 : m_temp_db(false)
	m_temp_db.init("testSqlite", true);
	@note  ���Ƕ����Ƶ�00000000-11111111, Ҳ����ʮ�����Ƶ�00-FF. ���ȶ���1�ֽ�,ȡֵ��Χ��ͬ��
			char:			-128~127
			unsigned char:	0~255 
			because lxw?conversion from 'const unsigned char*' to 'const char*'
			ע��ĵط���
			1. �����������ʮ���������ʮ�����Ƶ����Ҳ��һ����
			2. ��λ���� char ִ��������λ���� unsigned char ִ���߼���λ��
			3. �Ƚϡ�����
	@note  ֮���Ա�Ŀ¼����Ҫ��mysql��includeĿ¼������Ϊ�ڴ����ݿ����������һ��bin_data��������

	
******************************************************************************/
#pragma once
#include "sqlite_db.h"

namespace SHENGLI
{
	namespace DB
	{
		/// �ڴ����ݿ�ӿ�
		/**
			@brief      ���ڴ����ݿ�sqlite�ķ�װ,��װ�ķ�ʽ��ȫ��ͬ��db_obj��mysql�İ�װ			
		*/
		class SHENGLI_DB_API mem_db: public sqlite_db
		{
		public:
			mem_db();
			~mem_db(void);

			/// ��ʼ���ڴ����ݿ������
			/**
				@return		bool 
			*/
			bool init_memory_db();

		};

	}

}



