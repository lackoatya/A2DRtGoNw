#include <assert.h>

#include "Engine/Types.h"
#include "Engine/Core/NonDeterministic.hpp"

#include "P3A/Graphics/Menu.h"
#include "P3A/Graphics/Test.h"
#include "P3A/Graphics/GraphicsContext.h"

int main() {
  P3A::Graphics::GraphicsContext graphics(1024, 768);

  P3A::Core::State state(P3A::Core::CoreState::MENU);

  while (state.result() != P3A::Core::CoreState::EXIT) {
    switch (state.result()) {
      case P3A::Core::CoreState::MENU: {
        //P3A::Graphics::Menu menu(graphics);
        //state = Engine::Core::NonDeterministic <P3A::Graphics::Menu, P3A::Core::State>(menu, 1000 / 60);

        P3A::Graphics::Test test(graphics);
        state = Engine::Core::NonDeterministic<P3A::Graphics::Test, P3A::Core::State>(test,
                                                                                      60 / 1000);
      } break;

      default:
        assert(false && "Unknown CoreState!");
    }
  }

  return 0;
}