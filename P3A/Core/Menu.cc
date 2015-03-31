#include "P3A/Core/Menu.h"

P3A::Core::Menu::Menu(P3A::Graphics::GraphicsContext * _context)
  : renderer_(new P3A::Graphics::MenuRenderer(_context)),
    updater_(renderer_, 1.f / 60.f),
    processor_(&updater_) {
}

P3A::Core::Menu::~Menu() {
  delete renderer_;
  renderer_ = nullptr;
}