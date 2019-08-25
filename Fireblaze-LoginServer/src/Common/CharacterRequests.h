#pragma once
#include "Requests.h"

namespace Fireblaze
{

	// ===========================================================================================================================================
	// GET CHARACTERS REQUEST
	// ===========================================================================================================================================

	struct FBL_API GetCharactersRequest
	{
	public:
		static constexpr int ALL_CHARACTERS_INDEX = -1;

	public:
		uint64_t AccountId = InvalidId;
		int CharacterIndex = ALL_CHARACTERS_INDEX;
	};

	inline void Serialize(OutputMemoryStream& stream, const GetCharactersRequest& request)
	{
		Serialize(stream, request.AccountId);
		Serialize(stream, request.CharacterIndex);
	}

	inline void Deserialize(InputMemoryStream& stream, GetCharactersRequest& request)
	{
		Deserialize(stream, request.AccountId);
		Deserialize(stream, request.CharacterIndex);
	}

	// ===========================================================================================================================================
	// ADD CHARACTER REQUEST
	// ===========================================================================================================================================

	struct FBL_API CharacterCreateData
	{
	public:
		blt::string Name;
		int Level;
	};

	inline void Serialize(OutputMemoryStream& stream, const CharacterCreateData& data)
	{
		Serialize(stream, data.Name);
		Serialize(stream, data.Level);
	}

	inline void Deserialize(InputMemoryStream& stream, CharacterCreateData& data)
	{
		Deserialize(stream, data.Name);
		Deserialize(stream, data.Level);
	}

	struct FBL_API AddCharacterRequest
	{
	public:
		uint64_t AccountId = InvalidId;
		CharacterCreateData CreateData;
	};

	inline void Serialize(OutputMemoryStream& stream, const AddCharacterRequest& request)
	{
		Serialize(stream, request.AccountId);
		Serialize(stream, request.CreateData);
	}

	inline void Deserialize(InputMemoryStream& stream, AddCharacterRequest& request)
	{
		Deserialize(stream, request.AccountId);
		Deserialize(stream, request.CreateData);
	}

	// ===========================================================================================================================================
	// DELETE CHARACTER REQUEST
	// ===========================================================================================================================================

	struct FBL_API DeleteCharacterRequest
	{
	public:
		uint64_t AccountId = InvalidId;
		uint64_t CharacterId = InvalidId;
	};

	inline void Serialize(OutputMemoryStream& stream, const DeleteCharacterRequest& request)
	{
		Serialize(stream, request.AccountId);
		Serialize(stream, request.CharacterId);
	}

	inline void Deserialize(InputMemoryStream& stream, DeleteCharacterRequest& request)
	{
		Deserialize(stream, request.AccountId);
		Deserialize(stream, request.CharacterId);
	}

}