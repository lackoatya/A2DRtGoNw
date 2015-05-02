#ifndef P3A_HOST_HOST_CORE_H_
#define P3A_HOST_HOST_CORE_H_

#include "Engine/Types.h"
#include "Engine/Network/Gateway.h"
#include "Engine/Processor/ThreadedService.h"

#include "P3A/CoreResult.h"
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/GameArtSource.h"
#include "P3A/Host/HostCore_Lobby.h"
#include "P3A/Host/HostCore_Game.h"

namespace P3A {
namespace Host {
class HostCore : public NonCopyable {
public:
  HostCore( Graphics::GraphicsContext * _context
          , Graphics::GameArtSource * _art_source );
  virtual ~HostCore(void);

  CoreResult Run(void);

private:
  Graphics::GraphicsContext * m_context = nullptr;
  Graphics::GameArtSource * m_art_source = nullptr;

  Engine::Processor::ThreadedService m_service;
  Engine::Network::Gateway m_gateway;

  // shared_ptr < Core_Configurator > m_configurator = nullptr;
  // 
  shared_ptr < Core_Lobby > m_lobby = nullptr;
  Engine::Processor::Blocked < LobbyResult > m_lobby_process = nullptr;
  shared_ptr < Core_Game > m_game = nullptr;
  Engine::Processor::Blocked < GameResult > m_game_process = nullptr;
};
}
}

#endif