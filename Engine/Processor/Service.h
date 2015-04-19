#ifndef ENGINE_PROCESSOR_SERVICE_H_
#define ENGINE_PROCESSOR_SERVICE_H_

#include "BOOST/asio/io_service.hpp"

namespace Engine {
namespace Processor {
class Service {
  public:
    inline Service(void) : service_() { }
    inline virtual ~Service(void) = default;

    inline virtual void Run(void) { service_.run(); }
    inline virtual void Stop(void) { service_.stop(); }

    inline boost::asio::io_service & service(void) { return service_; }

  protected:
    boost::asio::io_service service_;
};
}
}

#endif