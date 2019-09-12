#include "clientpch.h"
#include "CharacterSelectScene.h"
#include "Utils/Clients/TcpRequestClient.h"
#include "Common/CharacterRequests.h"
#include "Common/CharacterResponses.h"

#include "StateManager.h"

namespace Fireblaze
{

	extern SocketAddress LoginServerAddress;

	UIRectangle& CreateCharacterBoxElement(const Vector2f& position, const Vector2f& size, UIElement& parent)
	{
		UIRectangle& button = parent.CreateRectangle(size.x, size.y, Color::White, Transform({ position, 1 }));
		return button;
	}

	void CreateCharacterSelectScene(Scene& scene, int width, int height, Scene& loginScene, Scene& characterCreateScene, Scene& gameScene)
	{
		Camera* characterCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& characterLayer = scene.CreateLayer(characterCamera, 100);

		scene.OnLoad.AddEventListener([&characterLayer, width, height, &loginScene, &characterCreateScene, &gameScene](Event<SceneLoadedEvent>& e)
			{
				UIRectangle& background = characterLayer.UI().Root().CreateRectangle(width, height, Color::Black, Transform({ width / 2.0f, height / 2.0f, -90 }));

				float margin = 50;
				int rows = 2;
				int cols = 3;
				Vector2f size = { (width - (cols + 1) * margin) / cols, (height - 50 - (rows + 1) * margin) / rows };
				float xStep = size.x + margin;
				float yStep = size.y + margin;
				float xStart = size.x / 2 + margin - width / 2;
				float yStart = size.y / 2 + margin + height / 2;

				UIRectangle& chr0 = CreateCharacterBoxElement({ xStart + xStep * 0, height - 50 - (yStart + yStep * 0) }, size, background);
				UIRectangle& chr1 = CreateCharacterBoxElement({ xStart + xStep * 1, height - 50 - (yStart + yStep * 0) }, size, background);
				UIRectangle& chr2 = CreateCharacterBoxElement({ xStart + xStep * 2, height - 50 - (yStart + yStep * 0) }, size, background);
				UIRectangle& chr3 = CreateCharacterBoxElement({ xStart + xStep * 0, height - 50 - (yStart + yStep * 1) }, size, background);
				UIRectangle& chr4 = CreateCharacterBoxElement({ xStart + xStep * 1, height - 50 - (yStart + yStep * 1) }, size, background);
				UIRectangle& chr5 = CreateCharacterBoxElement({ xStart + xStep * 2, height - 50 - (yStart + yStep * 1) }, size, background);

				std::vector<UIRectangle*> characterBoxArray = { &chr0, &chr1, &chr2, &chr3, &chr4, &chr5 };

				TaskManager::Run([]()
					{
						TcpRequestClient<RequestType> client;
						client.Connect(LoginServerAddress);
						GetCharactersRequest request;
						request.AccountId = StateManager::Get().Session().GetAccountId();
						request.CharacterIndex = GetCharactersRequest::ALL_CHARACTERS_INDEX;
						GetCharactersResponse response = client.Request<GetCharactersRequest, GetCharactersResponse>(RequestType::GetCharactersRequest, request);
						return std::move(response);						
				}).ContinueWithOnMainThread([characterBoxes{ std::move(characterBoxArray) }, &characterCreateScene, &gameScene](GetCharactersResponse response)
					{
						int characterCount = response.Characters.size();
						for (int i = 0; i < characterCount; i++)
						{
							UIRectangle& box = *characterBoxes[i];
							const CharacterOverviewData& characterData = response.Characters[i];
							UIText& nameText = box.CreateText(characterData.Name, ResourceManager::Get().Fonts().Calibri(26), Color::Black, Transform({ 0, 0, 1 }));
							box.Events().OnClick.AddEventListener([characterData, &gameScene](Event<UIClickedEvent>& e)
								{
									// Play as character
									StateManager::Get().Session().SetCharacterId(characterData.CharacterId);
									SceneManager::Get().SetCurrentScene(gameScene);
								});
						}
						for (int i = characterCount; i < characterBoxes.size(); i++)
						{
							UIRectangle& box = *characterBoxes[i];
							box.CreateText("Empty", ResourceManager::Get().Fonts().Calibri(26), Color::Black, Transform({ 0, 0, 1 }));
							box.Events().OnClick.AddEventListener([&characterCreateScene](Event<UIClickedEvent>& e)
								{
									SceneManager::Get().SetCurrentScene(characterCreateScene);
									e.StopPropagation();
								});
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