#include "tcpClient.hpp"

namespace pp
{ 
	CTCPClient::CTCPClient (const char* host, int port, int& result)
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

	CTCPClient::~CTCPClient()
	{
		delete m_socket;     
		//delete m_io_service; 
	}

	size_t CTCPClient::send (const char* message, int len)
	{
		boost::asio::const_buffers_1 request(message, len);     
		return m_socket->send(request); 
	}

	const char* CTCPClient::recv (int& num)     
	{    
		num = m_socket->receive(boost::asio::buffer(m_response));     
		if (num > 0)     
		{     
			return m_response;     
		}     

		return NULL;
	}

	void CTCPClient::close ()
	{
		m_socket->close();
	}

}



