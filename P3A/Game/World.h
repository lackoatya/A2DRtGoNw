#ifndef P3A_GAME_WORLD_H_
#define P3A_GAME_WORLD_H_

#include "Engine/Core/ProcessableInterface.h"
#include "Engine/Physics/Reality.h"
#include "P3A/Core/State.h"

namespace P3A {
namespace Game {
class World : public Engine::Core::ProcessableInterface_Deterministic<P3A::Core::State>,
              public Engine::Physics::Reality {
  public:
    inline World(real32 const& _interval) : Engine::Physics::Reality(_interval) { }
    inline World(void) = delete;
    inline World(World && _other) = delete;
    inline World(World const& _other) = delete;
    inline World & operator=(World && _other) = delete;
    inline World & operator=(World const& _other) = delete;
    inline virtual ~World(void) = default;

    inline P3A::Core::State Process(void) {
      Engine::Physics::Reality::Process();
      return P3A::Core::CoreState::CONTINUE;
    }
};
}
}

#endif