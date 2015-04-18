#ifndef ENGINE_NUMERICS_LINEAR_INTERPOLATION_HPP_
#define ENGINE_NUMERICS_LINEAR_INTERPOLATION_HPP_

#include "Engine/Types.h"

namespace Engine {
namespace Numerics {
template<class DataType>
DataType LinearInterpolation(DataType const& _start, real32 const& _alpha, DataType const& _end) {
  return _start + ((_end - _start) * _alpha);
};
}
}

#endif