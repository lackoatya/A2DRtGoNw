#ifndef ENGINE_PROCESSOR_THREADED_SERVICE_H_
#define ENGINE_PROCESSOR_THREADED_SERVICE_H_

#include "BOOST/thread.hpp"

#include "Engine/Processor/Service.h"

namespace Engine {
namespace Processor {
class ThreadedService : public Service {
  public:
    inline ThreadedService() : Service(), thread_() { }
    inline virtual ~ThreadedService(void) = default;

    inline void Run(void) {
      thread_ = boost::thread(boost::bind(&boost::asio::io_service::run, &service_));
    }
    inline virtual void Stop(void) { service_.stop(); thread_.interrupt(); }
    inline virtual void Join(void) { thread_.join(); }

  protected:
    boost::thread thread_;
};
}
}

#endif