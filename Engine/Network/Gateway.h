#ifndef ENGINE_NETWORK_GATEWAY_H_
#define ENGINE_NETWORK_GATEWAY_H_

#include "BOOST/bind.hpp"

#include "Engine/Container/Pool.h"
#include "Engine/Processor/Service.h"
#include "Engine/Network/IHandler.hpp"

namespace Engine { namespace Network {

class Gateway_TCP : public NonCopyable {
public:
  inline Gateway_TCP( Processor::Service * _service
                    , Handler < shared_ptr < tcp::socket > > _tcp_connection_handler )
      : m_service(_service)
      , m_gateway(_service->service())
      , m_tcp_connection_handler(_tcp_connection_handler) {
    assert( _service && "Invalid _service @ Gateway_TCP::ctor" );
  }

  inline Gateway_TCP( Processor::Service * _service )
      : Gateway_TCP(_service, nullptr) {
  }

  inline virtual ~Gateway_TCP(void) {
  }

  inline boost::system::error_code Bind(address const& _address, uint32 const& _port) {
    boost::system::error_code error;

    m_gateway.open( tcp::v4(), error );
    if (error) return error;

    m_gateway.bind( tcp::endpoint( _address, _port ), error );
    return error;
  }

  inline void Listen(void) {
    if ( m_gateway.is_open() ) {
      shared_ptr < tcp::socket > accepted(new tcp::socket(m_service->service()));
      m_gateway.async_accept( *accepted
                            , boost::bind( &Gateway_TCP::Handle_Accept
                                         , this
                                         , accepted
                                         , boost::asio::placeholders::error ) );
    }
  }

  inline void set_handler( Handler < shared_ptr < tcp::socket > > _handler ) {
    m_tcp_connection_handler = _handler;
  }

protected:
  Processor::Service * m_service = nullptr;
  tcp::acceptor m_gateway;
  ThreadSafeHandler < shared_ptr < tcp::socket > > m_tcp_connection_handler;

  inline void Handle_Accept( shared_ptr < tcp::socket > _socket
                           , boost::system::error_code const& _error ) {
    if (!_error) {
      auto tcp_connection_handler = m_tcp_connection_handler.load();
      if (tcp_connection_handler) {
        tcp_connection_handler->Handle(_socket);
      }
    }

    Listen();
  }
};

class Gateway_Both : public NonCopyable {
private:
  class Gateway_UDP final : IHandler < shared_ptr < tcp::socket > > {
  public:
    inline Gateway_UDP( Processor::Service * _service
                      , Handler < shared_ptr < tcp::socket >
                                , shared_ptr < udp::socket > > _connection_handler )
        : m_connection_handler( _connection_handler )
        , m_udp_gateway( _service->service() ) {
      assert( _service && "Invalid _service @ TCP_Handler::ctor" );
    }

    inline ~Gateway_UDP(void) {
    }

    inline boost::system::error_code Bind( address const& _address, uint32 const& _port ) {
      boost::system::error_code error;

      m_udp_gateway.open( udp::v4(), error);
      if (error) return error;

      m_udp_gateway.bind( udp::endpoint( _address, _port ), error);
      return error;
    }

    inline void Handle( shared_ptr < tcp::socket > _tcp_socket ) {
      shared_ptr < udp::socket > udp_socket( new udp::socket( m_service->service() ) );

      m_udp_gateway.async_connect( udp::endpoint( _tcp_socket->remote_endpoint().address()
                                                , _tcp_socket->remote_endpoint().port() )
                                 , boost::bind( &Gateway_UDP::Handle_Connection
                                              , this
                                              , boost::asio::placeholders::error
                                              , _tcp_socket
                                              , udp_socket ));
    }

    inline void set_handler( Handler < shared_ptr < tcp::socket >
                                     , shared_ptr < udp::socket > > _handler ) {
      m_connection_handler = _handler;
    }

  protected:
    ThreadSafeHandler < shared_ptr < tcp::socket >
                      , shared_ptr < udp::socket > > m_connection_handler;

    Processor::Service * m_service = nullptr;
    udp::socket m_udp_gateway;

    inline void Handle_Connection( boost::system::error_code const& _error
                                 , shared_ptr < tcp::socket > _tcp_socket
                                 , shared_ptr < udp::socket > _udp_socket ) {
      if ( !_error ) {
        auto connection_handler = m_connection_handler.load();
        if ( connection_handler ) {
          connection_handler->Handle( _tcp_socket, _udp_socket );
        }
      }
    }
  };

public:
  inline Gateway_Both( Processor::Service * _service
                     , Handler < shared_ptr < tcp::socket >
                               , shared_ptr < udp::socket > > _connection_handler )
      : m_udp_gateway( new Gateway_UDP( _service, _connection_handler ) )
      , m_tcp_gateway( _service, m_udp_gateway ) {
  }

  inline Gateway_Both( Processor::Service * _service )
      : Gateway_Both(_service, nullptr) {
  }

  inline virtual ~Gateway_Both(void) {
  }

  inline boost::system::error_code Bind( address const& _address, uint32 const& _port ) {
    boost::system::error_code error;
    if ( error = m_tcp_gateway.Bind( _address, _port ) ) return error;
    if ( error = m_udp_gateway->Bind( _address, _port ) ) return error;
    return error;
  }

  inline void Listen(void) {
    m_tcp_gateway.Listen();
  }

  inline void set_handler(Handler < shared_ptr < tcp::socket >
                          , shared_ptr < udp::socket > > _connection_handler) {
    m_udp_gateway->set_handler( _connection_handler );
  }

protected:
  shared_ptr < Gateway_UDP > m_udp_gateway;
  Gateway_TCP m_tcp_gateway;
};

} }

#endif