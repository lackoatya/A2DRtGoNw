#ifndef ENGINE_PROCESSOR_IRUNNABLE_HPP_
#define ENGINE_PROCESSOR_IRUNNABLE_HPP_

#include "Engine/Types.h"
#include "Engine/Updater/IUpdatable.hpp"

namespace Engine {
namespace Processor {
template < class Result >
class IRunnable : public NonCopyable {
public:
  virtual Result Run(void) = 0;

protected:
  Updater::IUpdatable < Result > * m_updatable = nullptr;

  inline IRunnable(Updater::IUpdatable < Result > * _updatable)
      : m_updatable(_updatable) {
    assert(m_updatable);
  }
  inline virtual ~IRunnable(void) { }
};
}
}

#endif