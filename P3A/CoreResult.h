#ifndef P3A_CORE_RESULT_H_
#define P3A_CORE_RESULT_H_

#include "Engine/Processor/IResult.hpp"

namespace P3A {
enum class CoreState {
  CONTINUE = 0,

  MENU,
  SOLE,
  HOST,
  CLIENT,
  OPTIONS,
  EXIT,

  Count
};

class CoreResult : public Engine::Processor::IResult < CoreState > {
  public:
    inline CoreResult(void)
        : Engine::Processor::IResult < CoreState >(CoreState::CONTINUE) {
    }
    inline CoreResult(CoreState const& _result)
        : Engine::Processor::IResult < CoreState > (_result) {
    }

    bool IsValid(void) const { return result() != CoreState::CONTINUE; }
    // CoreState NotValid(void) const { return CoreState::CONTINUE; }
};
}

#endif