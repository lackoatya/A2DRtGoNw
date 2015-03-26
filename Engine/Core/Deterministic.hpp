#ifndef ENGINE_CORE_DETERMINISTIC_HPP_
#define ENGINE_CORE_DETERMINISTIC_HPP_

#include "BOOST/chrono.hpp"

#include "Engine/Types.h"

namespace Engine { 
namespace Core {
template <class Processable, class Result>
static Result Deterministic(Processable * _instance, real32 const& _interval) {
  real32 elapsed_time = 0.0f;
  boost::chrono::steady_clock::time_point now, last_time = boost::chrono::steady_clock::now();

  while (true) {
    now = boost::chrono::steady_clock::now();
    boost::chrono::duration<real32> difference = now - last_time; // TODO use auto here?
    elapsed_time += difference.count();
    last_time = now;

    while (_interval <= elapsed_time) {
      Result result = _instance->Process();
      if (result.Valid()) return result;

      elapsed_time -= _interval;
    }
  }
};
}
}

#endif