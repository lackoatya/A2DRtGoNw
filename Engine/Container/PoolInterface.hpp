#ifndef ENGINE_CONTAINER_POOLINTERFACE_HPP_
#define ENGINE_CONTAINER_POOLINTERFACE_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Container {
template < class Type, uint32 size>
class PoolInterface : public NonCopyable {
  public:
    inline PoolInterface(void) { assert(0 < size); }
    inline virtual ~PoolInterface(void) = default;

    inline Type pop(void) { uint32 index = last_--;  return data_[index]; }
    inline void push(Type const& _value) { uint32 index = last_++; data_[index] = _value; }

  protected:
    atomic < uint32 > last_ = size;
    Type data_[size];
};
}
}

#endif