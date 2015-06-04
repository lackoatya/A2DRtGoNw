#ifndef ENGINE_NETWORK_CONNECTOR_H_
#define ENGINE_NETWORK_CONNECTOR_H_

#include "BOOST/bind.hpp"

#include "Engine/Platform.h"
#include "Engine/Processor/Service.h"
#include "Engine/Network/IHandler.hpp"

namespace Engine { namespace Network {

namespace Implementation {

class IConnector : public NonCopyable {
protected:
  shared_ptr< Processor::Service > m_service = nullptr;
  ThreadSafeHandler< boost::system::error_code const& > m_error_handler;

  inline IConnector( shared_ptr< Processor::Service > _service
                   , Handler< boost::system::error_code const& > _error_handler = nullptr )
      : m_service( _service )
      , m_error_handler( _error_handler ) {
    assert( _service && "Invalid _service @ IConnector::ctor" );
  }

  inline virtual ~IConnector(void) {
  }
};

class IConnector_TCP : public NonCopyable {
protected:
  shared_ptr< tcp::socket > m_tcp_connector = nullptr;

  inline explicit IConnector_TCP( shared_ptr< Processor::Service > _service )
      : m_tcp_connector( new tcp::socket( _service->service() ) ) {
    assert( _service && "Invalid _service @ IConnector_TCP::ctor" );
  }

  inline virtual ~IConnector_TCP(void) {
  }

  inline boost::system::error_code Bind( tcp::endpoint const& _local_tcp ) {
    boost::system::error_code error;

    m_tcp_connector->open( _local_tcp.protocol(), error );
    if ( error ) return error;
    m_tcp_connector->bind( _local_tcp, error );
    return error;
  }

  inline void Connect( tcp::endpoint const& _remote_tcp ) {
    assert( m_tcp_connector->is_open() && "Connecting before successful TCP Binding @ IConnector_TCP::Connect" );

    Connect_TCP( _remote_tcp );
  }

  virtual void Handle_TCP(void) = 0;
  virtual void Handle_TCP_Error( boost::system::error_code const& _error) = 0;

private:
  void Connect_TCP( tcp::endpoint const& _remote_tcp ) {
    boost::system::error_code error;

    m_tcp_connector->async_connect( _remote_tcp, boost::bind( &IConnector_TCP::Handle_TCP_Connect
                                                            , this
                                                            , boost::asio::placeholders::error ) );
  }

  void Handle_TCP_Connect( boost::system::error_code const& _error ) {
    if ( !_error ) {
      Handle_TCP();
    } else {
      Handle_TCP_Error( _error );
    }
  }
};

class IConnector_UDP : public NonCopyable {
protected:
  shared_ptr< udp::socket > m_udp_connector = nullptr;

  inline explicit IConnector_UDP( shared_ptr< Processor::Service > _service )
      : m_udp_connector( new udp::socket( _service->service() ) ) {
    assert( _service && "Invalid _service @ IConnector_UDP::ctor" );
  }

  inline virtual ~IConnector_UDP(void) {
  }

  inline boost::system::error_code Bind( udp::endpoint const& _local_udp ) {
    boost::system::error_code error;

    m_udp_connector->open( _local_udp.protocol(), error );
    if (error) return error;
    m_udp_connector->bind( _local_udp, error );
    return error;
  }

  inline void Connect( udp::endpoint const& _remote_udp ) {
    assert( m_udp_connector->is_open() && "Connecting before successful UDP Binding @ IConnector_UDP::Connect" );

    Connect_UDP( _remote_udp );
  }

  virtual void Handle_UDP(void) = 0;
  virtual void Handle_UDP_Error( boost::system::error_code const& _error ) = 0;

private:
  void Connect_UDP( udp::endpoint const& _remote_udp ) {
    boost::system::error_code error;

    m_udp_connector->async_connect( _remote_udp, boost::bind( &IConnector_UDP::Handle_UDP_Connect
                                                            , this
                                                            , boost::asio::placeholders::error ) );
  }

