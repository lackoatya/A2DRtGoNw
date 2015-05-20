#ifndef ENGINE_PHYSICS_AABB_H_
#define ENGINE_PHYSICS_AABB_H_

#include "Engine/Platform.h"
#include "Engine/Physics/ShapeInterface.h"

namespace Engine {
namespace Physics {
class AABB : public ShapeInterface {
  public:
    inline AABB(Vector2 const& _position, real32 const& _width, real32 const& _height)
        : ShapeInterface(_position),
          width_(_width),
          height_(_height) { }
    inline AABB(AABB && _other)
        : ShapeInterface(_other.position_),
          width_(_other.width_),
          height_(_other.height_) { }
    inline AABB(AABB const& _other)
        : ShapeInterface(_other.position_),
          width_(_other.width_),
          height_(_other.height_) { }
    inline AABB & operator=(AABB && _other) {
      position_ = _other.position_;
      width_ = _other.width_;
      height_ = _other.height_;

      return *this;
    }
    inline AABB & operator=(AABB const& _other) {
      position_ = _other.position_;
      width_ = _other.width_;
      height_ = _other.height_;

      return *this;
    }
    inline virtual ~AABB(void) = default;

    inline AABB boundary(void) const { return *this; }

    inline real32 width(void) const { return width_; }
    // inline void set_width(real32 const& _width) { width_ = _width; };
    inline real32 height(void) const { return height_; }
    // inline void set_height(real32 const& _height) { height_ = _height; }

  protected:
    real32 width_ = 0.f, height_ = 0.f;
};
}
}

#endif