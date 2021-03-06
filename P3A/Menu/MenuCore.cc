#include "Labyrinth/Menu/MenuCore.h"

namespace Labyrinth {
namespace Menu {
Core::Core(Graphics::IContext * _context)
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