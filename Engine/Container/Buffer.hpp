#ifndef ENGINE_CONTAINER_BUFFER_HPP_
#define ENGINE_CONTAINER_BUFFER_HPP_

#include "BOOST/atomic.hpp"

#include "Engine/Types.h"

namespace Engine {
namespace Container {
template<class DataType>
class Buffer : public NonCopyable {
public:
  inline Buffer(uint32 const& _size)
      : size_(_size),
        data_(new DataType[size_]) { }
  inline virtual ~Buffer(void) {
    delete[] data_;
    data_ = nullptr;
  }

  inline uint32 next(uint32 const& _index) const {
    return (_index < size_ - 1) ? _index + 1 : 0;
  }

  /*inline void add(DataType const& _value) {
    uint32 next_ = next(last_);
    data_[next_] = _value;
    last_ = next_;
  }*/

  inline void procede(void) {
    last_ = next(last_);
  }

  inline void add(DataType _value) {
    memcpy(&(data_[next(last_)]), &_value, sizeof(DataType));
    last_ = next(last_);
  }

  inline void add(DataType * _value) {
    memcpy(&(data_[next(last_)]), _value, sizeof(DataType));
    last_ = next(last_);
  }

  inline uint32 size(void) const { return size_; }
  inline uint32 last(void) const { return last_; }
  inline DataType * get(uint32 const& _index) const { return &data_[_index]; }
  inline DataType   get_value(uint32 const& _index) const { return data_[_index]; }
  inline DataType * get_last(void) const { return &data_[last_]; }
  inline DataType   get_last_value(void) const { return data_[last_]; }
  inline DataType * get_next(void) const { return &data_[next(last_)]; }
  inline DataType   get_next_value(void) const { return data_[nest(last_)]; }

  protected:
    const uint32 size_;
    boost::atomic<uint32> last_ = 0;
    DataType * data_ = nullptr;
};
}
}


#endif