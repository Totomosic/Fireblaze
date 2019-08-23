#include "RegisterScene.h"

namespace Fireblaze
{

	void CreateRegisterScene(Scene& scene, int width, int height, Scene& loginScene)
	{
		Camera* registerCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& registerLayer = scene.CreateLayer(registerCamera, 100);

		UISurface& registerBackdrop = registerLayer.UI().Root().CreateSurface(400, 600, Color(200, 190, 200), Transform({ width / 2.0f, height / 2.0f, -90 }));
		UIText& title = registerBackdrop.CreateText("Fireblaze", ResourceManager::Get().Fonts().Verdana(48), Color::Black, Transform({ 0, 200, 1 }), AlignH::Center);

		UISurface& usernameBox = registerBackdrop.CreateSurface(300, 50, Color(100, 100, 100), Transform({ 0, 100, 1 }));
		UIText& usernameText = usernameBox.CreateText("Username:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UISurface& passwordBox = usernameBox.CreateSurface(300, 50, Color(100, 100, 100), Transform({ 0, -90, 0 }));
		UIText& passwordText = passwordBox.CreateText("Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UISurface& passwordConfirmBox = passwordBox.CreateSurface(300, 50, Color(100, 100, 100), Transform({ 0, -80, 0 }));
		UIText& passwordConfirmText = passwordConfirmBox.CreateText("Confirm Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UISurface& emailBox = passwordConfirmBox.CreateSurface(300, 50, Color(100, 100, 100), Transform({ 0, -90, 0 }));
		UIText& emailText = emailBox.CreateText("Email:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);

		UISurface& registerButton = emailBox.CreateSurface(280, 50, Color(50, 50, 255), Transform({ 0, -75, 0 }));
		UIText& registerText = registerButton.CreateText("Register", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);

		registerButton.Events().OnClick.AddEventListener([&loginScene](Event<UIClickedEvent>& e)
			{
				SceneManager::Get().SetCurrentScene(loginScene);
				e.StopPropagation();
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}