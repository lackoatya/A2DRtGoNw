#include "P3A/Menu/MenuCore.h"

namespace P3A {
namespace Menu {
MenuCore::MenuCore(Graphics::GraphicsContext * _context)
    : renderer_(new MenuRenderer(1.f / 60.f, _context))
    , updater_(renderer_)
    , processor_(&updater_) {
}

MenuCore::~MenuCore() {
  delete renderer_;
  renderer_ = nullptr;
}
}
}