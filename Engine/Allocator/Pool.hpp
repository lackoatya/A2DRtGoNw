#ifndef ENGINE_ALLOCATOR_POOL_HPP_
#define ENGINE_ALLOCATOR_POOL_HPP_

#include "Engine/Platform.h"

namespace Engine { namespace Allocator {

template< typename T >
class IPool : public NonCopyable {
public:

protected:
  inline IPool(void) {
  }

  inline virtual ~IPool(void) {
  }
};

} }

#endif