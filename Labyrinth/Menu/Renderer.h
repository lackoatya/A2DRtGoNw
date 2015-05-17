#ifndef LABYRINTH_MENU_RENDERER_H_
#define LABYRINTH_MENU_RENDERER_H_

#include "Engine/Types.h"
#include "Engine/Updater/Deterministic.hpp"

#include "Labyrinth/CoreResult.h"
#include "Labyrinth/Graphics/IContext.h"

namespace Labyrinth {
namespace Menu {
class Renderer : public Engine::Updater::IDeterministicProcess < CoreResult > {
public:
  Renderer(real32 const& _interval, Graphics::IContext * _context);
  inline virtual ~Renderer(void) = default;

  CoreResult Process(void);

private:
  uint32 m_selected_option = 0;
  CoreResult m_result = CoreResult(CoreState::CONTINUE);

  Graphics::IContext * m_context = nullptr;

  void Render(void);

  void HandleKeys(void);
  void HandleMouse(void);
};
}
}

#endif