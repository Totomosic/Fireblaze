#pragma once
#include "fblpch.h"
#include "CharacterData.h"
#include "LoginServerConstants.h"

namespace Fireblaze
{

	// ===========================================================================================================================================
	// GET CHARACTERS RESPONSE
	// ===========================================================================================================================================

	FBL_API enum class GetCharactersFailReason
	{
		Ok,
		CannotConnect,
		InvalidAccount
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(GetCharactersFailReason);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(GetCharactersFailReason);

	struct FBL_API GetCharactersResponse
	{
	public:
		uint64_t AccountId = InvalidId;
		std::vector<CharacterOverviewData> Characters;
		GetCharactersFailReason FailReason;
	};

	inline void Serialize(OutputMemoryStream& stream, const GetCharactersResponse& response)
	{
		Serialize(stream, response.AccountId);
		Serialize(stream, response.Characters);
		Serialize(stream, response.FailReason);
	}

	inline void Deserialize(InputMemoryStream& stream, GetCharactersResponse& response)
	{
		Deserialize(stream, response.AccountId);
		Deserialize(stream, response.Characters);
		Deserialize(stream, response.FailReason);
	}

	// ===========================================================================================================================================
	// ADD CHARACTER RESPONSE
	// ===========================================================================================================================================

	FBL_API enum class AddCharacterFailReason
	{
		Ok,
		CannotConnect,
		InvalidAccount,
		InvalidName,
		InvalidCreateData
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(AddCharacterFailReason);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(AddCharacterFailReason);

	struct FBL_API AddCharacterResponse
	{
	public:
		uint64_t AccountId = InvalidId;
		CharacterOverviewData Character;
		AddCharacterFailReason FailReason;
	};

	inline void Serialize(OutputMemoryStream& stream, const AddCharacterResponse& response)
	{
		Serialize(stream, response.AccountId);
		Serialize(stream, response.Character);
		Serialize(stream, response.FailReason);
	}

	inline void Deserialize(InputMemoryStream& stream, AddCharacterResponse& response)
	{
		Deserialize(stream, response.AccountId);
		Deserialize(stream, response.Character);
		Deserialize(stream, response.FailReason);
	}

	// ===========================================================================================================================================
	// DELETE CHARACTER RESPONSE
	// ===========================================================================================================================================

	FBL_API enum class DeleteCharacterFailReason
	{
		Ok,
		CannotConnect,
		InvalidAccount,
		InvalidCharacter
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(DeleteCharacterFailReason);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(DeleteCharacterFailReason);

	struct FBL_API DeleteCharacterResponse
	{
	public:
		uint64_t AccountId = InvalidId;
		DeleteCharacterFailReason FailReason;
	};

	inline void Serialize(OutputMemoryStream& stream, const DeleteCharacterResponse& response)
	{
		Serialize(stream, response.AccountId);
		Serialize(stream, response.FailReason);
	}

	inline void Deserialize(InputMemoryStream& stream, DeleteCharacterResponse& response)
	{
		Deserialize(stream, response.AccountId);
		Deserialize(stream, response.FailReason);
	}

}