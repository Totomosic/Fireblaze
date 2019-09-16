#pragma once
#include "gspch.h"

namespace Fireblaze
{

	struct FBL_API PlayerConnection
	{
	public:
		SocketAddress Address;
		UDPsocket Socket;
		uint64_t CharacterId;
	};

	class FBL_API ConnectionManager
	{
	private:
		std::vector<PlayerConnection> m_Connections;

	public:
		ConnectionManager();

		const std::vector<PlayerConnection>& GetConnections() const;

	};

}