#pragma once
#include "fblpch.h"

namespace Fireblaze
{

	class FBL_API FireblazeClient : public Application
	{
	public:
		void Init() override;
		void Tick() override;
		void Update() override;
		void Render() override;
		void Exit() override;
	};

}