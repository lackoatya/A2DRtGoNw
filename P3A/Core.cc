#include <assert.h>

#include "BOOST/bind.hpp"
#include "BOOST/thread.hpp"

#include "Engine/Types.h"
#include "Engine/Core/Deterministic.hpp"
#include "Engine/Core/NonDeterministic.hpp"
#include "Engine/Physics/Reality.h"

#include "P3A/Game/World.h"
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

        P3A::Game::World world(1.f / 60.f);
        P3A::Graphics::Test test(graphics);

        boost::thread updater = boost::thread(boost::bind(
            Engine::Core::Deterministic< P3A::Game::World, P3A::Core::State >, &world, 1.f / 60.f));
        state = Engine::Core::NonDeterministic<P3A::Graphics::Test, P3A::Core::State>(&test, 1.f / 60.f);
        updater.interrupt();
        //state = Engine::Core::Interpolated<P3A::Game::World, P3A::Graphics::Test, P3A::Core::State>
        //    (world, test, 60.f / 1000.f);
        //state = Engine::Core::NonDeterministic<P3A::Graphics::Test, P3A::Core::State>(test,
        //                                                                              60 / 1000);
        //state = Engine::Core::
      } break;

      default: assert(false && "Unknown CoreState!");
    }
  }

  return 0;
}