#pragma once
#include "gspch.h"

namespace Fireblaze
{

	class FBL_API GameServer : public Application
	{
	public:
		void Init() override;
		void Update() override;
	};

}