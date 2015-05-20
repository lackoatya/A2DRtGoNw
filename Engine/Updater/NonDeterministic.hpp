#ifndef ENGINE_UPDATER_NONDETERMINISTIC_HPP_
#define ENGINE_UPDATER_NONDETERMINISTIC_HPP_

#include "Engine/Platform.h"
#include "Engine/Updater/ITimeUpdatable.hpp"

namespace Engine {
namespace Updater {
template < class Result >
class INonDeterministicProcess {
public:
  const real32 m_interval;

  virtual Result Process(real32 const& _elapsed_time) = 0;

protected:
  inline INonDeterministicProcess(real32 const& _interval) : m_interval(_interval) { }
  inline virtual ~INonDeterministicProcess(void) = default;
};

template < class Result >
class NonDeterministic : public ITimeUpdatable < Result > {
public:
  inline NonDeterministic(INonDeterministicProcess < Result > * _process)
      : ITimeUpdatable < Result > ()
      , m_process(_process) {
    assert(_process);
  }
  inline virtual ~NonDeterministic(void) { }

  Result Update(void) {
    UpdateTime();

    Result result;
    if (m_process->m_interval <= m_elapsed_time) {
      result = m_process->Process(m_elapsed_time);
      m_elapsed_time = 0.f;
    }
    return result;
  }

private:
  INonDeterministicProcess < Result > * m_process = nullptr;
};
}
}

#endif