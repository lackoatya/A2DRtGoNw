#ifndef P3A_GAME_NINJA_AGENT_H_
#define P3A_GAME_NINJA_AGENT_H_

#include "Engine/Types.h"

#include "P3A/Game/Ninja.h"

namespace P3A {
namespace Game {
class Ninja_Agent : public Ninja {
public:
  inline explicit Ninja_Agent( uint32 _command_buffer_size
                             , uint32 _id)
      : Ninja(_command_buffer_size, _id) { }
  inline virtual ~Ninja_Agent(void) { };

private:
};
}
}

#endif