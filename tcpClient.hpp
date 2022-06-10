#pragma once

#include <boost/asio.hpp>  
#include <boost/bind.hpp>  
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <iostream>  
#include <string>


using namespace std;
using boost::asio::io_service;     
using boost::asio::ip::tcp;  

#define _BUF_COUNT_				(1000 * 1000 * 10) 

namespace pp
{	
	class CTCPClient
	{
	public:
		CTCPClient (const char* host, int port, int& result)
		{
			m_socket = new tcp::socket(m_io_service);     

			tcp::resolver resolver(m_io_service);     
			tcp::resolver::query query(host, boost::lexical_cast<string, unsigned short>(port));     

			boost::system::error_code ec;     
			tcp::resolver::iterator iter = resolver.resolve(query, ec);     
			tcp::resolver::iterator end;     

			// pick the first endpoint     
			if (iter != end && ec == 0)     
			{     
				tcp::endpoint endpoint = *iter;     
				m_socket->connect(endpoint, ec);     
				if (ec)     
				{     
					throw ec;     
				}     

				result = 0;
			}     
		}

		~CTCPClient()
		{
			delete m_socket;     
			//delete m_io_service; 
		}

		size_t send (const char* message, int len)
		{
			boost::asio::const_buffers_1 request(message, len);     
			return m_socket->send(request); 
		}

		const char* recv (int& num)     
		{    
			memset(m_response, 0, _BUF_COUNT_);
			num = m_socket->receive(boost::asio::buffer(m_response));    
			if(num >= _BUF_COUNT_)
			{
				printf("warn tcp recv buf is over, count:%d", _BUF_COUNT_);
			}

			if (num > 0)     
			{     
				return m_response;     
			}     

			return NULL;
		}

		void close ()
		{
			m_socket->close();
		} 

	private:     
		io_service m_io_service;     
		tcp::socket * m_socket; 
		char m_response[_BUF_COUNT_]; 
	}; 

}