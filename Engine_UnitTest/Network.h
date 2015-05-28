#ifndef ENGINE_UNIT_TEST_NETWORK_H_
#define ENGINE_UNIT_TEST_NETWORK_H_

#include "Engine/Processor/Threaded.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/IRunnable.hpp"
#include "Engine/Processor/Service.h"
// #include "Engine/Network/Gateway.h"
// #include "Engine/Network/Connector.h"
// #include "Engine/Network/Connection.h"

#include "Engine/Graphics/GL/Shader.h"

/*class Network_GatewayTest : public Engine::Processor::IRunnable < uint32 > {
public:
  inline Network_GatewayTest(void)
      : m_service( new Engine::Processor::Service() )
      , m_thread_runner(new Engine::Processor::Threaded < void >(m_service))
      , m_gateway( new Engine::Network::Gateway( Engine::Network::Gateway::Configuration(16, 1425), m_service ) )
      , m_connection_handler( new ConnectionHandler() ) {
    m_gateway->m_handler = m_connection_handler;
  }

  inline uint32 Run(void) {
    assert( !m_gateway->Bind(tcp::endpoint(address::from_string("127.0.0.1"), 1425)) && "ASDASD");
    m_gateway->Listen();
    m_thread_runner->Run();
    return 0;
  }

protected:
  Engine::Processor::Service * m_service = nullptr;
  Engine::Processor::Threaded < void > * m_thread_runner = nullptr;
  Engine::Network::Gateway * m_gateway = nullptr;
  class ConnectionHandler : public Engine::Network::IConnectionHandler {
    inline void Handle_Connection(shared_ptr < tcp::socket > _socket) {
    }
  };
  shared_ptr < ConnectionHandler > m_connection_handler;
};*/

/*class Network_ConnectonTest : public Engine::Processor::IRunnable < uint32 > {
public:
  inline Network_ConnectonTest(void) {

  }

protected:
  Engine::Processor::Service * m_service = nullptr;
  Engine::Processor::Blocked < void > * m_tunner = nullptr;
  Engine::Network::Connection_TCP * m_tcp_connection = nullptr;
  class CommandHandler : public Engine::Network::ICommandHandler {
  public:
    inline void Handle(const char const* const _data, size_t _received) {
    }
  };

  shared_ptr < CommandHandler > m_command_handler = nullptr;
};*/

#endif
