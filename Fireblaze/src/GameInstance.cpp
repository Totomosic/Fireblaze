#include "clientpch.h"
#include "GameInstance.h"

namespace Fireblaze
{

	std::unique_ptr<GameInstance> GameInstance::s_Instance;

	void GameInstance::Create(Scene* gameScene)
	{
		s_Instance = std::make_unique<GameInstance>(gameScene);
	}

	void GameInstance::Delete()
	{
		s_Instance = nullptr;
	}

	GameInstance& GameInstance::Get()
	{
		return *s_Instance;
	}

	bool GameInstance::IsRunning()
	{
		return s_Instance != nullptr;
	}

	GameInstance::GameInstance(Scene* gameScene)
		: m_GameScene(gameScene), m_State(nullptr), m_ChatTerminal(nullptr)
	{

	}

	void GameInstance::SetStateManager(StateManager& manager)
	{
		m_State = &manager;
	}

	void GameInstance::Initialize()
	{
		Camera* uiCamera = m_GameScene->CreateCamera(Projection::Orthographic(0, 1280, 0, 720, -100, 100));
		Layer& uiLayer = m_GameScene->CreateLayer(uiCamera);
		m_ChatTerminal = std::make_unique<FireblazeChat>(&uiLayer);
	}

	Scene& GameInstance::GetGameScene() const
	{
		return *m_GameScene;
	}

	FireblazeChat& GameInstance::GetChatTerminal() const
	{
		return *m_ChatTerminal;
	}

}