#include "clientpch.h"
#include "SessionManager.h"
#include "Common/LoginServerConstants.h"

namespace Fireblaze
{

	SessionManager::SessionManager()
		: m_AccountId(InvalidId), m_CharacterId(InvalidId)
	{

	}

	uint64_t SessionManager::GetAccountId() const
	{
		return m_AccountId;
	}

	uint64_t SessionManager::GetCharacterId() const
	{
		return m_CharacterId;
	}

	bool SessionManager::HasAccountId() const
	{
		return m_AccountId != InvalidId;
	}

	bool SessionManager::HasCharacterId() const
	{
		return m_CharacterId != InvalidId;
	}

	void SessionManager::SetAccountId(uint64_t accountId)
	{
		m_AccountId = accountId;
	}

	void SessionManager::SetCharacterId(uint64_t characterId)
	{
		m_CharacterId = characterId;
	}

}