#include "clientpch.h"
#include "GameInstance.h"

#include "Camera/CameraController.h"

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
		: m_GameScene(gameScene), m_State(nullptr), m_ChatTerminal(nullptr), m_MainCamera(nullptr), m_Terrain(nullptr), m_TerrainGenerator(0.001f, 0.5f)
	{

	}

	void GameInstance::SetStateManager(StateManager& manager)
	{
		m_State = &manager;
	}

	void GameInstance::Initialize()
	{
		m_MainCamera = m_GameScene->CreateCamera(Projection::Perspective(PI / 2.0f, CurrentContext::GetWindow().Aspect(), 0.1f, 1000.0f));
		m_MainCamera->Components().AddComponent<CameraController>();
		m_MainCamera->transform().Translate(0, 0, 5);
		Layer& mainLayer = m_GameScene->CreateLayer(m_MainCamera);

		Camera* uiCamera = m_GameScene->CreateCamera(Projection::Orthographic(0, 1280, 0, 720, -100, 100));
		Layer& uiLayer = m_GameScene->CreateLayer(uiCamera, 1000);
		m_ChatTerminal = std::make_unique<FireblazeChat>(&uiLayer);

		ObjectFactory f(mainLayer);

		m_Terrain = f.Grid(100, 100, 100, 100, Color::LawnGreen);

		GameObject* player = f.Cuboid(1, 3, 1, Color::Red, Transform({ 0, 1.5f, 0 }));
		GameObject* camera = f.Instantiate();
		camera->MakeChildOf(player);
		m_MainCamera->MakeChildOf(camera);
	}

	void GameInstance::Update()
	{
		static float offset = 0.0f;
		VertexMapping mapping = m_Terrain->mesh().Mesh.Models[0].Model->Data().Vertices->Map();
		VertexIterator it = mapping.Begin();
		for (int z = 0; z < 100; z++)
		{
			for (int x = 0; x < 100; x++)
			{
				it.Position().y = m_TerrainGenerator.Generate(8, x + offset, z) * 20;
				it++;
			}
		}
		offset += 1.0f;
	}

	Scene& GameInstance::GetGameScene() const
	{
		return *m_GameScene;
	}

	FireblazeChat& GameInstance::GetChatTerminal() const
	{
		return *m_ChatTerminal;
	}

	Camera& GameInstance::Get3dCamera() const
	{
		return *m_MainCamera;
	}

}