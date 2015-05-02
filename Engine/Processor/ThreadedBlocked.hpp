#ifndef ENGINE_PROCESSOR_THREADED_BLOCKED_HPP_
#define ENGINE_PROCESSOR_THREADED_BLOCKED_HPP_

#include "BOOST/thread.hpp"

#include "Engine/Updater/IUpdatable.hpp"
#include "Engine/Processor/Blocked.hpp"

namespace Engine {
namespace Processor {
template < class Result >
class ThreadedBlocked {
  public:
    inline ThreadedBlocked(Updater::IUpdatable < Result > * _instance)
        : m_blocked(_instance)
        , m_thread() {
    }
    inline virtual ~ThreadedBlocked(void) { }

    inline void Run(void) {
      m_thread = boost::thread(boost::bind(&Blocked < Result >::Run, &m_blocked));
    }
    inline virtual void Stop(void) { m_thread.interrupt(); }
    inline virtual void Join(void) { m_thread.join(); }

  private:
    Blocked < Result > m_blocked;
    boost::thread m_thread;
};
}
}

#endif