#include "P3A/Host/HostCore.h"

namespace P3A {
namespace Host {
HostCore::HostCore( Graphics::GraphicsContext * _context
                  , Graphics::GameArtSource * _art_source)
    : m_context(_context)
    , m_art_source(_art_source) {
}

HostCore::~HostCore(void) {
  if (host_core_lobby) {
    delete host_core_lobby;
    host_core_lobby = nullptr;
  }

  if (host_core_game) {
    delete host_core_game;
    host_core_game = nullptr;
  }
}

CoreResult HostCore::Run(void) {
  return CoreState::MENU;
}

// HostCoreLobby

// HostCoreGame
HostCore::HostCoreGame::HostCoreGame( Graphics::GraphicsContext * _context
                                    , Graphics::GameArtSource * _art_source)
    : character(new Game::Hero(0))

    , state_buffer_(new Engine::Container::IntervalBuffer < HostSnapshot >(64, 1.f / 30.f))

    , game_(new HostGame(state_buffer_, character))
    , game_updater_(game_)
    , game_processor_(&game_updater_)

    , renderer_(new HostObserver(1.f / 60.f, character, _context, _art_source, state_buffer_))
    , renderer_updater_(renderer_)
    , renderer_processor_(&renderer_updater_) {
}

HostCore::HostCoreGame::~HostCoreGame(void) {
  delete character;
  character = nullptr;

  delete state_buffer_;
  state_buffer_ = nullptr;

  delete game_;
  game_ = nullptr;

  delete renderer_;
  renderer_ = nullptr;
}
}
}