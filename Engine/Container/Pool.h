#ifndef ENGINE_CONTAINER_POOL_H_
#define ENGINE_CONTAINER_POOL_H_

#include "Engine/Types.h"

namespace Engine {
namespace Container {
template < class Type >
class PoolInterface : public NonCopyable {
  public:
    inline PoolInterface(void) = default;
    inline virtual ~PoolInterface(void) {
      delete[] m_data;
      m_data = nullptr;
    }

    inline Type pop(void) {
      assert(m_data);
      uint32 index = last_--; 
      return data_[index];
    }
    inline void push(Type const& _value) {
      assert(m_data);
      uint32 index = last_++;
      data_[index] = _value;
    }

  protected:
    uint32 m_size = 0;
    atomic < uint32 > m_last_ = m_size;
    Type * m_data = nullptr;
    
    virtual void Fill(void) = 0;

    inline void Allocate(uint32 const& _size) {
      assert(!m_data);
      m_data = new Type[_size];
      m_size = _size;

      Fill();
    }
};

class OffsetPool : public PoolInterface < uint32 > {
  public:
    inline OffsetPool(uint32 const& _size)
        : PoolInterface < uint32 >() {
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