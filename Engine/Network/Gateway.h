#ifndef ENGINE_NETWORK_GATEWAY_H_
#define ENGINE_NETWORK_GATEWAY_H_

#include "BOOST/asio.hpp"
#include "BOOST/bind.hpp"

#include "Engine/Container/Pool.h"
#include "Engine/Processor/Service.h"

namespace Engine {
namespace Network {
class ConnectionHandlerInterface {
  public:
    virtual void Handle_Connection(shared_ptr < tcp_socket > _socket) = 0;
};

class Gateway : public NonCopyable {
  public:
    struct Configuration {
      uint32 connections_max;
      uint32 port_offset;
    } const m_configuration;


    // TODO This is not the perfect place for this!
    inline void ReturnPort(uint32 const& _port) {
      m_port_offsets.push(_port - m_configuration.port_offset);
    }

    inline void Listen(void) {
      shared_ptr < tcp_socket > accepted(new tcp_socket(m_service->service()));
      if (m_gateway.is_open) m_gateway.async_accept(*accepted
                                                    , boost::bind(&Handle_Accept
                                                    , this
                                                    , accepted
                                                    , boost::asio::placeholders::error));
    }

    atomic < shared_ptr < ConnectionHandlerInterface > > m_handler;

  protected:
    inline Gateway( Configuration const& _configuration
                  , shared_ptr < ConnectionHandlerInterface > _handler
                  , shared_ptr < Processor::Service > _service
                  , boost::asio::ip::tcp::endpoint const& _endpoint )
        : m_configuration(_configuration)
        , m_handler(_handler)
        , m_service(_service)
        , m_gateway(_service->service(), _endpoint)
        , m_port_offsets(m_configuration.connections_max) {
      Listen();
    }
    inline virtual ~Gateway(void) {
    }

    inline virtual void Dispose(void) {
      m_gateway.cancel();
      m_gateway.close();

      // TODO ?!?
      delete this;
    }

  private:
    shared_ptr < Processor::Service > m_service;

    boost::asio::ip::tcp::acceptor m_gateway;
    Engine::Container::OffsetPool m_port_offsets;

    inline void Handle_Accept( shared_ptr < tcp_socket > _socket
                             , boost::system::error_code const& _error) {
      if ( !_error ) {
        shared_ptr < ConnectionHandlerInterface > handler = m_handler.load();
        if (handler) {
          handler->Handle_Connection( _socket );
        }

        Listen();
      }
    }
};
}
}
#endif