#ifndef P3A_MENU_MENU_CORE_H_
#define P3A_MENU_MENU_CORE_H_

#include "Engine/Types.h"
#include "Engine/Updater/Deterministic.hpp"
#include "Engine/Processor/Blocked.hpp"

#include "P3A/CoreResult.h"
#include "P3A/Menu/MenuRenderer.h"

namespace P3A {
namespace Menu {
class MenuCore : public NonCopyable {
  private:
    typedef CoreResult Result;
    typedef MenuRenderer Renderer;

    typedef Engine::Updater::Deterministic < Renderer, Result > Updater;
    typedef Engine::Processor::Blocked<Updater, Result> Processor;

  public:
  MenuCore(Graphics::GraphicsContext * _context);
  virtual ~MenuCore(void);

    inline Result Run(void) { return processor_.Run(); }

  private:
    Renderer * renderer_ = nullptr;
    Updater updater_;
    Processor processor_;
};
}
}

#endif