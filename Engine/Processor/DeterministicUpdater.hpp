#ifndef ENGINE_PROCESSOR_DETERMINISTIC_UPDATER_HPP_
#define ENGINE_PROCESSOR_DETERMINISTIC_UPDATER_HPP_

#include "Engine/Processor/UpdaterInterface.hpp"

namespace Engine { 
namespace Processor {
template <class Result>
class DeterministicProcessInterface {
  public:
    virtual Result Process(void) = 0;
};

template <class Processable, class Result>
class DeterministicUpdater : UpdaterInterface<Processable, Result> {
  public:
    inline DeterministicUpdater(Processable * _instance, real32 const& _interval)
        : UpdaterInterface<Processable, Result>(_instance),
          interval_(_interval) { }
    inline DeterministicUpdater(void) = delete;
    inline virtual ~DeterministicUpdater(void) = default;

    Result Update(void) {
      UpdateTime();

      if (interval_ <= elapsed_time_) {
        Result result = instance_->Process();
        elapsed_time_ -= interval_;
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