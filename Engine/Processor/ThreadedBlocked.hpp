#ifndef ENGINE_PROCESSOR_THREADED_BLOCKED_HPP_
#define ENGINE_PROCESSOR_THREADED_BLOCKED_HPP_

#include "BOOST/thread.hpp"

#include "Engine/Processor/Blocked.hpp"

namespace Engine {
namespace Processor {
template<class Updatable, class Result>
class ThreadedBlocked {
  public:
    inline ThreadedBlocked(Updatable * _instance)
        : blocked_(_instance),
          thread_() {}
    inline virtual ~ThreadedBlocked(void) = default;

    inline void Run(void) {
      thread_ = boost::thread(boost::bind(&Blocked < Updatable, Result >::Run, &blocked_));
    }
    inline virtual void Stop(void) { thread_.interrupt(); }
    inline virtual void Join(void) { thread_.join(); }

  private:
    Blocked < Updatable, Result > blocked_;
    boost::thread thread_;
};
}
}

#endif