  void Handle_UDP_Connect(boost::system::error_code const& _error ) {
    if (!_error) {
      Handle_UDP();
    } else {
      Handle_UDP_Error( _error );
    }
  }
};

}

class Connector_TCP final : public Implementation::IConnector
                          , public Implementation::IConnector_TCP {
public:
  ThreadSafeHandler< shared_ptr < tcp::socket > > m_tcp_connection_handler;

  inline Connector_TCP( shared_ptr< Processor::Service > _service
                      , Handler< boost::system::error_code const& > _error_handler
                      , Handler< shared_ptr < tcp::socket > > _connection_handler )
      : IConnector( _service, _error_handler )
      , IConnector_TCP( _service ) {
  }

  inline ~Connector_TCP(void) {
  }

  inline boost::system::error_code Bind( tcp::endpoint const& _local_tcp ) {
    return IConnector_TCP::Bind( _local_tcp );
  }

  inline void Connect( tcp::endpoint const& _remote_tcp ) {
    IConnector_TCP::Connect( _remote_tcp );
  }

private:
  inline void Handle_TCP(void) override {
    auto connection_handler = m_tcp_connection_handler.load();
    if ( connection_handler ) {
      connection_handler->Handle( m_tcp_connector );
    }
  }

  inline void Handle_TCP_Error( boost::system::error_code const& _error ) override {
    auto error_handler = m_error_handler.load();
    if ( error_handler ) {
      error_handler->Handle( _error );
    }
  }
};

class Connector_UDP final : public Implementation::IConnector 
                          , public Implementation::IConnector_UDP {
public:
  ThreadSafeHandler< shared_ptr < udp::socket > > m_udp_connection_handler;

  inline Connector_UDP( shared_ptr< Processor::Service > _service
                      , Handler< boost::system::error_code const& > _error_handler
                      , Handler< shared_ptr < tcp::socket > > _connection_handler)
    : IConnector( _service, _error_handler )
    , IConnector_UDP( _service) {
  }

  inline ~Connector_UDP(void) {
  }

  inline boost::system::error_code Bind( udp::endpoint const& _local_udp ) {
    return IConnector_UDP::Bind( _local_udp );
  }

  inline void Connect( udp::endpoint const& _remote_udp ) {
    IConnector_UDP::Connect( _remote_udp );
  }

private:
  inline void Handle_UDP(void) override {
    auto connection_handler = m_udp_connection_handler.load();
    if ( connection_handler ) {
      connection_handler->Handle( m_udp_connector );
    }
  }

  inline void Handle_UDP_Error( boost::system::error_code const& _error ) override {
    auto error_handler = m_error_handler.load();
    if (error_handler) {
      error_handler->Handle(_error);
    }
  }
};

class Connector_Both final : public Implementation::IConnector 
                           , public Implementation::IConnector_TCP
                           , public Implementation::IConnector_UDP {
public:
  ThreadSafeHandler< shared_ptr< tcp::socket >
                   , shared_ptr< udp::socket > > m_connection_handler;

  inline Connector_Both( shared_ptr< Processor::Service > _service
                       , Handler< boost::system::error_code const& > _error_handler
                       , Handler< shared_ptr< tcp::socket >
                                , shared_ptr< udp::socket > > _connection_handler)
    : IConnector( _service, _error_handler )
    , IConnector_TCP( _service )
    , IConnector_UDP( _service ) {
  }

  inline ~Connector_Both(void) {
  }

  inline boost::system::error_code Bind( tcp::endpoint const& _local_tcp, udp::endpoint const& _local_udp) {
    boost::system::error_code error = IConnector_TCP::Bind( _local_tcp );
    if ( error ) return error;
    return IConnector_UDP::Bind( _local_udp );
  }

  inline void Connect( tcp::endpoint const& _remote_tcp, udp::endpoint const& _remote_udp) {
    IConnector_TCP::Connect( _remote_tcp );
    IConnector_UDP::Connect( _remote_udp );
  }

private:
  inline void Handle_UDP(void) override {
    auto connection_handler = m_udp_connection_handler.load();
    if (connection_handler) {
      connection_handler->Handle(m_udp_connector);
    }
  }

  inline void Handle_UDP_Error(boost::system::error_code const& _error) override {
    auto error_handler = m_error_handler.load();
    if (error_handler) {
      error_handler->Handle(_error);
    }
  };



class Connector : public NonCopyable {
public:
  ThreadSafeHandler< boost::system::error_code const& > m_error_handler;
  ThreadSafeHandler< shared_ptr< tcp::socket >, shared_ptr< udp::socket > > m_connection_handler;

  inline Connector( Processor::Service * _service
                  , Handler< boost::system::error_code const& > _error_handler = nullptr
                  , Handler< shared_ptr< tcp::socket >
                           , shared_ptr< udp::socket > > _connection_handler = nullptr )
      : m_error_handler( _error_handler )
      , m_connection_handler( _connection_handler ) 
      , tcp_connector( new tcp::socket( _service->service() ) )
      , udp_connector( new udp::socket( _service->service() ) ) {
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
  shared_ptr< tcp::socket > tcp_connector = nullptr;
  shared_ptr< udp::socket > udp_connector = nullptr;

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