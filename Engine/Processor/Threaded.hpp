#ifndef ENGINE_PROCESSOR_THREADED_HPP_
#define ENGINE_PROCESSOR_THREADED_HPP_

#include "BOOST/thread.hpp"

#include "Engine/Types.h"
#include "Engine/Processor/IRunnable.hpp"

namespace Engine {
namespace Processor {
template < class Result >
class Threaded : public NonCopyable
               , public IRunnable < void > {
public:
  inline Threaded(IRunnable < Result > * _runner)
      : m_runner(_runner)
      , m_thread() {
  }
    
  inline virtual ~Threaded(void) {
  }

  inline virtual void Run(void) override {
    m_thread = boost::thread(boost::bind(&IRunnable < Result >::Run, &m_runner));
  }

  inline virtual void Stop(void) {
    m_thread.interrupt();
  
  }
  inline virtual void Join(void) {
    m_thread.join();
  }

protected:
  IRunnable < Result > m_runner;
  boost::thread m_thread;
};
}
}

#endif