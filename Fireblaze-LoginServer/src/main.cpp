#include "fblpch.h"
#include "Engine/Initialization/Initializer.h"

namespace Fireblaze
{
	const char* DATABASE_SERVER_ADDRESS = "localhost";
	constexpr uint32_t DATABASE_SERVER_PORT = 3300;

	TCPsocket ConnectToDatabaseServer()
	{
		SocketAddress addr(DATABASE_SERVER_ADDRESS, DATABASE_SERVER_PORT);
		TCPsocket socket;
		socket.Connect(addr);
		return socket;
	}

}

int main()
{
	EngineCreateInfo info;
	info.UseGraphics = false;
	Bolt::Initializer::PreOpenGL(info);
	TCPsocket socket = Fireblaze::ConnectToDatabaseServer();
	socket.Send("SHOW tables;", 13);
	socket.Close();
	return 0;
}