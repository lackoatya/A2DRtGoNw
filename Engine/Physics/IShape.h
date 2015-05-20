#ifndef ENGINE_PHYSICS_ISHAPE_H_
#define ENGINE_PHYSICS_ISHAPE_H_

#include "Engine/Platform.h"

namespace Engine {
namespace Physics {
class AABB;

struct IShape {
  public:
    virtual AABB boundary(void) const = 0;

    inline Vector2 position(void) const { return position_; }
    inline void set_position(Vector2 const& _position) { position_ = _position; }

  protected:
    Vector2 position_;

    inline explicit IShape(Vector2 const& _position) : position_(_position) { }
    // inline ShapeInterface(ShapeInterface && _other) : position_(_other.position_) { }
    // inline ShapeInterface(ShapeInterface const& _other) : position_(_other.position_) { }
    // inline ShapeInterface & operator=(ShapeInterface && _other) { position_ = _other.position_; }
    // inline ShapeInterface & operator=(ShapeInterface const& _other) { position_ = _other.position_; }
    inline virtual ~IShape(void) = default;
};
}
}

#endif