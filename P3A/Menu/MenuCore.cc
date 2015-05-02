#include "P3A/Menu/MenuCore.h"

namespace P3A {
namespace Menu {
MenuCore::MenuCore(Graphics::GraphicsContext * _context)
    : m_renderer(new MenuRenderer(1.f / 60.f, _context))
    , m_updater(new Engine::Updater::Deterministic < CoreResult >(m_renderer))
    , m_processor(m_updater) {
}

MenuCore::~MenuCore() {
  delete m_renderer;
  m_renderer = nullptr;
}
}
}