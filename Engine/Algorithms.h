#ifndef ENGINE_ALGORITHMS_H_
#define ENGINE_ALGORITHMS_H_

#include "BOOST/algorithm/clamp.hpp"
template < typename T >
T & clamp(T const& _value, T const& _lower, T const& _upper) {
  return boost::algorithm::clamp(_value, _lower, _upper);
}

#endif