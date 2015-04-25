#ifndef P3A_GAME_PLAYER_H_
#define P3A_GAME_PLAYER_H_

#include "Engine/Types.h"
#include "Engine/Network/Connection.h"

namespace P3A {
namespace Game {
class Player : public Engine::Network::CommandHandlerInterface {
  public:



    void Handle_TCP(char const* _data, size_t _received);
    void Handle_UDP(char const* _data, size_t _received);
  protected:
};
}
}

#endif