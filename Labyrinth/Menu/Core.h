#ifndef LABYRINTH_MENU_CORE_H_
#define LABYRINTH_MENU_CORE_H_

#include "Engine/Types.h"
#include "Engine/Updater/Deterministic.hpp"
#include "Engine/Processor/Blocked.hpp"

#include "Labyrinth/CoreResult.h"
#include "Labyrinth/Graphics/IContext.h"
#include "Labyrinth/Menu/Renderer.h"

namespace Labyrinth {
namespace Menu {
class Core {
public:
  Core(real32 const& _interval, Graphics::IContext * _context);
  virtual ~Core(void);

  CoreResult Run(void) { return m_processor.Run(); }

private:
  Renderer * m_renderer = nullptr;
  Engine::Updater::Deterministic < CoreResult > * m_updater = nullptr;
  Engine::Processor::Blocked < CoreResult > m_processor;
};
}
}

#endif