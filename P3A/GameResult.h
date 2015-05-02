#ifndef P3A_GAME_RESULT_H_
#define P3A_GAME_RESULT_H_

#include "Engine/Processor/IResult.hpp"

namespace P3A {
enum class GameState {
  CONTINUE = 0,

  ENDED,

  Count
};

class GameResult : public Engine::Processor::IResult < GameState > {
public:
  inline GameResult(void)
      : Engine::Processor::IResult < GameState >(GameState::CONTINUE) {
  }
  inline GameResult(GameState const& _state)
      : Engine::Processor::IResult < GameState >(_state) {
  }

  bool IsValid(void) const { return result() != GameState::CONTINUE; }
  // GameState NotValid(void) const { return GameState::CONTINUE; }
};
}

#endif