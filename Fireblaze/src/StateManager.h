#pragma once
#include "SessionManager.h"

namespace Fireblaze
{

	class FBL_API StateManager
	{
	private:
		SessionManager m_Session;

	private:
		StateManager();

	public:
		static StateManager& Get();

		const SessionManager& Session() const;
		SessionManager& Session();
	};

}