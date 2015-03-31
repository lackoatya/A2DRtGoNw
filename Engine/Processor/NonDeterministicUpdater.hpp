#ifndef ENGINE_PROCESSOR_NONDETERMINISTIC_UPDATER_HPP_
#define ENGINE_PROCESSOR_NONDETERMINISTIC_UPDATER_HPP_

#include "Engine/Processor/UpdaterInterface.hpp"

namespace Engine {
namespace Processor {
template <class Result>
class NonDeterministicProcessInterface {
  public:
    virtual Result Process(real32 const& _elapsed_time) = 0;
};

template <class Processable, class Result>
class NonDeterministicUpdater : UpdaterInterface<Processable, Result> {
  public:
    inline NonDeterministicUpdater(Processable * _instance, real32 const& _interval)
        : UpdaterInterface<Processable, Result>(_instance),
          interval_(_interval) { }
    inline NonDeterministicUpdater(void) = delete;
    inline virtual ~NonDeterministicUpdater(void) = default;

    Result Update(void) {
      UpdateTime();

      if (interval_ <= elapsed_time_) {
        Result result = instance_->Process(elapsed_time_);
        elapsed_time_ = 0.f;
        return result;
      } else {
        return Result();
      }
    }

  private:
    real32 interval_ = 0.f;
};
}
}

#endif