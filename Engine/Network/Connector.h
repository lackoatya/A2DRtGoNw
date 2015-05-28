#ifndef ENGINE_NETWORK_CONNECTOR_H_
#define ENGINE_NETWORK_CONNECTOR_H_

#include "BOOST/bind.hpp"

#include "Engine/Platform.h"
#include "Engine/Processor/Service.h"
#include "Engine/Network/IHandler.hpp"

namespace Engine { namespace Network {

class Connector : public NonCopyable {
public:
  ThreadSafeHandler < boost::system::error_code const& > m_error_handler;
  ThreadSafeHandler < shared_ptr < tcp::socket >, shared_ptr < udp::socket > > m_connection_handler;

  inline Connector( Processor::Service * _service )
      : m_service(_service)
      , tcp_connector( new tcp::socket( m_service->service() ) )
      , udp_connector( new udp::socket( m_service->service() ) ) {
    assert( _service && "Invalid _service @ Connector::ctor" );
  }

  inline boost::system::error_code Bind( tcp::endpoint const& _local_tcp
                                       , udp::endpoint const& _local_udp ) {
    boost::system::error_code error;

    tcp_connector->open(_local_tcp.protocol(), error);
    if (error) return error;
    tcp_connector->bind(_local_tcp, error);
    if (error) return error;

    udp_connector->open(_local_udp.protocol(), error);
    if (error) return error;
    udp_connector->bind(_local_udp, error);
    return error;
  }

  inline void Connect( tcp::endpoint const& _remote_tcp
                     , udp::endpoint const& _remote_udp ) {
    assert( tcp_connector->is_open() && "Connecting before successful TCP Binding @ Connector::Connect" );
    assert( udp_connector->is_open() && "Connecting before successful UDP Binding @ Connector::Connect" );

    Connect_TCP( _remote_tcp, _remote_udp );
  }

protected:
  Processor::Service * m_service = nullptr;

  shared_ptr < tcp::socket > tcp_connector = nullptr;
  shared_ptr < udp::socket > udp_connector = nullptr;

  void Connect_TCP( tcp::endpoint const& _remote_tcp
                  , udp::endpoint const& _remote_udp ) {
    boost::system::error_code error;

    tcp_connector->async_connect( _remote_tcp, boost::bind( &Connector::Handle_TCP_Connect
                                                          , this
                                                          , boost::asio::placeholders::error
                                                          , _remote_udp) );
  }

  void Handle_TCP_Connect( boost::system::error_code const& _error, udp::endpoint _remote_udp ) {
    if ( !_error ) {
      Connect_UDP( _remote_udp );
    } else {
      auto error_handler = m_error_handler.load();
      if ( error_handler ) {
        error_handler->Handle( _error );
      }
    }
  }

  void Connect_UDP( udp::endpoint const& _remote_udp ) {
    boost::system::error_code error;

    udp_connector->async_connect( _remote_udp, boost::bind( &Connector::Handle_UDP_Connect
                                                          , this
                                                          , boost::asio::placeholders::error ) );
  }

  void Handle_UDP_Connect( boost::system::error_code const& _error ) {
    if ( !_error ) {
      auto connection_handler = m_connection_handler.load();
      if ( connection_handler ) {
        connection_handler->Handle( tcp_connector, udp_connector );
      }
    }
    else {
      auto error_handler = m_error_handler.load();
      if ( error_handler ) {
        error_handler->Handle( _error );
      }
    }
  }
};

} }

#endif