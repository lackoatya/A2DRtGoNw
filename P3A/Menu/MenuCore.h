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
    typedef Engine::Updater::Deterministic < CoreResult > Updater;
    typedef Engine::Processor::Blocked < Updater, CoreResult > Processor;

  public:
    MenuCore(Graphics::GraphicsContext * _context);
    virtual ~MenuCore(void);

    inline CoreResult Run(void) { return processor_.Run(); }

  private:
    MenuRenderer * renderer_ = nullptr;
    Updater updater_;
    Processor processor_;
};
}
}

#endif