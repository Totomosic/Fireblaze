#include "fblpch.h"
#include "LoginServer.h"

namespace Fireblaze
{

	void LoginServer::Init()
	{
		std::unordered_map<blt::string, blt::string> sqlServerConfig = ReadConfigFile(FIREBLAZE_SQL_SERVER_CONFIG_FILE);
		std::unordered_map<blt::string, blt::string> serverConfig = ReadConfigFile(FIREBLAZE_LOGIN_SERVER_CONFIG_FILE);
		SocketAddress sqlAddress(sqlServerConfig.at("server_host"), std::atoi(sqlServerConfig.at("server_port").c_str()));
		SocketAddress serverAddress(serverConfig.at("server_host"), std::atoi(serverConfig.at("server_port").c_str()));
		m_Manager.Connect(sqlAddress);

		m_Server.RegisterHandler<RegisterAccountRequest, RegisterAccountResponse>(RequestType::RegisterAccountRequst, [&manager = m_Manager](RegisterAccountRequest& request)
			{
				return manager.RegisterAccount(request);
			});

		m_Server.RegisterHandler<LoginRequest, LoginResponse>(RequestType::LoginRequest, [&manager = m_Manager](LoginRequest& request)
			{
				return manager.Login(request);
			});

		m_Server.RegisterHandler<LogoutRequest, LogoutResponse>(RequestType::LogoutRequest, [&manager = m_Manager](LogoutRequest& request)
			{
				return manager.Logout(request);
			});

		m_Server.Bind(serverAddress);
		m_Server.Listen(5);
	}

	void LoginServer::Update()
	{
		
	}

	void LoginServer::Exit()
	{
		m_Manager.Disconnect();
		Application::Exit();
	}

}