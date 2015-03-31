#ifndef ENGINE_PHYSICS_BODY_H_
#define ENGINE_PHYSICS_BODY_H_

#include "Engine/Types.h"

namespace Engine {
namespace Physics {
struct ShapeInterface;

struct Body {
  public:
    Vector2 position;
    Vector2 velocity;

    real32 angularVelocity;
    real32 torque;
    real32 orient; // radians

    Vector2 force;

    // Set by shape
    real32 I;  // moment of inertia
    real32 iI; // inverse inertia
    real32 m;  // mass
    real32 im; // inverse masee

    real32 staticFriction;
    real32 dynamicFriction;
    real32 restitution;

    ShapeInterface * shape;

    Body(ShapeInterface * _shape, uint32 const& _x, uint32 const& _y);
    inline Body(void) = delete;
    inline Body(Body && _other) = delete;
    inline Body(Body const& _other) = delete;
    inline Body & operator=(Body && _other) = delete;
    inline Body & operator=(Body const& _other) = delete;
    inline virtual ~Body(void) = default;

    inline void ApplyForce(Vector2 const& _f) { force += _f; }
    inline void ApplyImpulse(Vector2 const& _impulse, Vector2 const& _contact) {
      velocity += im * _impulse;
      angularVelocity += iI * Cross(_contact, _impulse);
    }

    inline void SetStatic(void) {
      I = 0.0f;
      iI = 0.0f;
      m = 0.0f;
      im = 0.0f;
    }

    void SetOrient(real32 const& _radians);
};
}
}

#endif