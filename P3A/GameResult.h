#ifndef P3A_GAME_RESULT_H_
#define P3A_GAME_RESULT_H_

#include "Engine/Processor/ResultInterface.hpp"

namespace P3A {
enum class GameState {
  CONTINUE = 0,

  ENDED,

  Count
};

class GameResult : public Engine::Processor::ResultInterface<GameState> {
public:
  inline GameResult(void)
    : Engine::Processor::ResultInterface<GameState>(GameState::CONTINUE) { }
  inline GameResult(GameState const& _result)
    : Engine::Processor::ResultInterface<GameState>(_result) { }
  inline GameResult(GameResult && _other)
    : Engine::Processor::ResultInterface<GameState>(_other) { }
  inline GameResult(GameResult const& _other)
    : Engine::Processor::ResultInterface<GameState>(_other) { }
  inline GameResult & operator=(GameResult && _other) {
    Engine::Processor::ResultInterface<GameState>::operator=(_other);
    return *this;
  }
  inline GameResult & operator=(GameResult const& _other) {
    Engine::Processor::ResultInterface<GameState>::operator=(_other);
    return *this;
  }
  inline ~GameResult(void) = default;

  bool IsValid(void) const { return result() != GameState::CONTINUE; }
  GameState NotValid(void) const { return GameState::CONTINUE; }
};
}

#endif