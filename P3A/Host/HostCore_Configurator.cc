#include "P3A/Host/HostCore_Configurator.h"

namespace P3A {
namespace Host {
Core_Configurator::Core_Configurator(void) {
}

ConfiguratorResult Core_Configurator::Update(void) {
  return ConfiguratorState::CONTINUE;
}

void Core_Configurator::Render(void) {
}

void Core_Configurator::HandleInput(void) {
}

Core_Configurator::~Core_Configurator(void) {
}
}
}