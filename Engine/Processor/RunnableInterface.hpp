#ifndef ENGINE_PROCESSOR_RUNNABLE_INTERFACE_HPP_
#define ENGINE_PROCESSOR_RUNNABLE_INTERFACE_HPP_

#include "BOOST/chrono.hpp"

#include "Engine/Types.h"

namespace Engine {
namespace Processor {
template <class Updatable, class Processable, class Result>
class RunnableInterface : public NonCopyable {
  public:
    virtual Result Run(void) = 0;

  protected:
    Updatable * instance_ = nullptr;

    inline RunnableInterface(Updatable * _instance) : instance_(_instance) { }
    inline virtual ~RunnableInterface(void) = default;
};
}
}

#endif