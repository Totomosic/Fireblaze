#pragma once
#include "fblpch.h"
#include "LoginServerConstants.h"

namespace Fireblaze
{

	FBL_API enum class RequestType
	{
		RegisterAccountRequst,
		LoginRequest,
		LogoutRequest,

		GetCharactersRequest,
		AddCharacterRequest,
		DeleteCharacterRequest
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(RequestType);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(RequestType);

}