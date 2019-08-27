#include "clientpch.h"
#include "CharacterSelectScene.h"
#include "Utils/Clients/TcpRequestClient.h"

#include "StateManager.h"

namespace Fireblaze
{

	UISurface& CreateCharacterBoxElement(const Vector2f& position, const Vector2f& size, UIElement& parent)
	{
		UISurface& button = parent.CreateSurface(size.x, size.y, Color::White, Transform({ position, 1 }));
		return button;
	}

	void CreateCharacterSelectScene(Scene& scene, int width, int height, Scene& loginScene)
	{
		Camera* characterCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& characterLayer = scene.CreateLayer(characterCamera, 100);

		scene.OnLoad.AddEventListener([&characterLayer, width, height, &loginScene](Event<SceneLoadedEvent>& e)
			{
				UISurface& background = characterLayer.UI().Root().CreateSurface(width, height, Color::Black, Transform({ width / 2.0f, height / 2.0f, -90 }));

				float margin = 50;
				int rows = 2;
				int cols = 3;
				Vector2f size = { (width - (cols + 1) * margin) / cols, (height - (rows + 1) * margin) / rows };
				float xStep = size.x + margin;
				float yStep = size.y + margin;
				float xStart = size.x / 2 + margin - width / 2;
				float yStart = size.y / 2 + margin + height / 2;

				UISurface& chr0 = CreateCharacterBoxElement({ xStart + xStep * 0, height - (yStart + yStep * 0) }, size, background);
				UISurface& chr1 = CreateCharacterBoxElement({ xStart + xStep * 1, height - (yStart + yStep * 0) }, size, background);
				UISurface& chr2 = CreateCharacterBoxElement({ xStart + xStep * 2, height - (yStart + yStep * 0) }, size, background);
				UISurface& chr3 = CreateCharacterBoxElement({ xStart + xStep * 0, height - (yStart + yStep * 1) }, size, background);
				UISurface& chr4 = CreateCharacterBoxElement({ xStart + xStep * 1, height - (yStart + yStep * 1) }, size, background);
				UISurface& chr5 = CreateCharacterBoxElement({ xStart + xStep * 2, height - (yStart + yStep * 1) }, size, background);
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