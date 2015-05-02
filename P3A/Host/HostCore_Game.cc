#include "P3A/Host/HostCore_Game.h"

namespace P3A {
namespace Host {
Core_Game::Core_Game( Graphics::GraphicsContext * _context
                    , Graphics::GameArtSource * _art_source)
    : m_state_buffer(new Engine::Container::IntervalBuffer < HostSnapshot >(64, 1.f / 30.f))

    , m_game(new HostGame(m_state_buffer))
    , m_game_updater(m_game)
    , m_game_processor(&m_game_updater)

    , m_renderer(new HostObserver(1.f / 60.f, nullptr, _context, _art_source, m_state_buffer))
    , m_renderer_updater(m_renderer)
    , m_renderer_processor(&m_renderer_updater) {
}

CoreResult Core_Game::Run(void) {
}

Core_Game::~Core_Game(void) {
  delete m_state_buffer;
  m_state_buffer = nullptr;

  delete m_game;
  m_game = nullptr;

  delete m_renderer;
  m_renderer = nullptr;
}
}
}
