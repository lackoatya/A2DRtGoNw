#ifndef P3A_HOST_HOST_CORE_GAME_H_
#define P3A_HOST_HOST_CORE_GAME_H_

#include "Engine/Types.h"
#include "Engine/Container/IntervalBuffer.hpp"
#include "Engine/Network/Gateway.h"
#include "Engine/Network/Connection.h"
#include "Engine/Updater/Deterministic.hpp"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Processor/Blocked.hpp"
#include "Engine/Processor/ThreadedBlocked.hpp"

#include "P3A/CoreResult.h"
#include "P3A/GameResult.h"
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/GameArtSource.h"
#include "P3A/Host/HostGame.h"
#include "P3A/Host/HostObserver.h"
#include "P3A/Host/HostSnapshot.h"

namespace P3A {
namespace Host {
class Core_Game : public Engine::Network::Gateway::ConnectionHandlerInterface  {
public:
  class ConnectionHandler : public Engine::Network::Connection::CommandHandlerInterface {
  public:
    void Handle_TCP(char const* const _data, size_t _received);
    void Handle_UDP(char const* const _data, size_t _received);
  }; // ConnectionHandler

public:
  Core_Game(Graphics::GraphicsContext * _context, Graphics::GameArtSource * _art_source);
  virtual ~Core_Game(void);

  CoreResult Run(void);

private:
  Engine::Network::Gateway * m_gateway = nullptr;
  Engine::Container::IntervalBuffer < HostSnapshot > * m_state_buffer = nullptr;

  HostGame * m_game = nullptr;
  Engine::Updater::Deterministic < GameResult > m_game_updater;
  Engine::Processor::ThreadedBlocked < GameResult > m_game_processor;

  HostObserver * m_renderer = nullptr;
  Engine::Updater::NonDeterministic < CoreResult > m_renderer_updater;
  Engine::Processor::Blocked < CoreResult > m_renderer_processor;
};
}
}

#endif
