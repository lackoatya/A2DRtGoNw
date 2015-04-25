#ifndef ENGINE_TYPES_H_
#define ENGINE_TYPES_H_

// Assert
#include <assert.h>

// Basic types
#include "BOOST/cstdint.hpp"

typedef int_fast8_t int8;
typedef int_fast16_t int16;
typedef int_fast32_t int32;

typedef uint_fast8_t uint8;
typedef uint_fast16_t uint16;
typedef uint_fast32_t uint32;

typedef float real32;
typedef double real64;

// Shared Pointer
#include "BOOST/shared_ptr.hpp"

template<class Type>
using shared_ptr = boost::shared_ptr <Type>;

// Atomic
#include "BOOST/atomic.hpp"
template<class Type>
using atomic = boost::atomic <Type>;

// Mutex
#include "BOOST/thread/shared_mutex.hpp"
typedef boost::shared_mutex Mutex;

// Lock
#include "BOOST/thread/locks.hpp"
typedef boost::unique_lock<Mutex> Lock;

// Sockets
#include "BOOST/asio.hpp"
typedef boost::asio::ip::tcp::socket tcp_socket;
typedef boost::asio::ip::udp::socket udp_socket;

// Constants
const real32 PI = 3.141592741f;
const real32 EPSILON = 0.0001f;

namespace NonCopyable_{
class NonCopyable {
  protected:
    inline NonCopyable(void) = default;
    inline virtual ~NonCopyable(void) = default;

  private:
    inline NonCopyable(NonCopyable && _other) = delete;
    inline NonCopyable(NonCopyable const& _other) = delete;
    inline NonCopyable & operator=(NonCopyable && _other) = delete;
    inline NonCopyable & operator=(NonCopyable const& _other) = delete;
};
}

typedef NonCopyable_::NonCopyable NonCopyable;

// Vector2
struct Vector2
{
  public:
  /*union
  {
	  real32 m[1][1];
	  real32 v[2];

	  struct
	  {
		  real32 x;
		  real32 y;
	  };
  };*/
    real32 x = 0.0f, y = 0.0f;

    inline Vector2(real32 const& _x, real32 const& _y) : x(_x), y(_y) { }
    inline Vector2(void) : Vector2(0.0f, 0.0f) { }
    inline Vector2(Vector2 && _other) : x(_other.x), y(_other.y) { }
    inline Vector2(Vector2 const& _other) : x(_other.x), y(_other.y) { }
    inline Vector2 & operator=(Vector2 && _other) {
      x = _other.x;
      y = _other.y;
      return *this;
    }
    inline Vector2 & operator=(Vector2 const& _other){
      x = _other.x;
      y = _other.y;
      return *this;
    }
    inline virtual ~Vector2(void) = default;

    inline void Set(real32 const& _x, real32 const& _y) { x = _x; y = _y; }

    inline Vector2 operator+(real32 const& _s) const { return Vector2(x + _s, y + _s); }
    inline Vector2 operator+(Vector2 const& _rhs) const { return Vector2(x + _rhs.x, y + _rhs.y); }
    inline void operator+=(Vector2 const& _rhs){ x += _rhs.x; y += _rhs.y; }

    inline Vector2 operator-(void) const { return Vector2(-x, -y); }
    inline Vector2 operator-(Vector2 const& _rhs) const { return Vector2(x - _rhs.x, y - _rhs.y); }
    inline void operator-=(Vector2 const& _rhs) { x -= _rhs.x; y -= _rhs.y; }

    inline Vector2 operator*(real32 const& _s) const { return Vector2(x * _s, y * _s); }
    inline Vector2 operator/(real32 const& _s) const { return Vector2(x / _s, y / _s); }
    inline void operator*=(real32 const& _s) { x *= _s; y *= _s; }

    inline real32 LenSqr(void) const { return x * x + y * y; }
    inline real32 Len(void) const { return std::sqrt(x * x + y * y); }

    inline void Rotate(real32 const& _radians) {
      real32 c = std::cos(_radians);
      real32 s = std::sin(_radians);

      real32 xp = x * c - y * s;
      real32 yp = x * s + y * c;

      x = xp;
      y = yp;
    }

    inline void Rotate_Degree(real32 const& _degree) {
      real32 radians = _degree / 180.0f * PI;
      real32 c = std::cos(radians);
      real32 s = std::sin(radians);

      real32 xp = x * c - y * s;
      real32 yp = x * s + y * c;

      x = xp;
      y = yp;
    }

    inline void Normalize(void) {
      real32 len = Len();

      if (EPSILON < len) {
	real32 invLen = 1.0f / len;
	x *= invLen;
	y *= invLen;
      }
    }
};

