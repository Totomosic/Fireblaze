#include "FireblazeClient.h"
#include "Common/LoginRequests.h"
#include "Common/LoginResponses.h"

#include "Scenes/LoginScene.h"
#include "Scenes/RegisterScene.h"

namespace Fireblaze
{

	SocketAddress LoginServerAddress;

	void FireblazeClient::Init()
	{
		std::unordered_map<blt::string, blt::string> loginServerConfig = ReadConfigFile(FIREBLAZE_LOGIN_SERVER_CONFIG_FILE);
		LoginServerAddress = SocketAddress(loginServerConfig.at("server_host"), std::atoi(loginServerConfig.at("server_port").c_str()));

		Scene& loginScene = SceneManager::Get().CreateScene(1);
		Scene& registerScene = SceneManager::Get().CreateScene(1);

		CreateRegisterScene(registerScene, Width(), Height(), loginScene);
		CreateLoginScene(loginScene, Width(), Height(), registerScene);		

		SceneManager::Get().SetCurrentScene(loginScene);
	}

	void FireblazeClient::Update()
	{
	
	}

	void FireblazeClient::Render()
	{
		Graphics::Get().RenderScene();
	}

	void FireblazeClient::Exit()
	{
		Application::Exit();
	}

}