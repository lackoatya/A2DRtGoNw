#ifndef ENGINE_PROCESSOR_IUPDATABLE_RUNNER_HPP_
#define ENGINE_PROCESSOR_IUPDATABLE_RUNNER_HPP_

#include "Engine/Platform.h"
#include "Engine/Updater/IUpdatable.hpp"
#include "Engine/Processor/IRunnable.hpp"

namespace Engine {
namespace Processor {
template < class Result >
class IUpdatableRunner : public NonCopyable
                       , public IRunnable < Result > {
public:
  virtual Result Run(void) = 0;

protected:
  Updater::IUpdatable < Result > * m_updatable = nullptr;

  inline IUpdatableRunner(Updater::IUpdatable < Result > * _updatable)
      : m_updatable(_updatable) {
    assert(m_updatable);
  }

  inline virtual ~IUpdatableRunner(void) {
  }
};
}
}

#endif