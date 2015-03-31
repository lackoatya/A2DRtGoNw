#ifndef P3A_GAME_STAGE_H_
#define P3A_GAME_STAGE_H_

#include "Engine/Physics/BSP_Tree.hpp"
#include "P3A/Game/Object.h"

namespace P3A {
namespace Game {
class Stage {
  public:
    Stage(void);
    inline Stage(Stage && _other) = delete;
    inline Stage(Stage const& _other) = delete;
    inline Stage & operator=(Stage && _other) = delete;
    inline Stage & operator=(Stage const& _other) = delete;
    inline virtual ~Stage(void) = default;

  private:
    Engine::Physics::BSP_Tree< Object * > * collision_tree_ = nullptr;
};
}
}

#endif