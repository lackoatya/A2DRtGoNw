#ifndef P3A_MENU_MENU_CORE_H_
#define P3A_MENU_MENU_CORE_H_

#include "Engine/Platform.h"
#include "Engine/Updater/Deterministic.hpp"
#include "Engine/Processor/Blocked.hpp"

#include "P3A/CoreResult.h"
#include "P3A/Menu/MenuRenderer.h"

namespace P3A {
namespace Menu {
class MenuCore {
  public:
    MenuCore(Graphics::GraphicsContext * _context);
    virtual ~MenuCore(void);

    CoreResult Run(void) { return m_processor.Run(); }

  private:
    MenuRenderer * m_renderer = nullptr;
    Engine::Updater::Deterministic < CoreResult > * m_updater = nullptr;
    Engine::Processor::Blocked < CoreResult > m_processor;
};
}
}

#endif