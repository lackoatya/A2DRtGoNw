#ifndef ENGINE_PHYSICS_DESCRIPTOR_H_
#define ENGINE_PHYSICS_DESCRIPTOR_H_

#include "Engine/Types.h"

namespace Engine {
namespace Physics {
struct DescriptorInterface {
  public:
    Vector2 center;
    real32 width, height;

    virtual void Describe(uint8 * _segment) = 0;

  protected:
    inline DescriptorInterface(Vector2 const& _center, real32 const& _widht, real32 const& _height)
        : center(_center),
          width(_widht),
          height(_height) { }
    inline DescriptorInterface(void) = delete;
    inline DescriptorInterface(DescriptorInterface && _other) = delete;
    inline DescriptorInterface(DescriptorInterface const& _other) = delete;
    inline DescriptorInterface & operator=(DescriptorInterface && _other) = delete;
    inline DescriptorInterface & operator=(DescriptorInterface const& _other) = delete;
    inline virtual ~DescriptorInterface(void) = default;
};

struct DynamicDescriptor : public DescriptorInterface {
public:
  Vector2 velocity, force;

  DynamicDescriptor(Vector2 const& _center, real32 const& _width, real32 const& _height)
    : DescriptorInterface(_center, _width, _height) { };
  inline DynamicDescriptor(void) = delete;
  inline DynamicDescriptor(DynamicDescriptor && _other) = delete;
  inline DynamicDescriptor(DynamicDescriptor const& _other) = delete;
  inline DynamicDescriptor & operator=(DynamicDescriptor && _other) = delete;
  inline DynamicDescriptor & operator=(DynamicDescriptor const& _other) = delete;
  inline virtual ~DynamicDescriptor(void) = default;

  void Describe(uint8 * _segment) { memcpy(_segment, this, sizeof(this)); };
};
}
}

#endif