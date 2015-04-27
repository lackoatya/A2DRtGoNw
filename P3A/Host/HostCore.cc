#include "P3A/Host/HostCore.h"

namespace P3A {
namespace Host {
HostCore::HostCore( Graphics::GraphicsContext * _context
                  , Graphics::GameArtSource * _art_source)
    : m_context(_context)
    , m_art_source(_art_source)

    , m_service()
    , m_gateway(Engine::Network::Gateway::Configuration(3, 1425), &m_service) {
}

HostCore::~HostCore(void) {
  m_gateway.Shutdown();
}

CoreResult HostCore::Run(void) {
  boost::system::error_code error = m_gateway.Bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("192.168.1.110"), 1425));

  return CoreState::MENU;
}

// HostCoreLobby
HostCore::HostCoreLobby::HostCoreLobby(Graphics::GraphicsContext * _context
                            , Engine::Network::Gateway * _gateway)
    : m_gateway(_gateway)
    , m_slots( new Slot[m_gateway->configuration.connections_max + 1]) {

}

// HostCoreGame
HostCore::HostCoreGame::HostCoreGame( Graphics::GraphicsContext * _context
                                    , Graphics::GameArtSource * _art_source)
    : state_buffer_(new Engine::Container::IntervalBuffer < HostSnapshot >(64, 1.f / 30.f))

    , game_(new HostGame(state_buffer_))
    , game_updater_(game_)
    , game_processor_(&game_updater_)

    , renderer_(new HostObserver(1.f / 60.f, nullptr, _context, _art_source, state_buffer_))
    , renderer_updater_(renderer_)
    , renderer_processor_(&renderer_updater_) {
}

HostCore::HostCoreGame::~HostCoreGame(void) {
  delete state_buffer_;
  state_buffer_ = nullptr;

  delete game_;
  game_ = nullptr;

  delete renderer_;
  renderer_ = nullptr;
}
}
}