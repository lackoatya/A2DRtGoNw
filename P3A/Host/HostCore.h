#ifndef P3A_HOST_HOST_CORE_H_
#define P3A_HOST_HOST_CORE_H_

#include "Engine/Types.h"
#include "Engine/Container/Buffer.hpp"
#include "Engine/Container/IntervalBuffer.hpp"
#include "Engine/Updater/Deterministic.hpp"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/ThreadedBlocked.hpp"
#include "Engine/Processor/ThreadedService.h"
#include "Engine/Network/Gateway.h"
#include "Engine/Network/Connection.h"

#include "P3A/CoreResult.h"
#include "P3A/GameResult.h"
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/GameArtSource.h"
#include "P3A/Host/HostGame.h"
#include "P3A/Host/HostLobby.h"
#include "P3A/Host/HostObserver.h"
#include "P3A/Host/HostSnapshot.h"

namespace P3A {
namespace Host {
class HostCore : public NonCopyable {
public:
  HostCore( Graphics::GraphicsContext * _context
          , Graphics::GameArtSource * _art_source );
  virtual ~HostCore(void);

  CoreResult Run(void);

private:
  class HostCoreLobby : public enable_shared_from_this < HostCoreLobby >
                      , public Engine::Network::Gateway::ConnectionHandlerInterface
                      // , public Engine::Network::Connection::CommandHandlerInterface
                      , public Engine::Network::Connection::DisconnectionHandlerInterface {
  public:
    HostCoreLobby(Graphics::GraphicsContext * _context, Engine::Network::Gateway * _gateway);

    CoreResult Run(void);

    void Handle_Connection(shared_ptr < tcp_socket > _socket);
    // void Handle_TCP(char const* const _data, size_t _received);
    // void Handle_UDP(char const* const _data, size_t _received);
    void Handle_Disconnection(shared_ptr < Engine::Network::Connection > _connection);

    struct Slot {
      public:
        Mutex m_mutex;

        std::string m_name;
        uint32 m_appearance = 0;

        shared_ptr < Engine::Network::Connection > m_connection = nullptr;
    } * m_slots = nullptr;

  private:
    Engine::Network::Gateway * m_gateway = nullptr;
  };

  class HostCoreGame : public Engine::Network::Gateway::ConnectionHandlerInterface  {
  private:
    typedef Engine::Updater::Deterministic < GameResult > GameUpdater;
    typedef Engine::Processor::ThreadedBlocked < GameUpdater, GameResult > GameProcessor;

    typedef Engine::Updater::NonDeterministic < CoreResult > RendererUpdater;
    typedef Engine::Processor::Blocked < RendererUpdater, CoreResult > RendererProcessor;

  public:
    HostCoreGame(Graphics::GraphicsContext * _context
                  , Graphics::GameArtSource * _art_source);
    virtual ~HostCoreGame(void);

    CoreResult Run(void);

  private:
    Engine::Network::Gateway * m_gateway = nullptr;
    Engine::Container::IntervalBuffer < HostSnapshot > * state_buffer_ = nullptr;

    HostGame * game_ = nullptr;
    GameUpdater game_updater_;
    GameProcessor game_processor_;

    HostObserver * renderer_ = nullptr;
    RendererUpdater renderer_updater_;
    RendererProcessor renderer_processor_;
  };

  Graphics::GraphicsContext * m_context = nullptr;
  Graphics::GameArtSource * m_art_source = nullptr;

  Engine::Processor::ThreadedService m_service;
  Engine::Network::Gateway m_gateway;

  shared_ptr < HostCoreLobby > m_host_core_lobby;
  shared_ptr < HostCoreGame > m_host_core_game = nullptr;
};
}
}

#endif