#ifndef P3A_GRAPHICS_MENU_H_
#define P3A_GRAPHICS_MENU_H_

#include "Engine/Types.h"
// #include "Engine/Graphics/KeyHandler.h"
#include "Engine/Core/ProcessableInterface.h"

#include "P3A/Core/State.h"
#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Graphics {
class Menu : public Engine::Core::ProcessableInterface<P3A::Core::State> {
  public:
    enum class Keys {
      UP = 0,
      DOWN,
      ESCAPE,

      Count
    };

  public:
    explicit Menu(P3A::Graphics::GraphicsContext & _context);
    inline Menu(void) = delete;
    inline Menu(Menu && _other) = delete;
    inline Menu(Menu const& _other) = delete;
    inline Menu & operator=(Menu && _other) = delete;
    inline Menu & operator=(Menu const& _other) = delete;
    inline virtual ~Menu(void) = default;

    void Render(void);

    P3A::Core::State Process(void);

    void HandleKeys(void);
    void HandleMouse(void);

  private:
    uint32 selected_option_ = 0;

    // Engine::Graphics::KeyHandler<Keys> bindings_; //(std::array < Keys, (uint32)Keys::Count > { KeyHandler< Keys, (uint32)Keys::Count >(Keys::UP, GLFW_KEY_W)});
    //bool keys[(uint32)Keys::Count];

    P3A::Graphics::GraphicsContext & context_;  
};
}
}

#endif