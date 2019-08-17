#include "fblpch.h"
#include "LoginManager.h"

namespace Fireblaze
{

	LoginManager::LoginManager()
		: m_Connection(), m_AccountsMutex(), m_Accounts()
	{

	}

	void LoginManager::Connect(const SocketAddress& address)
	{
		m_Connection.Connect(address);
	}

	void LoginManager::Disconnect()
	{
		m_Connection.Disconnect();
	}

	RegisterAccountResponse LoginManager::RegisterAccount(const RegisterAccountRequest& request)
	{
		RegisterAccountResponse response;
		blt::string query = "INSERT INTO Accounts (username,password,email) VALUES (\"" + request.Username + "\",\"" + request.Password + "\",\"" + request.Email + "\")";
		SQLQueryResult result = m_Connection.Execute(query, true);
		if (result.Status == SQLQueryStatus::Ok)
		{
			m_Connection.CommitChanges();
			SQLQueryResult result = m_Connection.Execute("SELECT LAST_INSERT_ID()");
			if (result.Status == SQLQueryStatus::Ok)
			{
				uint32_t id = std::atoi(result.Table.GetRow(0).GetValue(0).c_str());
				response.AccountId = id;
				response.FailReason = RegisterAccountFailReason::Ok;
			}
		}
		else
		{
			response.FailReason = RegisterAccountFailReason::UsernameAlreadyExists;
		}
		return response;
	}

	LoginResponse LoginManager::Login(const LoginRequest& request)
	{
		LoginResponse response;
		blt::string query = "SELECT account_id, password FROM Accounts WHERE username=\"" + request.Username + "\"";
		SQLQueryResult result = m_Connection.Execute(query, true);
		if (result.Status == SQLQueryStatus::Ok)
		{
			if (result.Table.GetRowCount() == 0)
			{
				response.FailReason = LoginFailReason::InvalidUsername;
				return response;
			}
			blt::string password = result.Table.GetRow(0).GetValue(1);
			if (password != request.Password)
			{
				response.FailReason = LoginFailReason::InvalidPassword;
				return response;
			}
			uint64_t accountId = std::atoi(result.Table.GetRow(0).GetValue(0).c_str());
			std::scoped_lock<std::mutex> lock(m_AccountsMutex);
			if (std::find_if(m_Accounts.begin(), m_Accounts.end(), [accountId](const LoggedInAccount& acc)
				{
					return acc.AccountId == accountId;
				}) != m_Accounts.end())
			{
				response.FailReason = LoginFailReason::AlreadyLoggedIn;
			}
			response.AccountId = accountId;
			response.FailReason = LoginFailReason::Ok;
			m_Accounts.push_back({ response.AccountId });
		}
		return response;
	}

	LogoutResponse LoginManager::Logout(const LogoutRequest& request)
	{
		LogoutResponse response;
		std::scoped_lock<std::mutex> lock(m_AccountsMutex);
		auto it = std::find_if(m_Accounts.begin(), m_Accounts.end(), [&request](const LoggedInAccount& acc)
			{
				return acc.AccountId == request.AccountId;
			});
		if (it == m_Accounts.end())
		{
			response.FailReason = LogoutFailReason::NotLoggedIn;
		}
		else
		{
			m_Accounts.erase(it);
			response.FailReason = LogoutFailReason::Ok;
		}
		return response;
	}

}