#ifndef ENGINE_CONTAINER_POOL_H_
#define ENGINE_CONTAINER_POOL_H_

#include "Engine/Platform.h"

namespace Engine {
namespace Container {
template < class Type >
class IPool : public NonCopyable {
  public:
    inline IPool(void) = default;
    inline virtual ~IPool(void) {
      delete[] m_data;
      m_data = nullptr;
    }

    inline Type pop(void) {
      assert( m_data );
      uint32 index = m_last--; 
      return m_data[index];
    }
    inline void push(Type const& _value) {
      assert( m_data );
      uint32 index = m_last++;
      m_data[index] = _value;
    }

  protected:
    uint32 m_size = 0;
    atomic < uint32 > m_last = m_size;
    Type * m_data = nullptr;
    
    virtual void Fill(void) = 0;

    inline void Allocate(uint32 const& _size) {
      assert(!m_data);
      m_data = new Type[_size];
      m_size = _size;

      Fill();
    }
};

class OffsetPool : public IPool < uint32 > {
  public:
    inline OffsetPool(uint32 const& _size)
        : IPool < uint32 >() {
      Allocate(_size);
    }
    inline ~OffsetPool(void) = default;

  private:
    void Fill(void) {
      for (uint32 current = 0; current < m_size; ++current) {
        m_data[current] = current;
      }
    }
};
}
}

#endif