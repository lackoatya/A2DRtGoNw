#ifndef P3A_CORE_MENU_H_
#define P3A_CORE_MENU_H_

#include "Engine/Types.h"
#include "Engine/Processor/DeterministicUpdater.hpp"
#include "Engine/Processor/Blocked.hpp"

#include "P3A/CoreResult.h"
#include "P3A/Graphics/MenuRenderer.h"

namespace P3A {
namespace Core {
class Menu {
  private:
    typedef P3A::CoreResult Result;
    typedef P3A::Graphics::MenuRenderer Renderer;

    typedef Engine::Processor::DeterministicUpdater<Renderer, Result> Updater;
    typedef Engine::Processor::Blocked<Updater, Renderer, Result> Processor;

  public:
    Menu(P3A::Graphics::GraphicsContext * _context);
    virtual ~Menu(void);

    inline Result Run(void) { return processor_.Run(); }

  private:
    Renderer * renderer_ = nullptr;
    Updater updater_;
    Processor processor_;
};
}
}

#endif