#include "clientpch.h"
#include "StateManager.h"

namespace Fireblaze
{

	StateManager::StateManager()
		: m_Session()
	{

	}

	StateManager& StateManager::Get()
	{
		static StateManager m_Manager;
		return m_Manager;
	}

	const SessionManager& StateManager::Session() const
	{
		return m_Session;
	}

	SessionManager& StateManager::Session()
	{
		return m_Session;
	}

}