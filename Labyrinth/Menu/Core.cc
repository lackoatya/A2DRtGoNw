#include "Labyrinth/Menu/Core.h"

namespace Labyrinth {
namespace Menu {
Core::Core(real32 const& _interval, Graphics::IContext * _context)
    : m_renderer(new Renderer(_interval, _context))
    , m_updater(new Engine::Updater::Deterministic < CoreResult >(m_renderer))
    , m_processor(m_updater) {
  assert( _context );
}

Core::~Core(void) {
  delete m_renderer;
  m_renderer = nullptr;
}
}
}