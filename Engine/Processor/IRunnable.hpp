#ifndef ENGINE_PROCESSOR_IRUNNABLE_HPP_
#define ENGINE_PROCESSOR_IRUNNABLE_HPP_

namespace Engine {
namespace Processor {
template < class Result >
class IRunnable {
public:
  virtual Result Run(void) = 0;
};
}
}

#endif