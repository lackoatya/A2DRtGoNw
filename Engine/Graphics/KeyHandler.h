#ifndef ENGINE_GRAPHICS_KEYHANDLER_H_
#define ENGINE_GRAPHICS_KEYHANDLER_H_

#include <vector>

#include "Engine/Types.h"
#include "Engine/Graphics/ContextBase.h"

namespace Engine {
namespace Graphics {
template <class Index>
class KeyHandler {
  public:
    struct KeyBinding
    {
      public:
        const Index index;
        const uint32 key;

        uint8 state = false;

        inline KeyBinding(Index const& _index, uint32 const& _key) : index(_index), key(_key) { }
        inline KeyBinding(void) = delete;
        inline KeyBinding(KeyBinding const& _other)
            : index(_other.index), key(_other.key),
              state(_other.state) { }
        inline KeyBinding(KeyBinding && _other)
            : index(_other.index), key(_other.key),
              state(_other.state) { }
        inline KeyBinding & operator=(KeyBinding && _other) = delete;
        inline KeyBinding & operator=(KeyBinding const& _other) = delete;
        inline virtual ~KeyBinding(void) = default;
    };

  public:
    KeyHandler(std::vector<KeyBinding> const& _state)
        : state(_state) { }
    inline KeyHandler(void) = delete;
    inline KeyHandler(KeyHandler &&& _other) = delete;
    inline KeyHandler(KeyHandler const& _other) = delete;
    inline KeyHandler & operator=(KeyHandler && _other) = delete;
    inline KeyHandler & operator=(KeyHandler const& _other) = delete;
    inline virtual ~KeyHandler() = default;

    inline void Process(Engine::Graphics::Context_Base const& _context) {
      for (KeyBinding & binding : state) {
	binding.state = (glfwGetKey(_context.window, GLFW_KEY_W) == GLFW_PRESS) ? 1 : 0;
      }
    }

    // TODO AddBinding/RemoveBinding.. Acessors, mutators..

  private:
    std::vector<KeyBinding> state;
};
}
}

#endif