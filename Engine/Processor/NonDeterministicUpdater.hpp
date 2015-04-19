#ifndef ENGINE_PROCESSOR_NONDETERMINISTIC_UPDATER_HPP_
#define ENGINE_PROCESSOR_NONDETERMINISTIC_UPDATER_HPP_

#include "Engine/Processor/UpdaterInterface.hpp"

namespace Engine {
namespace Processor {
template <class Result>
class NonDeterministicProcessInterface {
  public:
    virtual Result Process(real32 const& _elapsed_time) = 0;

    inline const real32 interval(void) const { return interval_; }

  protected:
    inline NonDeterministicProcessInterface(real32 const& _interval) : interval_(_interval) { }
    inline virtual ~NonDeterministicProcessInterface(void) = default;

    const real32 interval_ = 0.f;
};

template <class Processable, class Result>
class NonDeterministicUpdater : public UpdaterInterface<Processable, Result> {
  public:
    inline NonDeterministicUpdater(Processable * _instance)
        : UpdaterInterface<Processable, Result>(_instance) { }
    inline NonDeterministicUpdater(void) = delete;
    inline virtual ~NonDeterministicUpdater(void) = default;

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