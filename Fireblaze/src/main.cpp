#include "FireblazeClient.h"

int main()
{
	EngineCreateInfo info;
	info.WindowInfo.Resizable = false;
	Engine e(info);
	e.SetApplication<Fireblaze::FireblazeClient>();
	e.Run();

	return 0;
}