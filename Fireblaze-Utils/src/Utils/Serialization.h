#pragma once
#include "Bolt.h"

#define FBL_DEFAULT_SERIALIZATION_FUNC_DEF(Type)	\
inline void Serialize(OutputMemoryStream& stream, const Type& value)	\
{	\
	stream.Write(value);	\
}

#define FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(Type)	\
inline void Deserialize(InputMemoryStream& stream, Type& value)	\
{	\
	stream.Read(&value);	\
}

namespace Fireblaze
{

	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(int8_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(uint8_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(int16_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(uint16_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(int32_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(uint32_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(int64_t);
	FBL_DEFAULT_SERIALIZATION_FUNC_DEF(uint64_t);

	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(int8_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(uint8_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(int16_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(uint16_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(int32_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(uint32_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(int64_t);
	FBL_DEFAULT_DESERIALIZATION_FUNC_DEF(uint64_t);

	inline void Serialize(OutputMemoryStream& stream, const blt::string& value)
	{
		Serialize(stream, value.length());
		stream.Write(value.data(), value.length());
	}

	inline void Deserialize(InputMemoryStream& stream, blt::string& value)
	{
		uint32_t length;
		Deserialize(stream, length);
		char* buffer = new char[length];
		stream.Read(buffer, length);
		value = blt::string(buffer, length);
		delete[] buffer;
	}

	template<typename T>
	inline void Serialize(OutputMemoryStream& stream, const std::vector<T>& value)
	{
		Serialize(stream, value.size());
		for (int i = 0; i < value.size(); i++)
		{
			Serialize(stream, value.at(i));
		}
	}

	template<typename T>
	inline void Deserialize(InputMemoryStream& stream, std::vector<T>& value)
	{
		std::vector<T>::size_type size;
		Deserialize(stream, size);
		value.resize(size);
		for (int i = 0; i < size; i++)
		{
			Deserialize(stream, value[i]);
		}
	}

}