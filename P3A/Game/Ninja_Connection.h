#ifndef P3A_GAME_NINJA_CONNECTION_H_
#define P3A_GAME_NINJA_CONNECTION_H_

#include "Engine/Types.h"
#include "Engine/Network/Connection.h"

#include "P3A/Game/Ninja.h"

namespace P3A {
namespace Game {
class Ninja_Connection : public Ninja {
public:
  inline explicit Ninja_Connection( uint32 _command_buffer_size
                                  , uint32 _id
                                  , shared_ptr < Engine::Network::Connection > _connection)
      : Ninja(_command_buffer_size, _id)
      , m_connection(_connection) { }
  inline virtual ~Ninja_Connection(void) { };

private:
  shared_ptr < Engine::Network::Connection > m_connection = nullptr;
};
}
}

#endif