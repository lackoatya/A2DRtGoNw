#ifndef ENGINE_NUMERICS_IINTERPOLATOR_HPP_
#define ENGINE_NUMERICS_IINTERPOLATOR_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Numerics {
template < class Type >
class IInterpolator {
public:
  Type Interpolate(Type const& _start, real32 const& _alpha, Type const& _end);
};
}
}

#endif