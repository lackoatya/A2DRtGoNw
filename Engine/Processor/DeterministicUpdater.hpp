#ifndef ENGINE_PROCESSOR_DETERMINISTIC_UPDATER_HPP_
#define ENGINE_PROCESSOR_DETERMINISTIC_UPDATER_HPP_

#include "Engine/Processor/UpdaterInterface.hpp"

namespace Engine { 
namespace Processor {
template <class Result>
class DeterministicProcessInterface {
  public:
    virtual Result Process(void) = 0;

    inline const real32 interval(void) const { return interval_; }

  protected:
    inline DeterministicProcessInterface(real32 const& _interval) : interval_(_interval) { }
    inline virtual ~DeterministicProcessInterface(void) = default;

    const real32 interval_ = 0.f;
};

template <class Processable, class Result>
class DeterministicUpdater : public UpdaterInterface<Processable, Result> {
  public:
    inline DeterministicUpdater(Processable * _instance)
        : UpdaterInterface<Processable, Result>(_instance) { }
    inline DeterministicUpdater(void) = delete;
    inline virtual ~DeterministicUpdater(void) = default;

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