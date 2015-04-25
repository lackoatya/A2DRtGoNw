#ifndef P3A_HOST_HOST_LOBBY_H_
#define P3A_HOST_HOST_LOBBY_H_

#include "Engine/Types.h"
#include "Engine/Network/Gateway.h"
#include "Engine/Network/Connection.h"

namespace P3A {
namespace Host{
class HostLobby : public NonCopyable
                , public Engine::Network::Gateway::ConnectionHandlerInterface {
  public:
    const uint32 m_players_max;

    inline HostLobby(Engine::Network::Gateway * _gateway)
        : m_gateway(_gateway)
        , m_players_max(m_gateway->m_configuration.connections_max) {
      assert(_gateway);
    }
    inline ~HostLobby(void) = default;

    void Handle_Connection(shared_ptr < Engine::Network::tcp_socket > _socket);

  private:
    Engine::Network::Gateway * m_gateway = nullptr;

};
}
}

#endif