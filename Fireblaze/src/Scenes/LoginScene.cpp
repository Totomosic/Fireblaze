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
		coords.SetZ(graph.AddNode(std::make_unique<FloatNode>(1.0f)).GetValue());
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
				
				float speed = 0.5f;
				int row = (int)(currentTime / (speed)) % 8;
				int col = (int)(currentTime / (speed / 8.0f)) % 8;
				Matrix3f result = Matrix3f::Translation(row / 8.0f, col / 8.0f, 0.0f);
				result = result * Matrix3f::Scale(1.0f / 8.0f, 1.0f / 8.0f, 1.0f);
				return result;
			});

		return material;
	}

	void CreateLoginScene(Scene& scene, int width, int height, Scene& registerScene)
	{
		Camera* loginCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& loginLayer = scene.CreateLayer(loginCamera);

		UIsurface& background = loginLayer.UI().Rectangle(width, height, Color::Black, Transform({ width / 2.0f, height / 2.0f, -90 }));

		ResourceManager::Get().LoadPack("res/resources.pack", [&background](const ResourcePack& pack)
			{
				ResourceExtractor resources(pack);
				background.Object()->mesh().Mesh.Materials[0] = CreateBackgroundMaterial(resources.GetResourcePtr<Texture2D>("FireTitle8x8"));
			});

		UIsurface& loginBackdrop = background.Rectangle(400, 600, Color(200, 190, 200), Transform({ 0, 0, 1 }));
		Text& title = loginBackdrop.Text("Fireblaze", ResourceManager::Get().Fonts().Verdana(48), Color::Black, Transform({ 0, 200, 1 }), AlignH::Center);

		UIsurface& usernameBox = loginBackdrop.Rectangle(300, 50, Color(100, 100, 100), Transform({ 0, 50, 1 }));
		Text& usernameText = usernameBox.Text("Username:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UIsurface& passwordBox = usernameBox.Rectangle(300, 50, Color(100, 100, 100), Transform({ 0, -100, 0 }));
		Text& passwordText = passwordBox.Text("Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);

		UIsurface& signInButton = passwordBox.Rectangle(280, 50, Color(50, 255, 50), Transform({ 0, -110, 0 }));
		Text& signInText = signInButton.Text("Sign in", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);
		UIsurface& registerButton = signInButton.Rectangle(280, 50, Color(50, 50, 255), Transform({ 0, -60, 0 }));
		Text& registerText = registerButton.Text("Register", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);

		registerButton.EventHandler().OnClicked.AddEventListener([&registerScene](Event<UIClickedEvent>& e)
			{
				SceneManager::Get().SetCurrentScene(registerScene);
				e.StopPropagation();
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}