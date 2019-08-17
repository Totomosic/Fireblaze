#pragma once
#include "sql.h"
#include "Bolt.h"

namespace Fireblaze
{

	class FBL_API SQLConnection
	{
	private:
		TCPsocket m_Socket;

	public:
		SQLConnection(const SocketAddress& address);
		SQLConnection();

		void Connect(const SocketAddress& address);
		void Disconnect();

		SQLQueryResult Execute(const blt::string& sqlQuery, bool logResponse = false);
		bool CommitChanges();
		bool RollbackChanges();

	private:
		blt::string GetStringResponse(const blt::string& sendData);
		SQLQueryResult ConvertStringToQueryResult(const blt::string& str, bool logResponse);

	};

}