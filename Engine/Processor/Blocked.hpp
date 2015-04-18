#ifndef ENGINE_PROCESSOR_BLOCKED_HPP_
#define ENGINE_PROCESSOR_BLOCKED_HPP_

#include "BOOST/thread.hpp"

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
      instance_->Start();
      while (true) {
        Result result = instance_->Update();
        if (result.IsValid()) return result;

        boost::this_thread::sleep_for(boost::chrono::microseconds(1));
      }
    }
};
}
}

#endif