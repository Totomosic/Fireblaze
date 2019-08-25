#pragma once
#include "fblpch.h"

namespace Fireblaze
{

	struct FBL_API CharacterOverviewData
	{
	public:
		uint64_t CharacterId = InvalidId;
		blt::string Name;
		int Level = 0;
	};

	inline void Serialize(OutputMemoryStream& stream, const CharacterOverviewData& data)
	{
		Serialize(stream, data.CharacterId);
		Serialize(stream, data.Name);
		Serialize(stream, data.Level);
	}

	inline void Deserialize(InputMemoryStream& stream, CharacterOverviewData& data)
	{
		Deserialize(stream, data.CharacterId);
		Deserialize(stream, data.Name);
		Deserialize(stream, data.Level);
	}

}