//#include "Labyrinth/Graphics/GameArtSource.h"
#include "Labyrinth/Graphics/GL/Context.h"

#include "P3A/CoreResult.h"
// #include "P3A/Sole/SoleCore.h"
#include "Labyrinth/Menu/Core.h"
// #include "Labyrinth/Host/HostCore.h"

#include "Engine/Container/Buffer.hpp"

int main(void) {
  Labyrinth::Graphics::IContext * context = nullptr;
  
  if ("OpenGL" == "OpenGL") {
    context = new Labyrinth::Graphics::GL::Context(1024, 768);
  } else {
    assert( false );
  }

  Labyrinth::CoreResult state(Labyrinth::CoreState::MENU);
  while (state.result() != Labyrinth::CoreState::EXIT) {
    switch (state.result()) {
      case Labyrinth::CoreState::MENU: {
        Labyrinth::Menu::Core menu(1.f / 60.f, context);
        state = menu.Run();
      } continue;

      case Labyrinth::CoreState::SOLE: {
        /*P3A::Graphics::GameArtSource art_source;
        P3A::Sole::SoleCore sole(&graphics, &art_source);
        state = sole.Run();*/
      } continue;

      case Labyrinth::CoreState::HOST: {
        /*Labyrinth::Graphics::GameArtSource art_source;
        Labyrinth::Host::HostCore host(&graphics, &art_source);
        state = host.Run();*/
      } continue;

      default: {
        assert(false && "Unknown CoreState! ");
      } return 0;
    }
  }

  return 0;
}
