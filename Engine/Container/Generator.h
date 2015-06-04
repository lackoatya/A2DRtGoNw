#ifndef ENGINE_CONTAINER_GENERATOR_H_
#define ENGINE_CONTAINER_GENERATOR_H_

#include "Engine/Platform.h"

namespace Engine { namespace Container {

template< class T >
class IGenerator : public NonCopyable {
public:
  inline T pop(void) {
    assert( m_data );
    uint32 index = m_last--; 
    return m_data[index];
  }
  inline void push(T const& _value) {
    assert( m_data );
    uint32 index = m_last++;
    m_data[index] = _value;
  }

protected:
  uint32 m_size = 0;
  atomic< uint32 > m_last;
  T * m_data = nullptr;

  inline IGenerator(void)
      : m_last(0) {
  }

  inline virtual ~IGenerator(void) {
    delete[] m_data;
    m_data = nullptr;
  }
    
  virtual void Fill(void) = 0;

  inline void Allocate(uint32 const& _size) {
    assert( !m_data && "Allocating Pool second time @ IGenerator::Allocate" );
    m_data = new T[_size];
    m_size = _size;
    Fill();
  }
};

class OffsetPool final : public IGenerator< uint32 > {
public:
  inline explicit OffsetPool(uint32 const& _size)
      : IGenerator< uint32 >() {
    Allocate( _size );
  }

  inline ~OffsetPool(void) {
  }

private:
  void Fill(void) {
    for (uint32 current = 0; current < m_size; ++current) {
      m_data[current] = current;
    }
  }
};

} }

#endif