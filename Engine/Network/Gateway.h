#ifndef ENGINE_NETWORK_GATEWAY_H_
#define ENGINE_NETWORK_GATEWAY_H_

#include "BOOST/asio.hpp"
#include "BOOST/bind.hpp"

#include "Engine/Container/Pool.h"
#include "Engine/Processor/Service.h"

namespace Engine {
namespace Network {
class Gateway : public NonCopyable {
  public:
    class ConnectionHandlerInterface {
      public:
        virtual void Handle_Connection(shared_ptr < tcp_socket > _socket) = 0;
    };

  public:
    struct Configuration {
      uint32 connections_max;
      uint32 port_offset;

      inline Configuration(uint32 _connections_max, uint32 _port_offset)
          : connections_max(_connections_max)
          , port_offset(_port_offset) {
      }
    } const configuration;

    atomic < shared_ptr < ConnectionHandlerInterface > > m_handler;

    inline Gateway( Configuration const& _configuration
                  , Processor::Service * _service )
        : configuration(_configuration)
        , m_service(_service)
        , m_gateway(_service->service())
        , m_port_offsets(configuration.connections_max) {
      assert( _service );
      Listen();
    }

    inline virtual ~Gateway(void) {
    }

    inline boost::system::error_code Bind( boost::asio::ip::tcp::endpoint const& _endpoint ) {
      boost::system::error_code error;

      error = m_gateway.open(_endpoint.protocol(), error);
      if (error) return error;

      error = m_gateway.bind(_endpoint, error);
      return error;
    }

    inline void Listen(void) {
      shared_ptr < tcp_socket > accepted(new tcp_socket(m_service->service()));
      if (m_gateway.is_open()) m_gateway.async_accept( *accepted
                                                     , boost::bind( &Gateway::Handle_Accept
                                                                  , this
                                                                  , accepted
                                                                  , boost::asio::placeholders::error ) );
    }

    // TODO This is not the perfect place for this!
    inline void ReturnPort(uint32 const& _port) {
      m_port_offsets.push(_port - configuration.port_offset);
    }

    inline void Shutdown(void) {
      Dispose();
    }

  protected:
    inline virtual void Dispose(void) {
      m_gateway.cancel();
      m_gateway.close();

      // TODO ?!?
      delete this;
    }

  private:
    Processor::Service * m_service = nullptr;

    boost::asio::ip::tcp::acceptor m_gateway;
    Engine::Container::OffsetPool m_port_offsets;

    inline void Handle_Accept( shared_ptr < tcp_socket > _socket
                             , boost::system::error_code const& _error) {
      if ( !_error ) {
        shared_ptr < ConnectionHandlerInterface > handler = m_handler.load();
        if (handler) {
          handler->Handle_Connection( _socket );
        }
      }
      
      Listen();
    }
};
}
}
#endif