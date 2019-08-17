#include "RegisterScene.h"

namespace Fireblaze
{

	void CreateRegisterScene(Scene& scene, int width, int height, Scene& loginScene)
	{
		Camera* registerCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& registerLayer = scene.CreateLayer(registerCamera);

		UIsurface& registerBackdrop = registerLayer.UI().Rectangle(400, 600, Color(200, 190, 200), Transform({ width / 2.0f, height / 2.0f, -90 }));
		Text& title = registerBackdrop.Text("Fireblaze", ResourceManager::Get().Fonts().Verdana(48), Color::Black, Transform({ 0, 200, 1 }), AlignH::Center);

		UIsurface& usernameBox = registerBackdrop.Rectangle(300, 50, Color(100, 100, 100), Transform({ 0, 100, 1 }));
		Text& usernameText = usernameBox.Text("Username:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UIsurface& passwordBox = usernameBox.Rectangle(300, 50, Color(100, 100, 100), Transform({ 0, -90, 0 }));
		Text& passwordText = passwordBox.Text("Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UIsurface& passwordConfirmBox = passwordBox.Rectangle(300, 50, Color(100, 100, 100), Transform({ 0, -80, 0 }));
		Text& passwordConfirmText = passwordConfirmBox.Text("Confirm Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UIsurface& emailBox = passwordConfirmBox.Rectangle(300, 50, Color(100, 100, 100), Transform({ 0, -90, 0 }));
		Text& emailText = emailBox.Text("Email:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);

		UIsurface& registerButton = emailBox.Rectangle(280, 50, Color(50, 50, 255), Transform({ 0, -75, 0 }));
		Text& registerText = registerButton.Text("Register", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);

		registerButton.EventHandler().OnClicked.AddEventListener([&loginScene](Event<UIClickedEvent>& e)
			{
				SceneManager::Get().SetCurrentScene(loginScene);
				e.StopPropagation();
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}