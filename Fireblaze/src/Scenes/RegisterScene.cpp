#include "RegisterScene.h"
#include "Utils/Clients/TcpRequestClient.h"

namespace Fireblaze
{

	extern SocketAddress LoginServerAddress;

	void CreateRegisterScene(Scene& scene, int width, int height, Scene& loginScene)
	{
		Camera* registerCamera = scene.CreateCamera(Projection::Orthographic(0, width, 0, height, -100, 100));
		Layer& registerLayer = scene.CreateLayer(registerCamera, 100);

		UISurface& registerBackdrop = registerLayer.UI().Root().CreateSurface(400, 600, Color(200, 190, 200), Transform({ width / 2.0f, height / 2.0f, -90 }));
		UIText& title = registerBackdrop.CreateText("Fireblaze", ResourceManager::Get().Fonts().Verdana(48), Color::Black, Transform({ 0, 200, 1 }), AlignH::Center);

		UITextInput& usernameBox = registerBackdrop.CreateTextInput(300, 50, Color(100, 100, 100), ResourceManager::Get().Fonts().Calibri(20), Color::Black, Transform({ 0, 100, 1 }));
		UIText& usernameText = usernameBox.CreateText("Username:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UITextInput& passwordBox = usernameBox.CreateTextInput(300, 50, Color(100, 100, 100), ResourceManager::Get().Fonts().Calibri(20), Color::Black, Transform({ 0, -90, 0 }));
		UIText& passwordText = passwordBox.CreateText("Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UITextInput& passwordConfirmBox = passwordBox.CreateTextInput(300, 50, Color(100, 100, 100), ResourceManager::Get().Fonts().Calibri(20), Color::Black, Transform({ 0, -80, 0 }));
		UIText& passwordConfirmText = passwordConfirmBox.CreateText("Confirm Password:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);
		UITextInput& emailBox = passwordConfirmBox.CreateTextInput(300, 50, Color(100, 100, 100), ResourceManager::Get().Fonts().Calibri(20), Color::Black, Transform({ 0, -90, 0 }));
		UIText& emailText = emailBox.CreateText("Email:", ResourceManager::Get().Fonts().Calibri(16), Color::Black, Transform({ -150, 32, 0 }), AlignH::Left, AlignV::Bottom);

		UISurface& registerButton = emailBox.CreateSurface(280, 50, Color(50, 50, 255), Transform({ 0, -75, 0 }));
		UIText& registerText = registerButton.CreateText("Register", ResourceManager::Get().Fonts().Calibri(22), Color::Black, Transform({ 0, 0, 1 }), AlignH::Center);

		std::function<void()> handleRegister = [&loginScene, &usernameBox, &passwordBox, &passwordConfirmBox, &emailBox]()
		{
			const blt::string& username = usernameBox.GetText();
			const blt::string& password = passwordBox.GetText();
			const blt::string& email = emailBox.GetText();
			if (password != passwordConfirmBox.GetText())
			{
				return;
			}
			TcpRequestClient<RequestType> client;
			client.Connect(LoginServerAddress);
			RegisterAccountRequest request;
			request.Username = username;
			request.Password = password;
			request.Email = email;
			RegisterAccountResponse response = client.Request<RegisterAccountRequest, RegisterAccountResponse>(RequestType::RegisterAccountRequst, request);
			if (response.FailReason == RegisterAccountFailReason::Ok)
			{
				SceneManager::Get().SetCurrentScene(loginScene);
			}
		};

		registerButton.Events().OnClick.AddEventListener([handleRegister](Event<UIClickedEvent>& e)
			{
				handleRegister();
				e.StopPropagation();
			});

		emailBox.Events().OnKeyUp.AddEventListener([handleRegister](Event<UIKeyUpEvent>& e)
			{
				if (e.Data.Key == Keycode::Enter)
				{
					handleRegister();
				}
			});

		registerLayer.UI().AddElementToTabList(&usernameBox);
		registerLayer.UI().AddElementToTabList(&passwordBox);
		registerLayer.UI().AddElementToTabList(&passwordConfirmBox);
		registerLayer.UI().AddElementToTabList(&emailBox);

		usernameBox.Events().OnFocus.AddEventListener([&usernameBox](Event<UIFocusEvent>& e)
			{
				usernameBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(200, 200, 200));
			});
		usernameBox.Events().OnFocusLost.AddEventListener([&usernameBox](Event<UIFocusLostEvent>& e)
			{
				usernameBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(100, 100, 100));
			});

		passwordBox.Events().OnFocus.AddEventListener([&passwordBox](Event<UIFocusEvent>& e)
			{
				passwordBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(200, 200, 200));
			});
		passwordBox.Events().OnFocusLost.AddEventListener([&passwordBox](Event<UIFocusLostEvent>& e)
			{
				passwordBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(100, 100, 100));
			});

		passwordConfirmBox.Events().OnFocus.AddEventListener([&passwordConfirmBox](Event<UIFocusEvent>& e)
			{
				passwordConfirmBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(200, 200, 200));
			});
		passwordConfirmBox.Events().OnFocusLost.AddEventListener([&passwordConfirmBox](Event<UIFocusLostEvent>& e)
			{
				passwordConfirmBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(100, 100, 100));
			});

		emailBox.Events().OnFocus.AddEventListener([&emailBox](Event<UIFocusEvent>& e)
			{
				emailBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(200, 200, 200));
			});
		emailBox.Events().OnFocusLost.AddEventListener([&emailBox](Event<UIFocusLostEvent>& e)
			{
				emailBox.BackgroundElement().GetMesh().Materials[0]->GetLinkContext().Link("Color", Color(100, 100, 100));
			});

		RenderSchedule schedule(scene);
		schedule.AddRenderProcess({});
		SceneRenderer::Get().AddRenderSchedule(schedule);
	}

}