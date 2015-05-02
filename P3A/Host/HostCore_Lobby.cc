#include "P3A/Host/HostCore_Lobby.h"

namespace P3A {
namespace Host {
Core_Lobby::Core_Lobby( Graphics::GraphicsContext * _context
                      , Engine::Network::Gateway * _gateway)
    : Engine::Updater::INonDeterministicProcess < LobbyResult >(1.f / 60.f)
    , m_gateway(_gateway)
    /*, m_slots(new Slot[m_gateway->configuration.connections_max + 1]) */{
}

LobbyResult Core_Lobby::Process(void) {
  return GetResult();
}

void Core_Lobby::Handle_Connection(shared_ptr < tcp_socket > _socket) {
}

void Core_Lobby::Handle_Disconnection(shared_ptr < Engine::Network::Connection > _connection) {
}

LobbyResult Core_Lobby::GetResult(void) {
  return LobbyState::CONTINUE;
}

Core_Lobby::~Core_Lobby(void) {
}

}
}