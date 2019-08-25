#pragma once
#include "clientpch.h"

namespace Fireblaze
{

	class FBL_API SessionManager
	{
	private:
		uint64_t m_AccountId;
		uint64_t m_CharacterId;

	public:
		SessionManager();

		uint64_t GetAccountId() const;
		uint64_t GetCharacterId() const;
		bool HasAccountId() const;
		bool HasCharacterId() const;

		void SetAccountId(uint64_t accountId);
		void SetCharacterId(uint64_t characterId);

	};

}