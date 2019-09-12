#pragma once

namespace Fireblaze
{

	extern blt::string FireblazeCommonDataDirectory;

}

#define FBL_API
#define FIREBLAZE_SQL_SERVER_CONFIG_FILE FireblazeCommonDataDirectory + "SQLServer.cfg"
#define FIREBLAZE_LOGIN_SERVER_CONFIG_FILE FireblazeCommonDataDirectory + "LoginServer.cfg"
#define FIREBLAZE_CHAT_SERVER_CONFIG_FILE FireblazeCommonDataDirectory + "ChatServer.cfg"