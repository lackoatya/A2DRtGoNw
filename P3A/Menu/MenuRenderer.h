#ifndef P3A_MENU_MENU_RENDERER_H_
#define P3A_MENU_MENU_RENDERER_H_

#include "Engine/Types.h"
#include "Engine/Processor/Deterministicupdater.hpp"

#include "P3A/CoreResult.h"
#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Menu {
class MenuRenderer : public NonCopyable,
                     public Engine::Processor::DeterministicProcessInterface<CoreResult> {
  public:
    enum class Keys {
      UP = 0,
      DOWN,
      ESCAPE,

      Count
    };

  public:
    explicit MenuRenderer(real32 const& _interval, Graphics::GraphicsContext * _context);
    inline virtual ~MenuRenderer(void) = default;

    P3A::CoreResult Process(void);

  private:
    uint32 selected_option_ = 0;
    CoreResult result_ = P3A::CoreResult(P3A::CoreState::CONTINUE);

    // Engine::Graphics::KeyHandler<Keys> bindings_; //(std::array < Keys, (uint32)Keys::Count > { KeyHandler< Keys, (uint32)Keys::Count >(Keys::UP, GLFW_KEY_W)});
    //bool keys[(uint32)Keys::Count];

    Graphics::GraphicsContext * context_;  

    void Render(void);

    void HandleKeys(void);
    void HandleMouse(void);
};
}
}

#endif