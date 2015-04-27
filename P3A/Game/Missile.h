#ifndef P3A_GAME_MISSILE_H_
#define P3A_GAME_MISSILE_H_

#include "Engine/Types.h"
#include "Engine/Physics/AABB.h"
#include "Engine/Physics/Body.hpp"

namespace P3A {
namespace Game {
struct Missile_State {
public:
  Engine::Physics::Body < Engine::Physics::AABB > m_body;

  uint32 m_appearance = 0;

  real32 m_speed = 128.f;

  inline Missile_State(void) : m_body(Engine::Physics::AABB(Vector2(0.f, 0.f), 64.f, 32.f)) { }
  inline Missile_State(Vector2 const& _location, Vector2 const& _velocity)
      : m_body(Engine::Physics::AABB(_location, 64.f, 32.f)) {
    m_body.set_velocity(_velocity);
  }
  inline Missile_State & operator=(Missile_State const& _other) {
    m_body = _other.m_body;

    m_appearance = _other.m_appearance;

    return *this;
  }
  inline virtual ~Missile_State(void) { }

  inline void copy(Missile_State const& _other) {
    m_appearance = _other.m_appearance;
  }
};
}
}

#endif