//#include "Labyrinth/Graphics/GameArtSource.h"
#include "Labyrinth/Graphics/GL/Context.h"

#include "P3A/CoreResult.h"
// #include "P3A/Sole/SoleCore.h"
#include "Labyrinth/Menu/Core.h"
// #include "Labyrinth/Host/HostCore.h"

#include "Engine/Container/Buffer.hpp"

shared_ptr < Engine::Container::Buffer < uint32 > > m_buffer(make_shared(Engine::Container::Buffer < uint32 >, uint32)(8));
Engine::Container::Buffer_Proxy < uint32 > m_buffer_proxy(m_buffer);

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
