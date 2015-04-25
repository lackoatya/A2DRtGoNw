#ifndef ENGINE_NETWORK_CONNECTION_H
#define ENGINE_NETWORK_CONNECTION_H

#include <string>
#include <memory>

#include "BOOST/asio.hpp"
#include "BOOST/bind.hpp"

#include "Engine/Types.h"
#include "Engine/Processor/Service.h"

// TODO Modify char * to void * and get an Allocator?

namespace Engine {
namespace Network {
class CommandHandlerInterface {
  public:
    virtual void Handle_TCP(char const* _data, size_t _received) = 0;
    virtual void Handle_UDP(char const* _data, size_t _received) = 0;
};

class PacketInterface {
  public:
    virtual char * const data(void) = 0;
    virtual uint32 const size(void) = 0;
};

class Connection {
  public:

  public:
    struct Configuration {
      const uint32 packet_max_size;
    } const m_configuration;

    atomic < shared_ptr < CommandHandlerInterface > > m_handler;

    void Start(void) {
      char * tcp_data = new char[m_configuration.packet_max_size];
      char * udp_data = new char[m_configuration.packet_max_size];

      TCP_Receive(tcp_data);
      UDP_Receive(udp_data);
    }

    virtual void TCP_Send(shared_ptr < PacketInterface > _packet) {
      assert( _packet->size() < m_configuration.packet_max_size );
      m_tcp_socket->async_send( boost::asio::buffer( _packet->data(), _packet->size() )
                              , boost::bind( &Handle_TCP_Send
                                            , this
                                            , boost::asio::placeholders::error
                                            , boost::asio::placeholders::bytes_transferred ) );
    }

    virtual void UDP_Send(shared_ptr < PacketInterface > _packet) {
      assert( _packet->size() < m_configuration.packet_max_size );
      m_udp_socket->async_send( boost::asio::buffer( _packet->data(), _packet->size() )
                              , boost::bind( &Handle_UDP_Send
                                           , this
                                           , boost::asio::placeholders::error
                                           , boost::asio::placeholders::bytes_transferred ) );
    }

  protected:
    shared_ptr < tcp_socket > m_tcp_socket = nullptr;
    shared_ptr < udp_socket > m_udp_socket = nullptr;

    inline Connection( Configuration const& _configuration
                     , shared_ptr < CommandHandlerInterface > _handler
                     , shared_ptr < tcp_socket > _tcp_socket
                     , shared_ptr < udp_socket > _udp_socket)
        : m_configuration(_configuration)
        , m_handler(_handler)
        , m_tcp_socket(_tcp_socket)
        , m_udp_socket(_udp_socket) {
      assert( _tcp_socket && _udp_socket );
      }
    inline virtual ~Connection() = default;

    // TCP
    virtual void TCP_Receive(char const* _data) {
      if ( m_tcp_socket && m_tcp_socket->is_open() ) {
        m_tcp_socket->async_receive( boost::asio::buffer( _data, m_configuration.packet_max_size )
                                   , boost::bind(&Handle_TCP_Receive
                                                , this
                                                , boost::asio::placeholders::error
                                                , _data
                                                , boost::asio::placeholders::bytes_transferred ) );
      }
    }

    virtual void Handle_TCP_Receive( boost::system::error_code const& _error, char const* _data
                                   , size_t _received) {
      if ( !_error ) {
        shared_ptr < CommandHandlerInterface > handler = m_handler.load();
        if ( handler ) {
          handler->Handle_TCP( _data, _received );
        }

        TCP_Receive( _data );
      }
      else {
        // TODO what's this?!
        if ( _error.value() == 995 ) return;
        else {
          delete[] _data;
          Dispose();
        }
      }
    }

    virtual void Connection::Handle_TCP_Send(boost::system::error_code const& _error
                                           , size_t _sent) {
      if (_error) {
        // TODO what's this?!
        if ( _error.value() == 995 ) return;
        else Dispose();
      }
    }

    // UDP
    virtual void UDP_Receive(char const* _data) {
      if ( m_udp_socket && m_udp_socket->is_open ) {
        m_udp_socket->async_receive( boost::asio::buffer( _data, m_configuration.packet_max_size )
                                   , boost::bind( &Handle_UDP_Receive
                                                , this
                                                , boost::asio::placeholders::error
                                                , _data
                                                , boost::asio::placeholders::bytes_transferred ) );
      }
    }

    virtual void Handle_UDP_Receive(boost::system::error_code const& _error, char const* _data
                                  , size_t _received) {
      if ( !_error ) {
        shared_ptr < CommandHandlerInterface > handler = m_handler.load();
        if ( handler ) {
          handler->Handle_UDP( _data, _received );
        }

        UDP_Receive( _data );
      }
      else {
        // TODO what's this?!
        if ( _error.value() == 995 ) return;
        else {
          delete[] _data;
          Dispose();
        }
      }
    }

    virtual void Handle_UDP_Send(boost::system::error_code const& _error, size_t _sent) {
      if (_error) {
        // TODO what's this?!
        if ( _error.value() == 995 ) return;
        else Dispose();
      }
    }

    virtual void Dispose(void) {
      m_tcp_socket->close();
      m_udp_socket->close();

      // TODO delete this; Like @ Gateway?
    }
};
}
}

#endif