#ifndef ENGINE_GAME_ICONTROLLER_HPP_
#define ENGINE_GAME_ICONTROLLER_HPP_

#include "Engine/Types.h"
#include "Engine/Container/Buffer.hpp"

namespace Engine {
namespace Game {
template < class Command >
class IController : public NonCopyable {
public:
  const uint32 id;
  Engine::Container::Buffer < Command > m_command_buffer;

protected:
  inline IController(uint32 _command_buffer_size, uint32 _id)
      : id(_id)
      , m_command_buffer(Engine::Container::Buffer < Command >(_command_buffer_size)) { }
  inline virtual ~IController(void) { };
};
}
}

#endif