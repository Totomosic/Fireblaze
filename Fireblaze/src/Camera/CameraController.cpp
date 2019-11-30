#include "clientpch.h"
#include "CameraController.h"

namespace Fireblaze
{

	CameraController::CameraController() : Component()
	{
	}

	void CameraController::Update()
	{
		if (gameObject()->Parent() != nullptr)
		{			
			if (Input::Get().MouseButtonDown(MouseButton::Middle))
			{
				Vector3f delta = Input::Get().RelMousePosition();
				Transform& t = gameObject()->Parent()->transform();
				t.Rotate(-delta.x * 0.01f, Vector3f::Up(), Space::World);
				t.Rotate(delta.y * 0.01f, Vector3f::Right(), Space::Local);
			}
			Transform& t = gameObject()->transform();
			Vector2f scroll = Input::Get().RelMouseScroll();
			t.Translate(0, 0, -scroll.y);
		}
	}

}