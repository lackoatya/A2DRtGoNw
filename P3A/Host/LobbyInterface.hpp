#ifndef ENGINE_NETWORK_LOBBY_INTERFACE_HPP_
#define ENGINE_NETWORK_LOBBY_INTERFACE_HPP_

#include "Engine/Types.h"
#include "Engine/Network/Gateway.h"

namespace Engine {
namespace Network {
class LobbyInterface : public NonCopyable
                     , public Engine::Network::ConnectionHandlerInterface {
  public:
    const uint32 m_players_max;

    void Handle_Connection(shared_ptr < tcp_socket > _socket);

  protected:
    Engine::Network::Gateway * m_gateway = nullptr;
    
    inline LobbyInterface(Engine::Network::Gateway * _gateway)
        : m_gateway(_gateway)
        , m_players_max(m_gateway->m_configuration.connections_max) {
      assert(_gateway);
    }

    inline ~LobbyInterface(void) = default;
};
}
}

#endif