#ifndef P3A_HOST_HOST_CORE_LOBBY_H_
#define P3A_HOST_HOST_CORE_LOBBY_H_

#include "Engine/Types.h"
#include "Engine/Network/Gateway.h"
#include "Engine/Network/Connection.h"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Processor/IResult.hpp"

#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Host {
enum class LobbyState {
  CONTINUE = 0,

  READY,
  ESCAPE,

  Count
};

class LobbyResult : public Engine::Processor::IResult < LobbyState > {
public:
  inline LobbyResult(void)
      : Engine::Processor::IResult < LobbyState >(LobbyState::CONTINUE) {
  }
  inline LobbyResult(LobbyState const& _result)
      : Engine::Processor::IResult < LobbyState >(_result) {
  }

  bool IsValid(void) const { return result() != LobbyState::CONTINUE; }
  // LobbyState NotValid(void) const { return LobbyState::CONTINUE; }
};

class Core_Lobby : public enable_shared_from_this < Core_Lobby >
                 , public Engine::Updater::INonDeterministicProcess < LobbyResult >
                 , public Engine::Network::Gateway::ConnectionHandlerInterface
                 , public Engine::Network::Connection::DisconnectionHandlerInterface {
public:
  struct Slot : public enable_shared_from_this < Slot >
              , public Engine::Network::Connection::CommandHandlerInterface {
  public:
    std::string m_name;
    uint32 m_appearance = 0;

    shared_ptr < Engine::Network::Connection > m_connection = nullptr;

    void Handle_TCP(char const* const _data, size_t _received);
    void Handle_UDP(char const* const _data, size_t _received);
  };

public:
  Core_Lobby(Graphics::GraphicsContext * _context, Engine::Network::Gateway * _gateway);
  virtual ~Core_Lobby(void);

  LobbyResult Process(void);

private:
  Graphics::GraphicsContext * m_graphics = nullptr;

  Mutex m_mutex;
  Engine::Network::Gateway * m_gateway = nullptr;

  void Handle_Connection(shared_ptr < tcp_socket > _socket);
  void Handle_Disconnection(shared_ptr < Engine::Network::Connection > _connection);
  LobbyResult GetResult(void);
};
}
}
#endif