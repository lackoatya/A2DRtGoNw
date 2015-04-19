#ifndef ENGINE_NETWORK_GATEWAY_INTERFACE_H_
#define ENGINE_NETWORK_GATEWAY_INTERFACE_H_

#include "BOOST/asio.hpp"
#include "BOOST/bind.hpp"

#include "Engine/Container/PoolInterface.hpp"
#include "Engine/Processor/Service.h"

namespace Engine {
namespace Network {
struct GatewayConfiguration {
  const uint32 connections_max;
  const uint32 port_offset;
};

class GatewayInterface : public NonCopyable {
  public:
    inline void ReturnPort(uint32 const& _port) {
      port_offsets_.push(_port - configuration.port_offset);
    }

  protected:
    boost::asio::ip::tcp::socket accepted_;

    inline GatewayInterface( Processor::Service * _service
                           , boost::asio::ip::tcp::endpoint const& _endpoint )
      : service_(_service)
      , accepted_(_service->service())
      , gateway_(_service->service(), _endpoint) { assert(_service); Listen(); }
    inline virtual ~GatewayInterface(void) = default;

    virtual void Handle_Connection(void) = 0;

    inline virtual void Dispose(void) {
      service_->Stop();

      gateway_.cancel();
      gateway_.close();

      // TODO?!?
      delete this;
    }

  private:
    template < uint32 size >
    class PortOffsetPool : public Container::PoolInterface < uint32, size > {
      public:
      inline PortOffsetPool(void) : Container::PoolInterface < uint32, size >() {
        for (uint32 current = 0; current < size; ++current)
          data_[current] = current;
      }
      inline ~PortOffsetPool(void) = default;
    };

  private:
    const GatewayConfiguration configuration;

    Processor::Service * service_ = nullptr;

    // TODO use some kind of configuration!
    PortOffsetPool < 5 > port_offsets_;
    boost::asio::ip::tcp::acceptor gateway_;

    inline void Listen(void) {
      if (gateway_.is_open) gateway_.async_accept(accepted_, boost::bind(&Handle_Accept
                                                                       , this
                                                                       , boost::asio::placeholders::error));
    }
    inline void Handle_Accept(boost::system::error_code const& _error) {
      if (!_error) Handle_Connection();
      Listen();
    }
};
}
}
#endif