#include "LoginScene.h"

namespace Fireblaze
{

	std::unique_ptr<Material> CreateBackgroundMaterial(const ResourcePtr<Texture2D>& backgroundTexture)
	{
		BasicMaterialGraph graph;
		PropertyNode& texture = graph.AddProperty("Texture", backgroundTexture);
		PropertyNode& texCoordTransform = graph.AddProperty("Transform", Matrix3f::Identity());
		SampleTextureNode& sampler = graph.AddNode<SampleTextureNode>();

		Vec3Node& coords = graph.AddNode<Vec3Node>();
		coords.SetXY(graph.GetContext().VertexTexCoord().GetValue());
		coords.SetZ(graph.AddNode(std::make_unique<ConstantFloatNode>(1.0f)).GetValue());
		MultiplyNode& mul = graph.AddNode<MultiplyNode>();
		mul.SetInputA(texCoordTransform.GetValue());
		mul.SetInputB(coords.GetValue());
		SplitVec3Node& splitter = graph.AddNode<SplitVec3Node>();
		splitter.SetInput(mul.GetResult());

		sampler.SetTexture(texture.GetValue());
		sampler.SetTexCoord(splitter.GetRG());
		graph.SetRGB(sampler.GetRGB());
		graph.SetAlpha(sampler.GetA());
		graph.Build();
		std::unique_ptr<Material> material = graph.GetMaterial();
		material->SetIsTransparent(true);

		material->GetLinkContext().Link("Transform", [currentTime = 0.0f]() mutable
			{
				currentTime += Time::Get().RenderingTimeline().DeltaTime();
				
				int maxRows = 8;
				int maxCols = 8;

				float speed = 0.3f;
				int row = (maxRows - 1) - (int)(currentTime / (speed)) % maxRows;
				int col = (int)(currentTime / (speed / (float)maxCols)) % maxCols;
				Matrix3f result = Matrix3f::Translation(col / (float)maxCols, row / (float)maxRows, 0.0f);
				result = result * Matrix3f::Scale(1.0f / (float)maxCols, 1.0f / (float)maxRows, 1.0f);
				return result;
			});

		return material;
	}

	void CreateLoginScene(Scene& scene, int width, int height, Scene& registerScene)
	{
		Camera* loginCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& loginLayer = scene.CreateLayer(loginCamera, 100);

		UISurface& background = loginLayer.UI().Root().CreateSurface(width, height, Color::Black, Transform({ width / 2.0f, height / 2.0f, -90 }));

		ResourceManager::Get().LoadPack("res/resources.pack", [&background](const ResourcePack& pack)
			{
				ResourceExtractor resources(pack);
				background.GetGameObject()->mesh().Mesh.Materials[0] = CreateBackgroundMaterial(resources.GetResourcePtr<Texture2D>("FireTitle8x8"));
			});

		UISurface& loginBackdrop = background.CreateSurface(400, 600, Color(200, 190, 200, 200), Transform({ 0, 0, 1 }));
		UIText& title = loginBackdrop.CreateText("Fireblaze", ResourceManager::Get().Fonts().Verdana(48), Color::Black, Transform({ 0, 200, 1 }), AlignH::Center);

		UITextInput& usernameBox = loginBackdrop.CreateTextInput(300, 50, Color(100, 100, 100), ResourceManager::Get().Fonts().Calibri(20), Color::Black, Transform({ 0, 50, 1 }));
		UIText& usernameText = usernameBox.CreateText("Username:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UITextInput& passwordBox = usernameBox.CreateTextInput(300, 50, Color(100, 100, 100), ResourceManager::Get().Fonts().Calibri(20), Color::Black, Transform({ 0, -100, 0 }));
		UIText& passwordText = passwordBox.CreateText("Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		passwordBox.SetObfuscating(true);

		UISurface& signInButton = passwordBox.CreateSurface(280, 50, Color(50, 255, 50), Transform({ 0, -110, 0 }));
		UIText& signInText = signInButton.CreateText("Sign in", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);
		UISurface& registerButton = signInButton.CreateSurface(280, 50, Color(50, 50, 255), Transform({ 0, -60, 0 }));
		UIText& registerText = registerButton.CreateText("Register", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);

		registerButton.Events().OnClick.AddEventListener([&registerScene](Event<UIClickedEvent>& e)
			{
				SceneManager::Get().SetCurrentScene(registerScene);
				e.StopPropagation();
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}