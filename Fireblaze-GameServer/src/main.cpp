#include "gspch.h"
#include "GameServer.h"

namespace Fireblaze
{

	blt::string FireblazeCommonDataDirectory;

}

void usage(const char* name)
{
	std::cout << "Usage " << name << " [CommonDataDir]" << std::endl;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	else if (argc == 2)
	{
		Fireblaze::FireblazeCommonDataDirectory = argv[1];
		if (Fireblaze::FireblazeCommonDataDirectory.back() != '/' || Fireblaze::FireblazeCommonDataDirectory.back() != '\\')
		{
			Fireblaze::FireblazeCommonDataDirectory += '/';
		}
	}
	else
	{
		Fireblaze::FireblazeCommonDataDirectory = "../CommonData/";
	}
	EngineCreateInfo info;
	info.UseGraphics = false;
	Engine e(info);
	e.SetApplication<Fireblaze::GameServer>();
	e.Run();
	return 0;
}