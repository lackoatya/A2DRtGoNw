#ifndef ENGINE_PHYSICS_CIRCLE_H_
#define ENGINE_PHYSICS_CIRCLE_H_

#include "Engine/Physics/AABB.h"
#include "Engine/Physics/ShapeInterface.h"

namespace Engine {
namespace Physics {
class Circle : public ShapeInterface {
  public:
    inline explicit Circle(Vector2 const& _position, real32 const& _radius)
        : ShapeInterface(_position),
          radius_(_radius) { }
    inline Circle(Circle && _other)
        : ShapeInterface(_other.position),
          radius_(_other.radius_) { }
    inline Circle(Circle const& _other)
        : ShapeInterface(_other.position),
          radius_(_other.radius_) { }
    inline Circle & operator=(Circle && _other) {
      position_ = _other.position_;
      radius_ = _other.radius_;
    }
    inline Circle & operator=(Circle const& _other) {
      position_ = _other.position_;
      radius_ = _other.radius_;
    }
    inline virtual ~Circle(void) = default;

    inline AABB boundary(void) const { return AABB(position_, radius_, radius_); }

    inline real32 radius(void) const { return radius_; }

  protected:
    real32 radius_ = 0.f;
};
}
}

#endif