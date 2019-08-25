#pragma once
#include "fblpch.h"
#include "Utils/Serialization.h"

namespace Fireblaze
{

	// ===========================================================================================================================================
	// REGISTER ACCOUNT RESPONSE
	// ===========================================================================================================================================

	FBL_API enum class RegisterAccountFailReason
	{
		Ok,
		CannotConnect,
		InvalidUsername,
		InvalidPassword,
		InvalidEmail,
		UsernameAlreadyExists
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(RegisterAccountFailReason);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(RegisterAccountFailReason);

	struct FBL_API RegisterAccountResponse
	{
	public:
		uint64_t AccountId = InvalidId;
		RegisterAccountFailReason FailReason = RegisterAccountFailReason::InvalidUsername;
	};

	inline void Serialize(OutputMemoryStream& stream, const RegisterAccountResponse& value)
	{
		Serialize(stream, value.AccountId);
		Serialize(stream, value.FailReason);
	}
	
	inline void Deserialize(InputMemoryStream& stream, RegisterAccountResponse& value)
	{
		Deserialize(stream, value.AccountId);
		Deserialize(stream, value.FailReason);
	}

	// ===========================================================================================================================================
	// LOGIN RESPONSE
	// ===========================================================================================================================================

	FBL_API enum class LoginFailReason
	{
		Ok,
		CannotConnect,
		InvalidUsername,
		InvalidPassword,
		AlreadyLoggedIn
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(LoginFailReason);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(LoginFailReason);

	struct FBL_API LoginResponse
	{
	public:
		uint64_t AccountId = InvalidId;
		LoginFailReason FailReason = LoginFailReason::InvalidUsername;
	};

	inline void Serialize(OutputMemoryStream& stream, const LoginResponse& value)
	{
		Serialize(stream, value.AccountId);
		Serialize(stream, value.FailReason);
	}

	inline void Deserialize(InputMemoryStream& stream, LoginResponse& value)
	{
		Deserialize(stream, value.AccountId);
		Deserialize(stream, value.FailReason);
	}

	// ===========================================================================================================================================
	// LOGOUT RESPONSE
	// ===========================================================================================================================================

	FBL_API enum class LogoutFailReason
	{
		Ok,
		CannotConnect,
		NotLoggedIn
	};

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(LogoutFailReason);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(LogoutFailReason);

	struct FBL_API LogoutResponse
	{
	public:
		LogoutFailReason FailReason = LogoutFailReason::NotLoggedIn;
	};

	inline void Serialize(OutputMemoryStream& stream, const LogoutResponse& value)
	{
		Serialize(stream, value.FailReason);
	}

	inline void Deserialize(InputMemoryStream& stream, LogoutResponse& value)
	{
		Deserialize(stream, value.FailReason);
	}

}