#include "chatpch.h"
#include "ChatServer.h"

namespace Fireblaze
{

	ChatServer::ChatServer()
		: m_Server(), m_Address()
	{

	}

	void ChatServer::Bind(const SocketAddress& address)
	{
		m_Address = address;
		m_Server.Bind(address);
	}

	void ChatServer::Listen(int backlog, bool spawnThread)
	{
		m_Server.Listen(backlog);
		if (!spawnThread)
		{
			ListenInternal();
		}
		else
		{
			Task t = TaskManager::Run(std::bind(&ChatServer::ListenInternal, this));
		}
	}

	void ChatServer::ListenInternal()
	{
		SocketAddress fromAddress;
		while (true)
		{
			TCPsocket client = m_Server.Accept(&fromAddress);
			BLT_INFO("Client connected {}", fromAddress);
			Task t = TaskManager::Run(make_shared_function([this, fromAddress, client{ std::move(client) }]() mutable
				{
					HandleClient(std::move(fromAddress), std::move(client));
				}));
		}
	}

	void ChatServer::HandleClient(SocketAddress address, TCPsocket client)
	{
		char buffer[4096];
		while (true)
		{
			int received = client.Recv(buffer, sizeof(buffer));
			if (received > 0)
			{
				
			}
			else
			{
				break;
			}
		}
		BLT_INFO("Client disconnected {}", address);
	}

}