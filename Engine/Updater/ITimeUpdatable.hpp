#ifndef ENGINE_UPDATER_ITIME_UPDATABLE_HPP_
#define ENGINE_UPDATER_ITIME_UPDATABLE_HPP_

#include "Engine/Platform.h"
#include "Engine/Updater/IUpdatable.hpp"

namespace Engine {
namespace Updater {
template < class Result >
class ITimeUpdatable : public IUpdatable < Result > {
public:
  void Start(void) { last_time_ = boost::chrono::steady_clock::now(); }

protected:
  real32 m_elapsed_time = 0.f;
  boost::chrono::steady_clock::time_point m_last_time = boost::chrono::steady_clock::now();

  inline ITimeUpdatable(void) { }
  inline virtual ~ITimeUpdatable(void) { }

  void UpdateTime(void) {
    boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
    boost::chrono::duration < real32 > difference = now - m_last_time;
    m_elapsed_time += difference.count();
    m_last_time = now;
  }
};
}
}

#endif