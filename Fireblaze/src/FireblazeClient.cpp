#include "clientpch.h"
#include "FireblazeClient.h"
#include "Common/LoginRequests.h"
#include "Common/LoginResponses.h"

#include "Scenes/LoginScene.h"
#include "Scenes/RegisterScene.h"
#include "Scenes/CharacterSelectScene.h"
#include "Scenes/CharacterCreateScene.h"
#include "Scenes/CreateGameScene.h"

namespace Fireblaze
{

	SocketAddress LoginServerAddress;

	void FireblazeClient::Init()
	{
		std::unordered_map<blt::string, blt::string> loginServerConfig = ReadConfigFile(FIREBLAZE_LOGIN_SERVER_CONFIG_FILE);
		LoginServerAddress = SocketAddress(loginServerConfig.at("server_host"), std::atoi(loginServerConfig.at("server_port").c_str()));

		Scene& loginScene = SceneManager::Get().CreateScene(1);
		Scene& registerScene = SceneManager::Get().CreateScene(1);
		Scene& characterSelectScene = SceneManager::Get().CreateScene(1);
		Scene& characterCreateScene = SceneManager::Get().CreateScene(1);
		Scene& gameScene = SceneManager::Get().CreateScene(4);

		CreateRegisterScene(registerScene, Width(), Height(), loginScene);
		CreateLoginScene(loginScene, Width(), Height(), registerScene, characterSelectScene);	
		CreateCharacterSelectScene(characterSelectScene, Width(), Height(), loginScene, characterCreateScene, gameScene);
		CreateCharacterCreateScene(characterCreateScene, Width(), Height(), characterSelectScene);
		CreateGameScene(gameScene, Width(), Height(), loginScene, characterSelectScene);

		SceneManager::Get().SetCurrentScene(loginScene);
	}

	void FireblazeClient::Tick()
	{
		BLT_TRACE("Allocated Bytes {0} Average Allocation {1}", CustomAllocator::GetAllocatedBytes(), (float)CustomAllocator::GetAllocatedBytes() / (float)CustomAllocator::GetAllocationCount());
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