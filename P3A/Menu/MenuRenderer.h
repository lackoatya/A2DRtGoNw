#ifndef P3A_MENU_MENU_RENDERER_H_
#define P3A_MENU_MENU_RENDERER_H_

#include "Engine/Types.h"
#include "Engine/Updater/Deterministic.hpp"

#include "P3A/CoreResult.h"
#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Menu {
class MenuRenderer : public NonCopyable
                   , public Engine::Updater::IDeterministicProcess < CoreResult > {
  public:
    explicit MenuRenderer(real32 const& _interval, Graphics::GraphicsContext * _context);
    inline virtual ~MenuRenderer(void) = default;

    CoreResult Process(void);

  private:
    uint32 m_selected_option = 0;
    CoreResult m_result = CoreResult(CoreState::CONTINUE);

    Graphics::GraphicsContext * m_context;

    void Render(void);

    void HandleKeys(void);
    void HandleMouse(void);
};
}
}

#endif