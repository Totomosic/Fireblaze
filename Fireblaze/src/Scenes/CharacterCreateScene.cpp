#include "clientpch.h"
#include "CharacterCreateScene.h"
#include "Utils/Clients/TcpRequestClient.h"
#include "Common/CharacterRequests.h"
#include "Common/CharacterResponses.h"

#include "StateManager.h"

namespace Fireblaze
{

	extern SocketAddress LoginServerAddress;

	void CreateCharacterCreateScene(Scene& scene, int width, int height, Scene& characterSelectScene)
	{
		Camera* characterCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& characterLayer = scene.CreateLayer(characterCamera, 100);

		scene.OnLoad.AddEventListener([&characterLayer, width, height, &characterSelectScene](Event<SceneLoadedEvent>& e)
			{
				UIRectangle& background = characterLayer.UI().Root().CreateRectangle(width, height, Color::Black, Transform({ width / 2.0f, height / 2.0f, -99 }));
				UITextInput& nameInput = background.CreateTextInput(300, 50, Color::White, ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 300, 1 }));

				UIRectangle& createCharacterButton = background.CreateRectangle(300, 50, Color::Green, Transform({ 0, -230, 1 }));
				UIText& createCharacterText = createCharacterButton.CreateText("Create Character", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }));
				UIRectangle& cancelButton = createCharacterButton.CreateRectangle(300, 50, Color::Red, Transform({ 0, -60, 0 }));
				UIText& cancelText = cancelButton.CreateText("Cancel", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }));

				cancelButton.Events().OnClick.AddEventListener([&characterSelectScene](Event<UIClickedEvent>& e)
					{
						SceneManager::Get().SetCurrentScene(characterSelectScene);
						e.StopPropagation();
					});

				createCharacterButton.Events().OnClick.AddEventListener([&characterSelectScene, &nameInput](Event<UIClickedEvent>& e)
					{
						TcpRequestClient<RequestType> client;
						client.Connect(LoginServerAddress);
						AddCharacterRequest request;
						request.AccountId = StateManager::Get().Session().GetAccountId();
						request.CreateData.Name = nameInput.GetText();
						request.CreateData.Level = 1;
						AddCharacterResponse response = client.Request<AddCharacterRequest, AddCharacterResponse>(RequestType::AddCharacterRequest, request);
						if (response.FailReason == AddCharacterFailReason::Ok)
						{
							SceneManager::Get().SetCurrentScene(characterSelectScene);
						}
					});
			});

		scene.OnUnload.AddEventListener([&characterLayer](Event<SceneUnloadedEvent>& e)
			{
				characterLayer.Clear();
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}