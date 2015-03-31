#ifndef ENGINE_PROCESSOR_THREADED_SERVICE_H_
#define ENGINE_PROCESSOR_THREADED_SERVICE_H_

#include "BOOST/thread.hpp"

#include "Engine/Processor/Service.hpp"

namespace Engine {
namespace Processor {
template<class Updatable, class Processable>
class ThreadedService {
  public:
    inline ThreadedService(Updatable * _instance) : service_(_instance), thread_() { }
    inline virtual ~ThreadedService(void) = default;

    inline void Run(void) {
      thread_ = boost::thread(boost::bind(&Service<Updatable, Processable>::Run, &service_));
    }
    inline virtual void Stop(void) { service_.Stop(); thread_.interrupt(); }
    inline virtual void Join(void) { thread_.join(); }

  protected:
    Service<Updatable, Processable> service_;
    boost::thread thread_;
};
}
}

#endif