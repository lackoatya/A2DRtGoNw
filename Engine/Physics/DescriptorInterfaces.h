#ifndef ENGINE_PHYSICS_DESCRIPTOR_H_
#define ENGINE_PHYSICS_DESCRIPTOR_H_

#include "Engine/Types.h"

namespace Engine {
namespace Physics {
struct DescriptorInterface : public NonCopyable {
  public:
    Vector2 center;
    real32 width, height;

    virtual void Describe(uint8 * _segment) = 0;

  protected:
    inline DescriptorInterface(Vector2 const& _center, real32 const& _widht, real32 const& _height)
        : center(_center),
          width(_widht),
          height(_height) { }
    inline virtual ~DescriptorInterface(void) = default;
};

struct DynamicDescriptor : public DescriptorInterface {
public:
  Vector2 velocity, force;

  DynamicDescriptor(Vector2 const& _center, real32 const& _width, real32 const& _height)
    : DescriptorInterface(_center, _width, _height) { };
  inline virtual ~DynamicDescriptor(void) = default;

  void Describe(uint8 * _segment) { memcpy(_segment, this, sizeof(this)); };
};
}
}

#endif