#ifndef P3A_HOST_HOST_SNAPSHOT_H_
#define P3A_HOST_HOST_SNAPSHOT_H_

#include "Engine/Types.h"
#include "P3A/Game/Ninja.h"
#include "P3A/Game/Missile.h"

namespace P3A {
namespace Host {
struct HostSnapshot {
  public:
    struct Configuration {
      public:
      uint32 players_count;
      uint32 agents_max;
      uint32 missiles_max;

      inline Configuration(uint32 const& _players_count, uint32 const& _agents_max)
          : players_count(_players_count)
          , agents_max(_agents_max)
          , missiles_max((players_count + agents_max) * 3) {
      }
    } const configuration;

    Game::Ninja_State * player_ninja_states = nullptr;

    uint32 agent_ninjas_count = 0;
    Game::Ninja_State * agent_ninja_states = nullptr;

    uint32 missiles_count = 0;
    Game::Missile_State * missile_states = nullptr;

    inline explicit HostSnapshot(Configuration const& _configuration)
        : configuration(_configuration)
        , player_ninja_states(new Game::Ninja_State[configuration.players_count])
        , agent_ninja_states(new Game::Ninja_State[configuration.agents_max])
        , missile_states(new Game::Missile_State[configuration.missiles_max]) {
    }

    inline virtual ~HostSnapshot(void) {
      delete[] player_ninja_states;
      delete[] agent_ninja_states;
      delete[] missile_states;
    }
};
}
}

#endif