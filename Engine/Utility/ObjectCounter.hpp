#ifndef ENGINE_UTILITY_OBJECT_COUNTER_HPP_
#define ENGINE_UTILITY_OBJECT_COUNTER_HPP_

namespace Engine {
namespace Utility {
template < typename Object >
class ObjectCounter final {
public:
  inline ObjectCounter(void) {
    ++m_created;
    ++m_alive;
  }

  inline ObjectCounter(ObjectCounter const&) {
    ++m_created;
    ++m_alive;
  }

  unsigned int created(void) const { return m_created; }

  unsigned int alive(void) const { return m_alive; }

protected:
  static unsigned int m_created;
  static unsigned int m_alive;

  inline ~ObjectCounter(void) {
    --m_alive;
  }
};

template < typename Object > int ObjectCounter < Object >::m_created(0);
template < typename Object > int ObjectCounter < Object >::m_alive(0);
}
}

#endif