#include "fblpch.h"
#include "LoginServer.h"

int main()
{
	EngineCreateInfo info;
	info.UseGraphics = false;
	Engine e(info);
	e.SetApplication<Fireblaze::LoginServer>();
	e.Run();
	
	return 0;
}