inline Vector2 operator*(float const& _s, Vector2 const& _v) { return Vector2(_s * _v.x, _s * _v.y); }

inline Vector2 Min(const Vector2& a, const Vector2& b) {
  return Vector2(std::min(a.x, b.x), std::min(a.y, b.y));
}

inline Vector2 Max(const Vector2& a, const Vector2& b) {
  return Vector2(std::max(a.x, b.x), std::max(a.y, b.y));
}

inline real32 Dot(const Vector2& a, const Vector2& b) {
  return a.x * b.x + a.y * b.y;
}

inline real32 DistSqr(const Vector2& a, const Vector2& b) {
  Vector2 c = a - b;
  return Dot(c, c);
}

inline Vector2 Cross(const Vector2& v, real32 a) {
  return Vector2(a * v.y, -a * v.x);
}

inline Vector2 Cross(real32 a, const Vector2& v) {
  return Vector2(-a * v.y, a * v.x);
}

inline real32 Cross(const Vector2& a, const Vector2& b) {
  return a.x * b.y - a.y * b.x;
}

// 2x2 Matrix
struct Mat2
{
  public:
    /*union
    {
	    struct
	    {
		    real32 m00, m01;
		    real32 m10, m11;
	    };

	    real32 m[2][2];
	    real32 v[4];
    };*/

    real32 m00 = 0., m01 = 0.;
    real32 m10 = 0., m11 = 0.;

    inline Mat2(real32 const& _radians) {
      real32 c = std::cos(_radians);
      real32 s = std::sin(_radians);

      m00 = c; m01 = -s;
      m10 = s; m11 = c;
    }
    Mat2(real32 const& _a, real32 const& _b, real32 const& _c, real32 const& _d)
        : m00(_a), m01(_b),
	  m10(_c), m11(_d) { }
    inline Mat2(void)
          : Mat2(1.0f, 0.0f, 0.0f, 1.0f) { }
    inline Mat2(Mat2 && _other)
        : m00(_other.m00), m01(_other.m01), m10(_other.m10), m11(_other.m11) { }
    inline Mat2(Mat2 const& _other)
        : m00(_other.m00), m01(_other.m01), m10(_other.m10), m11(_other.m11) { }
    inline Mat2 & operator=(Mat2 && _other) {
      m00 = _other.m00;
      m01 = _other.m01;
      m10 = _other.m10;
      m11 = _other.m11;
      return *this;
    }
    inline Mat2 & operator=(Mat2 const& _other) {
      m00 = _other.m00;
      m01 = _other.m01;
      m10 = _other.m10;
      m11 = _other.m11;
      return *this;
    }    
    inline virtual ~Mat2(void) = default;

    inline void Set(real32 const& _radians) {
      real32 c = std::cos(_radians);
      real32 s = std::sin(_radians);

      m00 = c; m01 = -s;
      m10 = s; m11 = c;
    }

    inline Mat2 Abs(void) const {
      return Mat2(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11));
    }

    inline Vector2 AxisX(void) const { return Vector2(m00, m10); }
    inline Vector2 AxisY(void) const { return Vector2(m01, m11); }

    inline Mat2 Transpose(void) const { return Mat2(m00, m10, m01, m11); }

    inline const Vector2 operator*(Vector2 const& _rhs) const {
      return Vector2(m00 * _rhs.x + m01 * _rhs.y, m10 * _rhs.x + m11 * _rhs.y);
    }

    inline const Mat2 operator*(Mat2 const& _rhs) const {
      return Mat2(m00 * _rhs.m00 + m01 * _rhs.m10,
	          m00 * _rhs.m01 + m01 * _rhs.m11,
	          m10 * _rhs.m00 + m11 * _rhs.m10,
	          m10 * _rhs.m01 + m11 * _rhs.m11 );
    }
};

// Comparison with tolerance of EPSILON
inline bool Equal(real32 a, real32 b) {
  return std::abs(a - b) <= EPSILON;
}

inline real32 Sqr(real32 a) {
  return a * a;
}

inline real32 Clamp(real32 min, real32 max, real32 a) {
  if (a < min) return min;
  if (a > max) return max;
  return a;
}

inline int32 Round(real32 a) {
  return (int32)(a + 0.5f);
}

inline bool BiasGreaterThan(real32 a, real32 b) {
  const real32 k_biasRelative = 0.95f;
  const real32 k_biasAbsolute = 0.01f;
  return a >= b * k_biasRelative + a * k_biasAbsolute;
}

const real32 gravityScale = 5.0f;
const Vector2 gravity(0, 10.0f * gravityScale);

// TODO Remove this!!
const float dt = 1.0f / 60.0f;

#endif