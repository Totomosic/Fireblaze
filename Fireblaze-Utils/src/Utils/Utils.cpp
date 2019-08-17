#include "Utils.h"

namespace Fireblaze
{

	std::unordered_map<blt::string, blt::string> ReadConfigFile(const Filepath& file)
	{
		std::unordered_map<blt::string, blt::string> result;
		File f = Filesystem::Open(file, OpenMode::Read);
		blt::string data = f.ReadText();
		std::vector<blt::string> lines = data.split('\n');
		for (blt::string& line : lines)
		{
			if (!line.contains('='))
			{
				continue;
			}
			line.remove_all("\n\r\t ");
			uint32_t index = line.find_first_of('=');
			result[line.substr(0, index)] = line.substr(index + 1);
		}
		return result;
	}

}