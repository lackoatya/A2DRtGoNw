#ifndef ENGINE_UPDATER_DETERMINISTIC_HPP_
#define ENGINE_UPDATER_DETERMINISTIC_HPP_

#include "Engine/Types.h"
#include "Engine/Updater/ITimeUpdatable.hpp"

namespace Engine { 
namespace Updater {
template < class Result >
class IDeterministicProcess {
public:
  const real32 m_interval;

  virtual Result Process(void) = 0;

protected:
  inline IDeterministicProcess(real32 const& _interval) : m_interval(_interval) { }
  inline virtual ~IDeterministicProcess(void) { }
};

template < class Result >
class Deterministic : public ITimeUpdatable < Result > {
public:
  inline Deterministic(IDeterministicProcess < Result > * _process)
      : ITimeUpdatable < Result > ()
      , m_process(_process) {
    assert(_process);
  }
  inline virtual ~Deterministic(void) { }

  Result Update(void) {
    UpdateTime();

    Result result;
    while (m_process->m_interval <= m_elapsed_time) {
      result = m_process->Process();
      m_elapsed_time -= m_process->m_interval;
    }
    return result;
  }

private:
  IDeterministicProcess < Result > * m_process = nullptr;
};
}
}

#endif