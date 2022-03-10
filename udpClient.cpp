#include "udpClient.hpp"
#include <assert.h>

namespace pp
{ 

	CUDPClient::CUDPClient (const char* host, int port, int localport)
	{
		//m_io_service = new io_service();     
		boost::asio::ip::address recvive = boost::asio::ip::address::from_string(host);
		m_reciver_endpoint = udp::endpoint(recvive, port);   //得到对方的套接字
		m_socket = new udp::socket(m_io_service, udp::endpoint(udp::v4(), localport));     
	}

	CUDPClient::~CUDPClient()
	{
		delete m_socket;     
		//delete m_io_service; 
	}

	size_t CUDPClient::sendto (const char* message, int len)
	{
		boost::asio::const_buffers_1 request(message, len);
		return m_socket->send_to(request, m_reciver_endpoint);
	}

	const char* CUDPClient::recv (int & num)     
	{
		num = m_socket->receive_from(boost::asio::buffer(m_response), m_reciver_endpoint);     
		if (num > 0)     
		{     
			return m_response;     
		}     

		return NULL;
	}
}



