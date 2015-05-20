#ifndef ENGINE_PROCESSOR_SERVICE_H_
#define ENGINE_PROCESSOR_SERVICE_H_

#include "BOOST/asio/io_service.hpp"

#include "Engine/Platform.h"
#include "Engine/Processor/IRunnable.hpp"

namespace Engine {
namespace Processor {
class Service : public NonCopyable
              , public IRunnable < void > {
public:
  inline Service(void)
      : m_service() {
  }

  inline virtual ~Service(void) {
  }

  inline virtual void Run(void) override {
    m_service.run();
  }
  
  inline virtual void Stop(void) {
    m_service.stop();
  }

  inline boost::asio::io_service & service(void) { return m_service; }

protected:
  boost::asio::io_service m_service;
};
}
}

#endif