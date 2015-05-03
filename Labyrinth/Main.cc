#include "Labyrinth/Graphics/GameArtSource.h"
#include "Labyrinth/Graphics/GraphicsContext.h"

#include "P3A/CoreResult.h"
// #include "P3A/Sole/SoleCore.h"
#include "Labyrinth/Menu/MenuCore.h"
#include "Labyrinth/Host/HostCore.h"

int main(void) {
  Labyrinth::Graphics::GraphicsContext graphics(1024, 768);

  Labyrinth::CoreResult state(Labyrinth::CoreState::MENU);
  while (state.result() != P3A::CoreState::EXIT) {
    switch (state.result()) {
      case P3A::CoreState::MENU: {
        P3A::Menu::MenuCore menu(&graphics);
        state = menu.Run();
      } continue;

      case P3A::CoreState::SOLE: {
        /*P3A::Graphics::GameArtSource art_source;
        P3A::Sole::SoleCore sole(&graphics, &art_source);
        state = sole.Run();*/
      } continue;

      case P3A::CoreState::HOST: {
        P3A::Graphics::GameArtSource art_source;
        P3A::Host::HostCore host(&graphics, &art_source);
        state = host.Run();
      } continue;

      default: {
        assert(false && "Unknown CoreState! ");
      } return 0;
    }
  }

  return 0;
}