#ifndef ENGINE_NETWORK_CONNECTION_H
#define ENGINE_NETWORK_CONNECTION_H

#include "BOOST/bind.hpp"

#include "Engine/Platform.h"
#include "Engine/Network/IHandler.hpp"
// #include "Engine/Processor/Service.h"

// TODO Modify char * to void * and get an Allocator?

namespace Engine { namespace Network {

// TODO not nice!!
enum class Protocol {
  TCP,
  UDP
};

class IPacket {
public:
  virtual char * const data(void) = 0;
  virtual uint32 const size(void) = 0;
};

namespace Implementation {

class IConnection : public NonCopyable {
protected:
  virtual void Start(void) = 0;

  virtual void Dispose(void) = 0;
};

template< typename Derived >
class IDisconnector : public NonCopyable {
public:
  ThreadSafeHandler< shared_ptr < Derived > > m_disconnection_handler;

protected:
  inline IDisconnector( Handler< shared_ptr< Derived > > _disconnection_handler )
      : m_disconnection_handler( _disconnection_handler ) {
  }

  inline ~IDisconnector(void) {
  }

  virtual void Disconnect(void) = 0;
};

class IConnection_TCP : public IConnection {
public:
  struct Configuration {
    const uint32 packet_max_size;
  } const configuration;

public:
  inline IConnection_TCP( Configuration const& _configuration
                        , shared_ptr< tcp::socket > _tcp_socket )
      : configuration( _configuration )
      , m_tcp_socket( _tcp_socket ) {
    assert( _tcp_socket && "Invalid socket @ Connection_TCP::ctor" );
  }

  inline virtual ~IConnection_TCP(void) {
  }

  inline virtual void TCP_Send( shared_ptr< IPacket > _packet ) {
    assert( _packet->size() < configuration.packet_max_size
            && "Too long _packet->size() @ Implementation::Connection_TCP::TCP_Send" );
    m_tcp_socket->async_send( boost::asio::buffer( _packet->data(), _packet->size() )
                            , boost::bind( &IConnection_TCP::Handle_TCP_Send
                                         , this
                                         , boost::asio::placeholders::error
                                         , boost::asio::placeholders::bytes_transferred ) );
  }

protected:
  inline void Start(void) override {
    char * tcp_data = new char[configuration.packet_max_size];

    TCP_Receive(tcp_data);
  }

  inline virtual void Dispose(void) override {
    m_tcp_socket->close();
  }

  inline virtual void Handle_TCP( char * const _data, size_t _received ) = 0;

private:
  shared_ptr < tcp::socket > m_tcp_socket = nullptr;

  inline virtual void Handle_TCP_Send( boost::system::error_code const& _error
                                     , size_t _sent ) {
    if (_error) {
      // TODO what's this?!
      if (_error.value() == 995) return;
      else Dispose();
    }
  }

  inline virtual void TCP_Receive( char * const _data ) {
    if (m_tcp_socket && m_tcp_socket->is_open()) {
      m_tcp_socket->async_receive( boost::asio::buffer( _data, configuration.packet_max_size )
                                 , boost::bind( &IConnection_TCP::Handle_TCP_Receive
                                              , this
                                              , boost::asio::placeholders::error
                                              , _data
                                              , boost::asio::placeholders::bytes_transferred ) );
    }
  }


