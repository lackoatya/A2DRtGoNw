#ifndef ENGINE_UPDATER_DETERMINISTIC_HPP_
#define ENGINE_UPDATER_DETERMINISTIC_HPP_

#include "Engine/Updater/UpdaterInterface.hpp"

namespace Engine { 
namespace Updater {
template < class Result >
class DeterministicProcessInterface {
  public:
    virtual Result Process(void) = 0;

    inline const real32 interval(void) const { return interval_; }

  protected:
    inline DeterministicProcessInterface(real32 const& _interval) : interval_(_interval) { }
    inline virtual ~DeterministicProcessInterface(void) = default;

    const real32 interval_ = 0.f;
};

template < class Processable, class Result >
class Deterministic : public UpdaterInterface < Processable, Result > {
  public:
    inline Deterministic(Processable * _instance)
        : UpdaterInterface < Processable, Result >(_instance) { }
    inline virtual ~Deterministic(void) = default;

    Result Update(void) {
      UpdateTime();

      Result result;
      while (instance_->interval() <= elapsed_time_) {
        result = instance_->Process();
        elapsed_time_ -= instance_->interval();
      }
      return result;
    }
};
}
}

#endif