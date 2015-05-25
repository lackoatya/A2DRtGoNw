#ifndef ENGINE_CONTAINER_BUFFER_HPP_
#define ENGINE_CONTAINER_BUFFER_HPP_

#include "Engine/Platform.h"

namespace Engine {
namespace Container {
// Single-Threaded Circlic Buffer.
template < typename DataType >
class Buffer : public NonCopyable {
public:
  inline Buffer(uint32 const& _size)
      : size_(_size),
        m_data(new DataType[size_]) {
  }
  
  inline virtual ~Buffer(void) {
    delete[] m_data;
    m_data = nullptr;
  }

  inline uint32 size(void) const { return m_size; }
  inline uint32 last(void) const { return m_last.load(); }

  // Advances m_last value, and returns the current m_last value into _index
  inline void Advance(uint32 & _index) {
    uint32 last_cache = m_last.load();
    _index = Next(last_cache);
    assert( m_last.compare_exchange_strong(last_cache, _index) && "Invalid compare_exhange_strong @ Buffer::Advance");
  }

  // Returns the data at _index.
  // Note: _index is not bound checked!
  inline DataType * operator[](uint32 const& _index) const {
    assert( _index < m_size && "Invalid _index @ Buffer::[]");
    return m_data[_index];
  }

protected:
  const uint32 m_size;
  boost::atomic< uint32 > m_last = 0;
  DataType * m_data = nullptr;

  // Sets _index to be bound valid.
  // Note: _index should not be greater than 2 * m_size!
  inline void Next(uint32 & _index) const {
    assert( _index < 2 * m_size && "Invalid _index @ Buffer::Next!");
    return _index < m_size ? _index : _index - m_size;
  }
};

// Multi-Threaded Proxy for a Single-Threaded Circlic Buffer.
template < typename DataType >
class Buffer_Proxy : public NonCopyable {
public:
  inline Buffer_Proxy(shared_ptr < Buffer < DataType > > _buffer)
      : m_buffer(_buffer) {
    assert( _buffer && "Invalid _buffer @ Buffer_Proxy::ctor!");
  }

  inline ~Buffer_Proxy(void) = default;

  // Returns the data at _index as const.
  // Note: _index is not bound checked!
  inline const DataType * operator[](uint32 const& _index) const {
    assert( m_buffer && "Invalid _index @ Buffer_Proxy::[]!");
    return m_buffer[_index];
  }

private:
  shared_ptr < Buffer < DataType > > m_buffer;
};
}
}


#endif