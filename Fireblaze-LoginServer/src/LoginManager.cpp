#include "fblpch.h"
#include "LoginManager.h"

namespace Fireblaze
{

	LoginManager::LoginManager()
		: m_Connection(), m_AccountsMutex(), m_Accounts(), m_ConnectedMutex(), m_IsConnected(false), m_ServerAddress()
	{

	}

	void LoginManager::Connect(const SocketAddress& address)
	{
		int result = m_Connection.Connect(address);
		m_IsConnected = result >= 0;
		m_ServerAddress = address;
	}

	void LoginManager::Disconnect()
	{
		m_Connection.Disconnect();
	}

	RegisterAccountResponse LoginManager::RegisterAccount(const RegisterAccountRequest& request)
	{
		RegisterAccountResponse response;
		if (AttemptReconnect())
		{			
			blt::string query = "INSERT INTO Accounts (Username, Password, Email) VALUES (\"" + request.Username + "\", \"" + request.Password + "\", \"" + request.Email + "\")";
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
		response.FailReason = RegisterAccountFailReason::CannotConnect;
		return response;
	}

	LoginResponse LoginManager::Login(const LoginRequest& request)
	{
		LoginResponse response;
		if (AttemptReconnect())
		{
			blt::string query = "SELECT AccountId, Password FROM Accounts WHERE Username=\"" + request.Username + "\"";
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
		response.FailReason = LoginFailReason::CannotConnect;
		return response;
	}

	LogoutResponse LoginManager::Logout(const LogoutRequest& request)
	{
		LogoutResponse response;
		if (AttemptReconnect())
		{
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
		response.FailReason = LogoutFailReason::CannotConnect;
		return response;
	}

	GetCharactersResponse LoginManager::GetCharacters(const GetCharactersRequest& request)
	{
		GetCharactersResponse response;
		if (AttemptReconnect())
		{
			response.FailReason = GetCharactersFailReason::InvalidAccount;
			blt::string query = "SELECT Characters.CharacterId, Name, Level FROM Characters JOIN CharacterAccountMap ON Characters.CharacterId = CharacterAccountMap.CharacterId WHERE Characters.AccountId = \"" + std::to_string(request.AccountId) + '"';
			SQLQueryResult result = m_Connection.Execute(query, true);
			if (result.Status == SQLQueryStatus::Ok)
			{
				SQLTable& table = result.Table;
				if (table.GetRowCount() > 0)
				{
					for (auto& row : table)
					{
						CharacterOverviewData data;
						data.CharacterId = std::atoi(row.GetValue(0).c_str());
						data.Name = row.GetValue(1);
						data.Level = std::atoi(row.GetValue(2).c_str());
						response.Characters.push_back(data);
					}
				}
				response.FailReason = GetCharactersFailReason::Ok;
			}
			return response;
		}
		response.FailReason = GetCharactersFailReason::CannotConnect;
		return response;
	}

	AddCharacterResponse LoginManager::AddCharacter(const AddCharacterRequest& request)
	{
		AddCharacterResponse response;
		if (AttemptReconnect())
		{
			response.FailReason = AddCharacterFailReason::InvalidCreateData;
			blt::string query = "INSERT INTO Characters (Name, Level) VALUES (\"" + request.CreateData.Name + "\", " + std::to_string(request.CreateData.Level) + ')';
			SQLQueryResult result = m_Connection.Execute(query);
			if (result.Status == SQLQueryStatus::Ok)
			{
				m_Connection.CommitChanges();
				SQLQueryResult result = m_Connection.Execute("SELECT LAST_INSERT_ID()");
				if (result.Status == SQLQueryStatus::Ok)
				{
					uint64_t characterId = std::atoi(result.Table.GetRow(0).GetValue(0).c_str());
					CharacterOverviewData data;
					data.CharacterId = characterId;
					data.Name = request.CreateData.Name;
					data.Level = request.CreateData.Level;
					response.Character = data;
					response.FailReason = AddCharacterFailReason::Ok;
				}
			}
			return response;
		}
		response.FailReason = AddCharacterFailReason::CannotConnect;
		return response;
	}

	DeleteCharacterResponse LoginManager::DeleteCharacter(const DeleteCharacterRequest& request)
	{
		DeleteCharacterResponse response;
		if (AttemptReconnect())
		{
			return response;
		}
		response.FailReason = DeleteCharacterFailReason::CannotConnect;
		return response;
	}

	bool LoginManager::AttemptReconnect()
	{
		if (!m_IsConnected)
		{
			Connect(m_ServerAddress);
			return m_IsConnected;
		}
		return true;
	}

}