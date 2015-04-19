#ifndef ENGINE_NETWORK_CONNECTION_H
#define ENGINE_NETWORK_CONNECTION_H

#include <string>
#include <memory>

#include "BOOST/asio.hpp"

#include "Engine/Types.h"
#include "Engine/Processor/Service.h"
#include "Engine/Network/CommandHandlerInterface.h"

namespace Engine {
namespace Network {
struct ConnectionConfiguration {
  const uint32 packet_max_size;
};

template < class Packet >
class Connection {
  public:
    const ConnectionConfiguration configuration;

    void Start(void) {
      char * tcp_data = new char[configurationpacket_max_size];
      char * udp_data = new char[configuration.packet_max_size];

      TCP_Receive(tcp_data);
      UDP_Receive(udp_data);
    }

    virtual void TCP_Send(const Packet const* _packet) {
      m_tcp_socket.async_send(boost::asio::buffer(_packet->data(), _packet->size()),
                              boost::bind(&Handle_TCP_Send
                              , this
                              , boost::asio::placeholders::error
                              , boost::asio::placeholders::bytes_transferred));
    }

    virtual void UDP_Send(const Packet const* _packet) {
      m_udp_socket.async_send(boost::asio::buffer(_packet->data(), _packet->size())
                            , boost::bind(&Handle_UDP_Send, this
                            , boost::asio::placeholders::error
                            , boost::asio::placeholders::bytes_transferred));
    }

    void set_handler(CommandHandlerInterface _handler) {
      m_handler = _handler;
    }

  protected:
    CommandHandlerInterface m_handler;

    boost::asio::ip::tcp::socket m_tcp_socket;
    boost::asio::ip::udp::socket m_udp_socket;

    inline Connection( ConnectionConfiguration _configuration
                     , CommandHandlerInterface _handler
                     , boost::asio::ip::tcp::socket _tcp_socket
                     , boost::asio::ip::udp::socket _udp_socket)
        : configuration(_configuration)
        , m_handler(_handler)
        , m_tcp_socket(std::move(_tcp_socket))
        , m_udp_socket(std::move(_udp_socket)) { }
    inline virtual ~ConnectionInterface() = default;

    // TCP
    virtual void TCP_Receive(char const* _data) {
      if (m_tcp_socket.is_open)
        m_tcp_socket.async_receive(boost::asio::buffer(_data, configuration.packet_max_size)
                                 , boost::bind(&Handle_TCP_Receive
                                             , this
                                             , boost::asio::placeholders::error
                                             , _data
                                             , boost::asio::placeholders::bytes_transferred));
    }

    virtual void Handle_TCP_Receive(boost::system::error_code const& _error, char const* _data
                                  , size_t _received) {
      if (!_error) {
        m_handler.Handle_TCP(_data, _received);
        TCP_Receive(_data);
      }
      else {
        // TODO what's this?!
        if (_error.value() == 995) return;
        else {
          delete[] _data;
          Dispose();
        }
      }
    }


    virtual void Connection::Handle_TCP_Send(boost::system::error_code const& _error
                                           , size_t _sent) {
      if (_error)
        if (_error.value() == 995) return;
        else Dispose();
    }

    // UDP
    virtual void UDP_Receive(char const* _data) {
      if (m_udp_socket.is_open)
        m_udp_socket.async_receive(boost::asio::buffer(_data, configuration.packet_max_size)
                                 , boost::bind(&Handle_UDP_Receive, this
                                             , boost::asio::placeholders::error
                                             , _data
                                             , boost::asio::placeholders::bytes_transferred));
    }

    virtual void Handle_UDP_Receive(boost::system::error_code const& _error, char const* _data
                                  , size_t _received) {
      if (!_error) {
        m_handler.Handle_UDP(_data, _received);
        UDP_Receive(_data);
      }
      else {
        if (_error.value() == 995) return;
        else {
          delete[] _data;
          Dispose();
        }
      }
    }

    virtual void Handle_UDP_Send(boost::system::error_code const& _error, size_t _sent) {
      if (_error)
        if (_error.value() == 995) return;
        else Dispose();
    }

    virtual Dispose(void) {
      tcp_socket.close();
      udp_socket.close();
    }
};
}
}

#endif