#pragma once

#include <string>

#include "BOOST\asio.hpp"
#include "BOOST\thread.hpp"
#include "BOOST\atomic.hpp"

#include "Engine\Types.h"

struct Packet;
class Hero;
class Gateway;

namespace Engine
{
	namespace Network
	{
		/*enum class ServerCommand
		{
			UDP_PORT = 0,
			GAME_STATE,

			Count
		};

		enum class ClientCommand
		{
			LOGIN = 0
		};*/

		class Connection
		{
		public:
			Connection() = delete;
			Connection(boost::asio::io_service &_io_service);
			Connection(Connection const& _other) = delete;
			Connection & operator=(Connection const& _other) = delete;
			virtual ~Connection();

			void Start();

			void TCP_Send(Packet *_packet);

			void UDP_Send(Packet *_packet);

			inline boost::asio::ip::tcp::socket const& TCP_Socket() const { return tcp_socket; };
			inline boost::asio::ip::udp::socket const& UDP_Socket() const { return udp_socket; };

			// TODO this should be pure virtual, right?
			virtual void Dispose();

			virtual void Process(char *_data, size_t _received) = 0;

		protected:
			atomic< bool > disposed;

			// TODO This shouldn't be base class specific!
			//shared_ptr< Hero > hero = 0;

			// TCP
			char *tcp_data = 0;
			boost::asio::ip::tcp::socket tcp_socket;

			void TCP_Receive();
			void Handle_TCP_Receive(boost::system::error_code const& _error, size_t const& _received);

			void Handle_TCP_Send(boost::system::error_code const& _error, size_t const& _sent);

			// UDP
			char *udp_data = 0;
			boost::asio::ip::udp::socket udp_socket;

			void UDP_Receive();
			void Handle_UDP_Receive(boost::system::error_code const& _error, size_t const& _received);

			void Handle_UDP_Send(boost::system::error_code const& _error, size_t const& _sent);
		};
	}
}