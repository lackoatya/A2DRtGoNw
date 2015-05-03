#ifndef LABYRINTH_GAME_RESULT_H_
#define LABYRINTH_GAME_RESULT_H_

#include "Engine/Processor/IResult.hpp"

namespace Labyrinth {
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
};
}

#endif