#pragma once
#include "../Serialization.h"
#include "FBLDefines.h"

namespace Fireblaze
{

	template<typename T>
	class FBL_API TcpRequestServer
	{
	private:
		std::mutex m_FunctionMutex;
		TCPsocket m_Socket;
		std::unordered_map<T, std::function<OutputMemoryStream(InputMemoryStream&)>> m_Functions;
		std::function<void(TCPsocket&, const SocketAddress&)> m_OnConnect;
		std::function<void(TCPsocket&, const SocketAddress&)> m_OnDisconnect;

	public:
		TcpRequestServer()
			: m_FunctionMutex(), m_Socket(), m_Functions()
		{
		
		}

		int Bind(const SocketAddress& address)
		{
			return m_Socket.Bind(address);
		}

		void Listen(int backlog)
		{
			m_Socket.Listen(backlog);
			TaskManager::Run([&server = m_Socket, &functions = m_Functions, &onConnect = m_OnConnect, &onDisconnect = m_OnDisconnect, &mutex = m_FunctionMutex]() mutable
				{
					SocketAddress from;
					while (true)
					{
						TCPsocket client = server.Accept(&from);
						TaskManager::Run(make_shared_function([client{ std::move(client) }, &functions, address{ std::move(from) }, &onConnect, &onDisconnect, &mutex]() mutable
							{
								if (onConnect)
								{
									std::scoped_lock<std::mutex> lock(mutex);
									onConnect(client, address);
								}
								char buffer[4096];
								while (true)
								{
									int received = client.Recv(buffer, sizeof(buffer));
									if (received > 0)
									{
										InputMemoryStream data(received);
										memcpy(data.GetBufferPtr(), buffer, received);
										T key;
										Deserialize(data, key);
										if (functions.find(key) != functions.end())
										{
											std::scoped_lock<std::mutex> lock(mutex);
											OutputMemoryStream response = functions.at(key)(data);
											client.Send(response.GetBufferPtr(), response.GetRemainingDataSize());
										}
									}
									else
									{
										break;
									}
								}
								if (onDisconnect)
								{
									std::scoped_lock<std::mutex> lock(mutex);
									onDisconnect(client, address);
								}
							}));
					}
				});
		}

		template<typename PacketT, typename ResponseT>
		void RegisterHandler(T key, const std::function<ResponseT(PacketT&)>& function)
		{
			std::scoped_lock<std::mutex> lock(m_FunctionMutex);
			m_Functions[key] = [function](InputMemoryStream& stream)
				{
					PacketT packet;
					Deserialize(stream, packet);
					ResponseT response = function(packet);
					OutputMemoryStream responseData;
					Serialize(responseData, response);
					return responseData;
				};
		}

		void OnClientConnect(const std::function<void(TCPsocket&, const SocketAddress&)>& function)
		{
			std::scoped_lock<std::mutex> lock(m_FunctionMutex);
			m_OnConnect = function;
		}

		void OnClientDisconnect(const std::function<void(TCPsocket&, const SocketAddress&)>& function)
		{
			std::scoped_lock<std::mutex> lock(m_FunctionMutex);
			m_OnDisconnect = function;
		}

	};

}