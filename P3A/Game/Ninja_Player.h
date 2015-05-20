#ifndef P3A_GAME_NINJA_PLAYER_H_
#define P3A_GAME_NINJA_PLAYER_H_

#include "Engine/Platform.h"

#include "P3A/Game/Ninja.h"

namespace P3A {
namespace Game {
class Ninja_Player : public Ninja {
public:
  inline Ninja_Player( uint32 _command_buffer_size
                     , uint32 _id)
      : Engine::Game::IController < NinjaCommand >(_command_buffer_size, _id) { }
  inline virtual ~Ninja_Player(void) { }

private:
};
}
}

#endif