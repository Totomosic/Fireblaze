#pragma once
#include "Bolt.h"
#include "FBLDefines.h"

namespace Fireblaze
{

	FBL_API std::unordered_map<blt::string, blt::string> ReadConfigFile(const Filepath& path);

}