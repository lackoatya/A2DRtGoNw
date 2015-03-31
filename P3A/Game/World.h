#ifndef P3A_GAME_WORLD_H_
#define P3A_GAME_WORLD_H_

#include "Engine/Processor/DeterministicUpdater.hpp"

#include "P3A/GameResult.h"
#include "P3A/Game/Stage.h"

namespace P3A {
namespace Game {
class World : public Engine::Processor::DeterministicProcessInterface<P3A::GameResult> {
  public:
    World(void);
    inline virtual ~World(void) = default;

    P3A::GameResult Process(void);

  private:
    P3A::Game::Stage * stage_ = nullptr;
};
}
}

#endif