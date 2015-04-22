#ifndef ENGINE_UPDATER_NONDETERMINISTIC_HPP_
#define ENGINE_UPDATER_NONDETERMINISTIC_HPP_

#include "Engine/Updater/UpdaterInterface.hpp"

namespace Engine {
namespace Updater {
template < class Result >
class NonDeterministicProcessInterface {
  public:
    virtual Result Process(real32 const& _elapsed_time) = 0;

    inline const real32 interval(void) const { return interval_; }

  protected:
    inline NonDeterministicProcessInterface(real32 const& _interval) : interval_(_interval) { }
    inline virtual ~NonDeterministicProcessInterface(void) = default;

    const real32 interval_ = 0.f;
};

template < class Result >
class NonDeterministic : public UpdaterInterface < NonDeterministicProcessInterface < Result >, Result > {
  public:
  inline NonDeterministic(NonDeterministicProcessInterface < Result > * _instance)
        : UpdaterInterface < NonDeterministicProcessInterface < Result >, Result >(_instance) { }
    inline virtual ~NonDeterministic(void) = default;

    Result Update(void) {
      UpdateTime();

      if (instance_->interval() <= elapsed_time_) {
        Result result = instance_->Process(elapsed_time_);
        elapsed_time_ = 0.f;
        return result;
      } else {
        return Result();
      }
    }
};
}
}

#endif