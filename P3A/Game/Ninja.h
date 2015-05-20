#ifndef P3A_GAME_NINJA_H_
#define P3A_GAME_NINJA_H_

#include "Engine/Platform.h"
#include "Engine/Container/Buffer.hpp"
#include "Engine/Physics/AABB.h"
#include "Engine/Physics/Body.hpp"
#include "Engine/Game/IController.hpp"

namespace P3A {
namespace Game {
enum class Ninja_Command {

};

struct Ninja_State {
public:
  Engine::Physics::Body < Engine::Physics::AABB > body;

  uint32 appearance = 0;

  real32 speed = 128.f;

  inline Ninja_State(void) : body(Engine::Physics::AABB(Vector2(0.f, 0.f), 64.f, 64.f)) { }
  inline Ninja_State(Vector2 const& _location, Vector2 const& _velocity)
      : body(Engine::Physics::AABB(_location, 64., 64.)) {
    body.set_velocity(_velocity);
  }
  inline Ninja_State & operator=(Ninja_State const& _other) {
    body = _other.body;

    appearance = _other.appearance;

    return *this;
  }
  inline virtual ~Ninja_State(void) { }

  inline void copy(Ninja_State const& _other) {
    appearance = _other.appearance;
  }
};

class Ninja : public Engine::Game::IController < Ninja_Command > {
public:
  uint32 last_processed_command = 0;

  inline Ninja(uint32 _command_buffer_size, uint32 _id)
      : Engine::Game::IController < Ninja_Command >( _command_buffer_size, _id ) { }
  inline virtual ~Ninja(void) { }
};
}
}
#endif