  virtual void Handle_TCP_Receive( boost::system::error_code const& _error, char * const _data
                                  , size_t _received ) {
    if (!_error) {
      Handle_TCP( _data, _received);
      TCP_Receive( _data );
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
};

class IConnection_UDP : public IConnection {
public:
  struct Configuration {
    const uint32 packet_max_size;
  } const configuration;

public:
  inline IConnection_UDP( Configuration const& _configuration
                        , shared_ptr < udp::socket > _udp_socket )
      : configuration( _configuration )
      , m_udp_socket( _udp_socket ) {
    assert( _udp_socket && "Invalid socket @ Connection_UDP::ctor");
  }

  inline virtual ~IConnection_UDP(void) {
  }

  virtual void UDP_Send(shared_ptr < IPacket > _packet) {
    assert( _packet->size() < configuration.packet_max_size
           && "Invalid _packet size @ Implementation::Connection_UDP::UDP_Send" );
    m_udp_socket->async_send( boost::asio::buffer( _packet->data(), _packet->size() )
                            , boost::bind( &IConnection_UDP::Handle_UDP_Send
                                         , this
                                         , boost::asio::placeholders::error
                                         , boost::asio::placeholders::bytes_transferred ) );
  }

protected:
  inline void Start(void) override {
    char * udp_data = new char[configuration.packet_max_size];

    UDP_Receive(udp_data);
  }
  
  inline virtual void Dispose(void) override {
    m_udp_socket->close();
  }

  virtual void Handle_UDP( char * const _data, size_t _received ) = 0;

private:
  shared_ptr < udp::socket > m_udp_socket = nullptr;

  virtual void Handle_UDP_Send( boost::system::error_code const& _error, size_t _sent ) {
    if (_error) {
      // TODO what's this?!
      if (_error.value() == 995) return;
      else Dispose();
    }
  }

  virtual void UDP_Receive( char * const _data ) {
    if ( m_udp_socket && m_udp_socket->is_open() ) {
      m_udp_socket->async_receive( boost::asio::buffer( _data, configuration.packet_max_size )
                                 , boost::bind( &IConnection_UDP::Handle_UDP_Receive
                                              , this
                                              , boost::asio::placeholders::error
                                              , _data
                                              , boost::asio::placeholders::bytes_transferred ) );
    }
  }

  virtual void Handle_UDP_Receive( boost::system::error_code const& _error, char * const _data
                                 , size_t _received ) {
    if (!_error) {
      Handle_UDP( _data, _received );
      UDP_Receive(_data);
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
};

}

class Connection_TCP final : public enable_shared_from_this< Connection_TCP > 
                           , public Implementation::IConnection_TCP
                           , public Implementation::IDisconnector< Connection_TCP > {
public:
  ThreadSafeHandler< char * const, size_t > m_tcp_handler;

  inline Connection_TCP( Configuration const& _configuration
                       , Handler< shared_ptr< Connection_TCP > > _disconnection_handler
                       , Handler< char * const, size_t > _tcp_handler
                       , shared_ptr< tcp::socket > _tcp_socket)
      : IConnection_TCP( _configuration, _tcp_socket )
      , IDisconnector( _disconnection_handler )
      , m_tcp_handler( _tcp_handler ) {
  }

  inline ~Connection_TCP( void ) {
  }

  inline void Start(void) override {
    IConnection_TCP::Start();
  }

  inline void Dispose(void) override {
    Disconnect();
    IConnection_TCP::Dispose();
  }

protected:
  inline void Handle_TCP( char * const _data, size_t _received) override {
    auto tcp_handler = m_tcp_handler.load();
    if ( tcp_handler ) {
      tcp_handler->Handle( _data, _received );
    }
  }

  inline void Disconnect(void) override {
    auto disconnection_handler = m_disconnection_handler.load();
    if ( disconnection_handler ) {
      disconnection_handler->Handle( shared_from_this() );
    }
  }
};

class Connection_UDP final : public enable_shared_from_this< Connection_UDP >
                           , public Implementation::IConnection_UDP
                           , public Implementation::IDisconnector< Connection_UDP > {
public:
  ThreadSafeHandler< char * const, size_t > m_udp_handler;

  inline Connection_UDP( Configuration const& _configuration
                       , Handler< shared_ptr< Connection_UDP > > _disconnection_handler
                       , Handler< char * const, size_t >  _udp_handler
                       , shared_ptr< udp::socket > _udp_socket )
      : IConnection_UDP( _configuration, _udp_socket )
      , IDisconnector( _disconnection_handler )
      , m_udp_handler( _udp_handler ) {
  }
  
  inline ~Connection_UDP() {
  }

  inline void Start(void) override {
    IConnection_UDP::Start();
  }

  inline void Dispose(void) override {
    Disconnect();
    IConnection_UDP::Dispose();
  }

protected:
  void Handle_UDP( char * const _data, size_t _received) override {
    auto udp_handler = m_udp_handler.load();
    if ( udp_handler ) {
      udp_handler->Handle( _data, _received );
    }
  }

  void Disconnect(void) override {
    auto disconnection_handler = m_disconnection_handler.load();
    if (disconnection_handler) {
      disconnection_handler->Handle( shared_from_this() );
    }
  }
};

class Connection_Both final : public enable_shared_from_this< Connection_Both >
                            , public Implementation::IConnection_TCP
                            , public Implementation::IConnection_UDP
                            , public Implementation::IDisconnector< Connection_Both > {
public:
  ThreadSafeHandler < char * const, size_t, Protocol > m_tcp_handler;
  ThreadSafeHandler < char * const, size_t, Protocol > m_udp_handler;

  inline Connection_Both( IConnection_TCP::Configuration const& _tcp_configuration
                        , IConnection_UDP::Configuration const& _udp_configuration
                        , Handler< shared_ptr < Connection_Both > > _disconnection_handler
                        , Handler< char * const, size_t, Protocol > _tcp_handler
                        , Handler< char * const, size_t, Protocol > _udp_handler
                        , shared_ptr< tcp::socket > _tcp_socket
                        , shared_ptr< udp::socket > _udp_socket )
      : IConnection_TCP( _tcp_configuration, _tcp_socket )
      , IConnection_UDP( _udp_configuration, _udp_socket )
      , IDisconnector( _disconnection_handler )
      , m_tcp_handler( _tcp_handler )
      , m_udp_handler( _udp_handler ) {
  }

  inline virtual ~Connection_Both(void) {
  };

  void Start(void) override {
    IConnection_TCP::Start();
    IConnection_UDP::Start();
  }

  void Dispose(void) {
    Disconnect();
    IConnection_TCP::Dispose();
    IConnection_UDP::Dispose();
  }

protected:
  inline void Handle_TCP( char * const _data, size_t _received ) override {
    auto tcp_handler = m_tcp_handler.load();
    if ( tcp_handler ) {
      tcp_handler->Handle( _data, _received, Protocol::TCP );
    }
  }

  inline void Handle_UDP( char * const _data, size_t _received ) override {
    auto udp_handler = m_udp_handler.load();
    if ( udp_handler ) {
      udp_handler->Handle(_data, _received, Protocol::UDP);
    }
  }

  inline void Disconnect(void) override {
    auto disconnection_handler = m_disconnection_handler.load();
    if (disconnection_handler) {
      disconnection_handler->Handle(shared_from_this());
    }
  }
};

} }

#endif