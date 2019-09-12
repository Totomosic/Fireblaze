#include "clientpch.h"
#include "CreateGameScene.h"
#include "Utils/Clients/TcpRequestClient.h"
#include "Common/CharacterRequests.h"
#include "Common/CharacterResponses.h"

#include "StateManager.h"
#include "GameInstance.h"

namespace Fireblaze
{

	void CreateGameScene(Scene& scene, int width, int height, Scene& loginScene, Scene& characterSelectScene)
	{
		scene.OnLoad.AddEventListener([width, height, &scene, &loginScene, &characterSelectScene](Event<SceneLoadedEvent>& e)
			{
				GameInstance::Create(&scene);
				GameInstance::Get().SetStateManager(StateManager::Get());
				GameInstance::Get().Initialize();
			});

		scene.OnUnload.AddEventListener([](Event<SceneUnloadedEvent>& e)
			{
				GameInstance::Delete();
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}