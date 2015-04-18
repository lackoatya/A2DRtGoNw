#ifndef ENGINE_GRAPHICS_MOTION_H_
#define ENGINE_GRAPHICS_MOTION_H_

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
struct Motion {
  public:
    uint32 animation = 0;
    real32 start_time = 0.f, duration = 0.f;

    inline Motion(void) { }
    inline Motion(uint32 const& _animation, real32 const& _start_time, real32 const& _duration)
        : animation(_animation),
          start_time(_start_time),
          duration(_duration){ }
    inline Motion(Motion && _other) = delete;
    inline Motion(Motion const& _other) = delete;
    inline Motion & operator=(Motion && _other) {
      animation = _other.animation;
      start_time = _other.start_time;
      duration = _other.duration;

      return *this;
    }
    inline Motion & operator=(Motion const& _other) {
      animation = _other.animation;
      start_time = _other.start_time;
      duration = _other.duration;

      return *this;
    }
    inline virtual ~Motion(void) = default;
};
}
}

#endif