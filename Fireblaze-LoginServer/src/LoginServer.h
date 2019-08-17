#pragma once
#include "fblpch.h"
#include "LoginManager.h"

namespace Fireblaze
{

	class FBL_API LoginServer : public Application
	{
	private:
		LoginManager m_Manager;
		TcpRequestServer<RequestType> m_Server;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};

}