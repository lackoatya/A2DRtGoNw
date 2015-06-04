#ifndef ENGINE_UNIT_TEST_NETWORK_H_
#define ENGINE_UNIT_TEST_NETWORK_H_

#include <iostream>

#include "Engine/Processor/Threaded.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/IRunnable.hpp"
#include "Engine/Processor/Service.h"
#include "Engine/Network/Gateway.h"
// #include "Engine/Network/Connector.h"
// #include "Engine/Network/Connection.h"

class Network_Test : public Engine::Processor::IRunnable< uint32 > {
public:
  inline Network_Test(void)
      : m_service( boost::make_shared< Engine::Processor::Service >() )
      , m_thread_runner( new Engine::Processor::Threaded< void >( m_service ) )
      , m_connection_handler( new ConnectionHandler() )
      , m_gateway( new Engine::Network::Gateway_Both( m_service, m_connection_handler ) ) {
    m_gateway->set_handler( m_connection_handler );
  }

  inline uint32 Run(void) {
    assert( !m_gateway->Listen(address::from_string("127.0.0.1"), 1425, 8) && "Error while binding!");
    m_gateway->Accept();
    m_thread_runner->Run();
    return 0;
  }

protected:
  shared_ptr< Engine::Processor::Service > m_service = nullptr;
  Engine::Processor::Threaded < void > * m_thread_runner;
  class ConnectionHandler : public Engine::Network::IHandler< shared_ptr< tcp::socket >
                                                            , shared_ptr< udp::socket > > {
    inline void Handle( shared_ptr < tcp::socket > _tcp_socket
                      , shared_ptr< udp::socket > _udp_socket) override {
      std::cout << "CONNECTION ASKDJSKDN\n";
    }
  };
  shared_ptr < ConnectionHandler > m_connection_handler;
  Engine::Network::Gateway_Both * m_gateway = nullptr;
};

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
