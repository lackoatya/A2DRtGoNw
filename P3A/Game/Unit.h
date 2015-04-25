#ifndef P3A_GAME_UNIT_H_
#define P3A_GAME_UNIT_H_

// TODO ..........
#define MOTIONS_MAX 8

#include "Engine/Types.h"
#include "Engine/Container/Buffer.hpp"
#include "Engine/Physics/AABB.h"
#include "Engine/Physics/Body.hpp"
#include "Engine/Graphics/Motion.h"

namespace P3A {
namespace Game {
struct UnitState {
  public:
    Engine::Physics::Body < Engine::Physics::AABB > body;

    uint32 mesh = 0, appearance = 0;

    real32 speed = 128.f;

    uint32 motions_count = 0;
    Engine::Graphics::Motion motions[MOTIONS_MAX];

    inline UnitState(void) : body(Engine::Physics::AABB(Vector2(0.f, 0.f), 64., 64.)) { }
    inline UnitState(Vector2 const& _location, Vector2 const& _velocity)
      : body(Engine::Physics::AABB(_location, 64., 64.)) {
      body.set_velocity(_velocity);
    }
    inline UnitState & operator=(UnitState const& _other) {
      body = _other.body;

      mesh = _other.mesh;
      appearance = _other.appearance;

      motions_count = _other.motions_count;
      memcpy(motions, &_other.motions, sizeof(motions));

      return *this;
    }
    inline virtual ~UnitState(void) { }

    inline void copy(UnitState const& _other) {
      mesh = _other.mesh;
      appearance = _other.appearance;
    }
};

template < class Command >
class UnitController : public NonCopyable {
  public:
    struct Configuration {
      uint32 command_buffer_size;
    } const configuration;

    const uint32 id;
    Engine::Container::Buffer < Command > m_command_buffer;

    // TODO get size from configuration.
    inline UnitController(Configuration _configuration, uint32 _id)
        : configuration(_configuration)
        , id(_id)
        , command_buffer(Engine::Container::Buffer < Command >(configuration.command_buffer_size)) {
    }
    inline virtual ~UnitController(void) { }
};
}
}
#endif