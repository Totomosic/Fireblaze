#pragma once
#include "Requests.h"

namespace Fireblaze
{

	// ===========================================================================================================================================
	// REGISTER ACCOUNT REQUEST
	// ===========================================================================================================================================

	struct FBL_API RegisterAccountRequest
	{
	public:
		blt::string Username;
		blt::string Password;
		blt::string Email;
	};

	inline void Serialize(OutputMemoryStream& stream, const RegisterAccountRequest& value)
	{
		Serialize(stream, value.Username);
		Serialize(stream, value.Password);
		Serialize(stream, value.Email);
	}

	inline void Deserialize(InputMemoryStream& stream, RegisterAccountRequest& value)
	{
		Deserialize(stream, value.Username);
		Deserialize(stream, value.Password);
		Deserialize(stream, value.Email);
	}

	// ===========================================================================================================================================
	// LOGIN REQUEST
	// ===========================================================================================================================================

	struct FBL_API LoginRequest
	{
	public:
		blt::string Username;
		blt::string Password;
	};

	inline void Serialize(OutputMemoryStream& stream, const LoginRequest& value)
	{
		Serialize(stream, value.Username);
		Serialize(stream, value.Password);
	}

	inline void Deserialize(InputMemoryStream& stream, LoginRequest& value)
	{
		Deserialize(stream, value.Username);
		Deserialize(stream, value.Password);
	}

	// ===========================================================================================================================================
	// LOGOUT REQUEST
	// ===========================================================================================================================================

	struct FBL_API LogoutRequest
	{
	public:
		uint64_t AccountId;
	};

	inline void Serialize(OutputMemoryStream& stream, const LogoutRequest& value)
	{
		Serialize(stream, value.AccountId);
	}

	inline void Deserialize(InputMemoryStream& stream, LogoutRequest& value)
	{
		Deserialize(stream, value.AccountId);
	}

}