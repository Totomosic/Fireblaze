#pragma once
#include "Bolt.h"

#define FIREBLAZE_COMMON_DATA_DIRECTORY "../CommonData/"

namespace Fireblaze
{

	std::unordered_map<blt::string, blt::string> ReadConfigFile(const Filepath& path);

}