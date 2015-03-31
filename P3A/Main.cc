#include <assert.h>

#include "P3A/CoreResult.h"
#include "P3A/Core/Sole.h"
#include "P3A/Core/Menu.h"
#include "P3A/Graphics/GraphicsContext.h"

int main(void) {
  P3A::Graphics::GraphicsContext graphics(1024, 768);

  P3A::CoreResult state(P3A::CoreState::MENU);
  while (state.result() != P3A::CoreState::EXIT) {
    switch (state.result()) {
      case P3A::CoreState::MENU: {
        P3A::Core::Menu menu(&graphics);
        state = menu.Run();
      } continue;

      case P3A::CoreState::SOLE: {
        P3A::Core::Sole sole(&graphics);
        state = sole.Run();
      } continue;

      default: {
        assert(false && "Unknown CoreState!");
      } return 0;
    }
  }

  return 0;
}