#pragma once
#include "clientpch.h"

namespace Fireblaze
{

	class BLT_API CameraController : public Component
	{
	private:

	public:
		CameraController();

		void Update() override;
		BLT_DEFAULT_COMPONENT_CLONE(CameraController);

	};

}