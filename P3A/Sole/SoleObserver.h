/*#ifndef P3A_SOLE_SOLE_OBSERVER_H_
#define P3A_SOLE_SOLE_OBSERVER_H_

#include "Engine/Platform.h"

#include "P3A/CoreResult.h"
#include "P3A/Graphics/GameObserverInterface.hpp"
#include "P3A/Sole/SoleSnapshot.h"

namespace P3A {
namespace Sole {
typedef Graphics::GameObserverInterface < SoleSnapshot, void, CoreResult > ObserverInterface;
class SoleObserver : public ObserverInterface {
  public:
    SoleObserver(real32 const& _interval
              //, Game::Hero * _observed
               , Graphics::GraphicsContext * _graphics_context
               , Graphics::GameArtSource * _art_source
               , Engine::Container::IntervalBuffer < SoleSnapshot > * _state_buffer);
    inline virtual ~SoleObserver(void) = default;

  protected:
    // TODO Use KeyBindings!
    bool pressed[6];
    uint32 inp_cnt = 0;
    int32 last_direction = -1;

    void Render(void);
    // void Render_Hero(const Game::HeroState * _current, const Game::HeroState * _next);

    void HandleInput(void);
    void Handle_Keys(void);
    void Handle_Mouse(void);

    inline CoreResult GetResult(void) {
      if (graphics_context_->ShouldClose()) return CoreState::EXIT;
      else return CoreState::CONTINUE;
    }
};
}
}

#endif*/