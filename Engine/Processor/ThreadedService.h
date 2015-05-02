#ifndef ENGINE_PROCESSOR_THREADED_SERVICE_H_
#define ENGINE_PROCESSOR_THREADED_SERVICE_H_

#include "BOOST/thread.hpp"

#include "Engine/Processor/Service.h"

namespace Engine {
namespace Processor {
class ThreadedService : public Service {
  public:
    inline ThreadedService() : Service(), m_thread() { }
    inline virtual ~ThreadedService(void) { }

    inline void Run(void) {
      m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &service_));
    }
    inline virtual void Stop(void) { service_.stop(); m_thread.interrupt(); }
    inline virtual void Join(void) { m_thread.join(); }

  protected:
    boost::thread m_thread;
};
}
}

#endif