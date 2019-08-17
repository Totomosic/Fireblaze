#pragma once
#include "fblpch.h"
#include "Common/LoginRequests.h"
#include "Common/LoginResponses.h"

namespace Fireblaze
{

	struct FBL_API LoggedInAccount
	{
	public:
		uint64_t AccountId;
	};

	class FBL_API LoginManager
	{
	private:
		SQLConnection m_Connection;
		std::mutex m_AccountsMutex;
		std::vector<LoggedInAccount> m_Accounts;

	public:
		LoginManager();

		void Connect(const SocketAddress& address);
		void Disconnect();

		RegisterAccountResponse RegisterAccount(const RegisterAccountRequest& request);
		LoginResponse Login(const LoginRequest& request);
		LogoutResponse Logout(const LogoutRequest& request);

	};

}