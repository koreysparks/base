#pragma once

#include <boost/asio.hpp>  
#include <boost/bind.hpp>  
#include <boost/lexical_cast.hpp>  
#include <iostream>  
#include <string>
#include <boost/array.hpp>


using namespace std;
using boost::asio::io_service;     
using boost::asio::ip::udp;  

#define _BUF_COUNT_				(1000 * 1000 * 10) 

namespace pp
{	
	class CUDPClient
	{

	public:
		CUDPClient (const char* host, int port, int localport)
		{
			//m_io_service = new io_service();     
			boost::asio::ip::address recvive = boost::asio::ip::address::from_string(host);
			m_reciver_endpoint = udp::endpoint(recvive, port);   //得到对方的套接字
			m_socket = new udp::socket(m_io_service, udp::endpoint(udp::v4(), localport));     
		}

		~CUDPClient()
		{
			delete m_socket;     
			//delete m_io_service; 
		}

		size_t sendto (const char* message, int len)
		{
			boost::asio::const_buffers_1 request(message, len);
			return m_socket->send_to(request, m_reciver_endpoint);
		}

		const char* recv (int & num)     
		{

			memset(m_response, 0, _BUF_COUNT_);
			num = m_socket->receive_from(boost::asio::buffer(m_response), m_reciver_endpoint);     
			if(num >= _BUF_COUNT_)
			{
				printf("warn udp recv buf is over, count:%d", _BUF_COUNT_);
			}
			
			if (num > 0)     
			{     
				return m_response;     
			}     

			return NULL;
		}     

	private:     
		io_service m_io_service;     
		udp::socket * m_socket; 
		udp::endpoint m_reciver_endpoint;
		char m_response[_BUF_COUNT_]; 
	}; 

}