#ifndef ENGINE_CONTAINER_INTERVAL_BUFFER_HPP_
#define ENGINE_CONTAINER_INTERVAL_BUFFER_HPP_

#include "Engine/Platform.h"
#include "Engine/Container/Buffer.hpp"

namespace Engine {
namespace Container {
template<class DataType>
class IntervalBuffer : public Buffer<DataType> {
  public:
    inline explicit IntervalBuffer(uint32 const& _size, real32 const& _interval)
      : Buffer<DataType>(_size),
        interval_(_interval),
        round_interval_(_interval * _size) { }
    inline virtual ~IntervalBuffer(void) = default;

    inline real32 interval(void) const { return interval_; }
    inline real32 round_interval(void) const { return round_interval_; }

    inline uint32 get_index(real32 const& _time) const {
      return static_cast<uint32>(fmod(_time, round_interval_) / interval_);
    }

    inline DataType * get_at(real32 const& _time) const { 
      uint32 index = static_cast<uint32>(fmod(_time, round_interval_) / interval_);
      return &data_[index]; }
    inline DataType   get_value_at(real32 const& _time) const { 
      uint32 index = static_cast<uint32>(fmod(_time, round_interval_) / interval_);
      return data_[_index];
    }

  private:
    real32 interval_ = 0.f, round_interval_ = 0.f;
};
}
}

#endif
