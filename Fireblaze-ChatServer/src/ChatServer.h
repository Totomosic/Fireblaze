#pragma once
#include "chatpch.h"

namespace Fireblaze
{

	class FBL_API ChatServer
	{
	private:
		TCPsocket m_Server;
		SocketAddress m_Address;

	public:
		ChatServer();

		void Bind(const SocketAddress& address);
		void Listen(int backlog, bool spawnThread = true);

	private:
		void ListenInternal();
		void HandleClient(SocketAddress address, TCPsocket client);

	};

}