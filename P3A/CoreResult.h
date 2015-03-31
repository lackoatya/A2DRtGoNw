#ifndef P3A_CORE_RESULT_H_
#define P3A_CORE_RESULT_H_

#include "Engine/Processor/ResultInterface.hpp"

namespace P3A {
enum class CoreState {
  CONTINUE = 0,

  MENU,
  SOLE,
  SERVER,
  CLIENT,
  OPTIONS,
  EXIT,

  Count
};

class CoreResult : public Engine::Processor::ResultInterface<CoreState> {
  public:
    inline CoreResult(void)
        : Engine::Processor::ResultInterface<CoreState>(CoreState::CONTINUE) { }
    inline CoreResult(CoreState const& _result)
        : Engine::Processor::ResultInterface<CoreState>(_result) { }
    inline CoreResult(CoreResult && _other)
        : Engine::Processor::ResultInterface<CoreState>(_other) { }
    inline CoreResult(CoreResult const& _other)
        : Engine::Processor::ResultInterface<CoreState>(_other) { }
    inline CoreResult & operator=(CoreResult && _other) {
      Engine::Processor::ResultInterface<CoreState>::operator=(_other);
      return *this;
    }
    inline CoreResult & operator=(CoreResult const& _other) {
      Engine::Processor::ResultInterface<CoreState>::operator=(_other);
      return *this;
    }
    inline ~CoreResult(void) = default;

    bool IsValid(void) const { return result() != CoreState::CONTINUE; }
    CoreState NotValid(void) const { return CoreState::CONTINUE; }
};
}

#endif