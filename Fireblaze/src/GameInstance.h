#pragma once
#include "clientpch.h"
#include "StateManager.h"

#include "Communication/Chat/FireblazeChat.h"

namespace Fireblaze
{

	class FBL_API GameInstance
	{
	private:
		static std::unique_ptr<GameInstance> s_Instance;

	public:
		static void Create(Scene* gameScene);
		static void Delete();
		static GameInstance& Get();
		static bool IsRunning();

	private:
		Scene* m_GameScene;
		StateManager* m_State;

		std::unique_ptr<FireblazeChat> m_ChatTerminal;

	public:
		GameInstance(Scene* gameScene);
		void SetStateManager(StateManager& manager);

		void Initialize();

		Scene& GetGameScene() const;
		FireblazeChat& GetChatTerminal() const;
	};

}