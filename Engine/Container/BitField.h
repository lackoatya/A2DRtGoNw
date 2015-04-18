#ifndef ENGINE_CONTAINER_BIT_FIELD_H_
#define ENGINE_CONTAINER_BIT_FIELD_H_

#include "Engine/Types.h"

namespace Engine {
namespace Container {
class BitField32 : public NonCopyable {
  public:
    inline BitField32(void) = default;
    inline BitField32(uint32 _field) : field_(_field) { }
    inline virtual ~BitField32(void) = default;

    inline void reset(void) { field_ = 0; }
    inline void set(uint32 _index) { field_ |= (1 << _index); }
    inline uint32 get(uint32 _index) { return field_ & (1 << _index); }
  protected:
    uint32 field_ = 0;
};
}
}
#endif