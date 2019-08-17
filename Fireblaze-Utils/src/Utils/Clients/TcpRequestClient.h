#pragma once
#include "../Serialization.h"
#include "FBLDefines.h"

namespace Fireblaze
{

	template<typename T>
	class FBL_API TcpRequestClient
	{
	private:
		TCPsocket m_Socket;

	public:
		TcpRequestClient()
			: m_Socket()
		{
		
		}

		int Connect(const SocketAddress& address)
		{
			return m_Socket.Connect(address);
		}

		template<typename RequestT, typename ResponseT>
		ResponseT Request(T key, const RequestT& data)
		{
			OutputMemoryStream stream;
			Serialize(stream, key);
			Serialize(stream, data);
			m_Socket.Send(stream.GetBufferPtr(), stream.GetRemainingDataSize());
			char buffer[4096];
			int received = m_Socket.Recv(buffer, sizeof(buffer));
			if (received > 0)
			{
				InputMemoryStream stream(received);
				memcpy(stream.GetBufferPtr(), buffer, received);
				ResponseT response;
				Deserialize(stream, response);
				return response;
			}
			return ResponseT();
		}

	};

}