#ifndef ENGINE_PROCESSOR_THREADED_SERVICE_H_
#define ENGINE_PROCESSOR_THREADED_SERVICE_H_

#include "BOOST/bind.hpp"
#include "BOOST/thread.hpp"

#include "Engine/Processor/Service.h"

namespace Engine {
namespace Processor {
class ThreadedService : public Service {
public:
  inline ThreadedService(void)
      : Service()
      , m_thread() {
  }

  inline virtual ~ThreadedService(void) {
  }

  inline virtual void Run(void) override {
    m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_service));
  }
  
  inline virtual void Stop(void) override {
    m_service.stop();
    m_thread.interrupt();
  }
  
  inline virtual void Join(void) {
    m_thread.join();
  }

protected:
  boost::thread m_thread;
};
}
}

#endif