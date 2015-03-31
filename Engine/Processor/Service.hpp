#ifndef ENGINE_PROCESSOR_SERVICE_H_
#define ENGINE_PROCESSOR_SERVICE_H_

#include "BOOST/bind.hpp"
#include "BOOST/asio/strand.hpp"
#include "BOOST/asio/io_service.hpp"

#include "Engine/Processor/RunnableInterface.hpp"

namespace Engine {
namespace Processor {
template<class Updatable, class Processable>
class Service : public RunnableInterface<Updatable, Processable, void> {
  public:
    inline Service(Updatable * _instance)
        : RunnableInterface<Updatable, Processable, void>(_instance),
          service_(),
          work_(service_),
          strand_(service_) { }
    inline virtual ~Service(void) = default;

    // inline virtual void Start(void) { service_.run(); }
    inline void Run(void) {
      service_.post(strand_.wrap(boost::bind(&Service::Work, this)));
      service_.run();
    }
    inline virtual void Stop(void) { service_.stop(); }

    inline boost::asio::io_service & service(void) { return service_; }
    inline boost::asio::strand & strand(void) { return strand_; };

  protected:
    boost::asio::io_service service_;
    boost::asio::io_service::work work_;
    boost::asio::strand strand_;

    inline void Work(void) {
      instance_->Update();
      service_.post(strand_.wrap(boost::bind(&Service::Work, this)));
    }
};
}
}

#endif