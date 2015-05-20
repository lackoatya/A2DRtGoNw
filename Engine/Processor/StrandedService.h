#ifndef ENGINE_PROCESSOR_STRANDED_SERVICE_H_
#define ENGINE_PROCESSOR_STRANDED_SERVICE_H_

#include "BOOST/asio/strand.hpp"

#include "Engine/Platform.h"
#include "Engine/Processor/Service.h"

namespace Engine {
namespace Processor {
class StrandedService : public NonCopyable
                      , public Service {
public:
  inline StrandedService(void)
      : Service()
      , m_work(m_service)
      , m_strand(m_service) {
  }
  
  inline virtual ~StrandedService(void) {
  }

  inline boost::asio::strand & strand(void) { return m_strand; };

protected:
  boost::asio::io_service m_service;
  boost::asio::io_service::work m_work;
  boost::asio::strand m_strand;
};
}
}

#endif