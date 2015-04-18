#ifndef P3A_GAME_HERO_STATE_H_
#define P3A_GAME_HERO_STATE_H_

#define MOTIONS_MAX 8

#include "Engine/Types.h"
#include "Engine/Container/Buffer.hpp"
#include "Engine/Physics/AABB.h"
#include "Engine/Physics/Body.hpp"
#include "Engine/Graphics/Motion.h"

namespace P3A {
namespace Game {
class Hero;

struct HeroState {
  public:
    Hero * hero = nullptr;

    Engine::Physics::Body<Engine::Physics::AABB> body;

    uint32 mesh = 0, appearance = 0;

    uint32 motions_count = 0;
    Engine::Graphics::Motion motions[MOTIONS_MAX];

    inline HeroState(void) : body(Engine::Physics::AABB(Vector2(0.f, 0.f), 64., 64.)) { }
    inline HeroState(Vector2 const& _location, Vector2 const& _velocity)
      : body(Engine::Physics::AABB(_location, 64., 64.)) {
      body.set_velocity(_velocity);
    }
    inline HeroState & operator=(HeroState const& _other) {
      body = _other.body;

      mesh = _other.mesh;
      appearance = _other.appearance;

      motions_count = _other.motions_count;
      memcpy(motions, &_other.motions, sizeof(motions));

      return *this;
    }
    inline virtual ~HeroState(void) { }

    inline void copy(HeroState const& _other) {
      hero = _other.hero;
      mesh = _other.mesh;
      appearance = _other.appearance;
    }
};

struct HeroInput {

};

class Hero : public NonCopyable {
  public:
    const uint32 id;
    Engine::Container::Buffer < HeroInput > input_buffer;

    // TODO get size from configuration.
    inline Hero(uint32 _id) : id(_id), input_buffer(Engine::Container::Buffer < HeroInput >(8)) { }
    inline virtual ~Hero(void) { }


  private:
};
}
}
#endif