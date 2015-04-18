/*#ifndef P3A_GAME_SNAPSHOT_H_
#define P3A_GAME_SNAPSHOT_H_

#include "Engine/Types.h"
#include "P3A/Game/Hero.h"

namespace P3A {
namespace Game {
struct Snapshot {
  public:
    uint32 hero_state_count = 0;
    HeroState hero_states[8];

    inline Snapshot(void) { }
    inline virtual ~Snapshot(void) = default;

  private:
};
}
}

#endif*/