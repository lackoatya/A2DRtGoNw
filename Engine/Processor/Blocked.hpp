#ifndef ENGINE_PROCESSOR_BLOCKED_HPP_
#define ENGINE_PROCESSOR_BLOCKED_HPP_

#include "BOOST/thread.hpp"

#include "Engine/Processor/IRunnable.hpp"

namespace Engine {
namespace Processor {
template < class Result >
class Blocked : public IRunnable < Result > {
public:
  inline Blocked(Updater::IUpdatable < Result > * _updatable)
      : IRunnable < Result > (_updatable) {
    assert(_updatable);
  }
  inline virtual ~Blocked(void) { }

  inline Result Run(void) {
    while (true) {
      Result result = m_updatable->Update();
      if (result.IsValid()) return result;

      boost::this_thread::sleep_for(boost::chrono::microseconds(1));
    }
  }
};
}
}

#endif