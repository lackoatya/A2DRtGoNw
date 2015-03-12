#ifndef P3A_CORE_STATE_H_
#define P3A_CORE_STATE_H_

#include "Engine/Core/ProcessableResultInterface.h"

namespace P3A {
namespace Core {
enum class CoreState {
  CONTINUE = 0,

  MENU,
  LOCAL,
  LOBBY,
  EXIT,

  Count
};

class State : public Engine::Core::ProcessableResultInterface<CoreState> {
public:
  inline State(void) = delete;
  inline State(CoreState const& _result)
      : Engine::Core::ProcessableResultInterface<CoreState>(_result) { }
  inline State(State && _other)
      : Engine::Core::ProcessableResultInterface<CoreState>(_other) { }
  inline State(State const& _other)
      : Engine::Core::ProcessableResultInterface<CoreState>(_other) { }
  inline State & operator=(State && _other) {
    Engine::Core::ProcessableResultInterface<CoreState>::operator=(_other);
    return *this;
  }
  inline State & operator=(State const& _other) {
    Engine::Core::ProcessableResultInterface<CoreState>::operator=(_other);
    return *this;
  }
  inline ~State(void) = default;

  bool Valid(void) const { return result() != CoreState::CONTINUE; }
};
}
}

#endif