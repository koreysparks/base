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

#define _BUF_COUNT_				1024

namespace pp
{	
	class CTCPClient
	{

	public:
		CTCPClient(const char* host, int port, int& result);
		~CTCPClient();   

		// methods     
		virtual size_t send (const char* message, int len);     
		virtual const char* recv (int& num);       
		virtual void close ();  

	private:     
		io_service m_io_service;     
		tcp::socket * m_socket; 
		char m_response[_BUF_COUNT_]; 
	}; 

}