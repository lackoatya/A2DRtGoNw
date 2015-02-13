#pragma once

// Basic types
#include <boost\cstdint.hpp>

typedef int_fast8_t int8;
typedef int_fast16_t int16;
typedef int_fast32_t int32;

typedef uint_fast8_t uint8;
typedef uint_fast16_t uint16;
typedef uint_fast32_t uint32;

typedef float real32;
typedef double real64;

// Shared Pointer
#include <boost\shared_ptr.hpp>

template< class Type >
using shared_ptr = boost::shared_ptr < Type >;