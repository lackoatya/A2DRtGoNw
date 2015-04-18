#ifndef ENGINE_PHYSICS_BODY_HPP_
#define ENGINE_PHYSICS_BODY_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Physics {
template <class Shape>
class Body : public Shape {
  public:
    inline Body(Shape const& _shape) : Shape(_shape) { }
    inline virtual ~Body(void) = default;

    inline Vector2 velocity(void) const { return velocity_; }
    inline void set_velocity(Vector2 const& _velocity) { velocity_ = _velocity; }
    inline Vector2 force(void) const { return force_; }
    inline void set_force(Vector2 const& _force) { force_ = _force; }

    inline real32 inertia(void) const { return inertia_; }
    inline void set_inertia(real32 const& _inertia) { inertia_ = _inertia; }
    inline real32 inverse_inertia(void) const { return inverse_intertia_; }
    inline real32 mass(void) const { return mass_; }
    inline void set_mass(real32 const& _mass) { mass_ = _mass; }
    inline real32 inverse_mass(void) const { return inverse_mass_; }

  private:
    Vector2 velocity_, force_;

    real32 inertia_ = 0.f;
    real32 inverse_inertia_ = 0.f;
    real32 mass_ = 0.f;
    real32 inverse_mass_ = 0.f;
};
}
}

#endif