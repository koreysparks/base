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

#define _BUF_COUNT_				1024

namespace pp
{	
	class CUDPClient
	{

	public:
		CUDPClient (const char* host, int port, int localport);
		~CUDPClient();   

		// methods     
		virtual size_t sendto (const char* message, int len);     
		virtual const char* recv (int & num);        

	private:     
		io_service m_io_service;     
		udp::socket * m_socket; 
		udp::endpoint m_reciver_endpoint;
		char m_response[_BUF_COUNT_]; 
	}; 

}