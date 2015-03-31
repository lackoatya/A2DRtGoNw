#ifndef ENGINE_PROCESSOR_BLOCKED_HPP_
#define ENGINE_PROCESSOR_BLOCKED_HPP_

#include "Engine/Processor/RunnableInterface.hpp"

namespace Engine {
namespace Processor {
template<class Updatable, class Processable, class Result>
class Blocked : public RunnableInterface<Updatable, Processable, Result> {
  public:
    inline Blocked(Updatable * _instance)
        : RunnableInterface<Updatable, Processable, Result>(_instance) { }
    inline virtual ~Blocked(void) = default;

    inline Result Run(void) {
      while (true) {
        Result result = instance_->Update();
        if (result.IsValid()) return result;
      }
    }
};
}
}

#endif