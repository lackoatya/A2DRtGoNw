#ifndef P3A_SOLE_SOLE_OBSERVER_H_
#define P3A_SOLE_SOLE_OBSERVER_H_

#include "Engine/Types.h"

#include "P3A/CoreResult.h"
#include "P3A/Game/HeroBase.h"
#include "P3A/Graphics/GameObserverInterface.hpp"
#include "P3A/Sole/SoleSnapshot.h"

namespace P3A {
namespace Sole {
typedef Graphics::GameObserverInterface < SoleSnapshot, Game::Hero, CoreResult > ObserverInterface;
class SoleObserver : public ObserverInterface {
  public:
    SoleObserver(real32 const& _interval
               , Game::Hero * _observed
               , Graphics::GraphicsContext * _graphics_context
               , Graphics::GameArtSource * _art_source
               , Engine::Container::IntervalBuffer < SoleSnapshot > * _state_buffer)
        : ObserverInterface(_interval, _observed, _graphics_context, _art_source, _state_buffer) { }
    inline virtual ~SoleObserver(void) = default;

  protected:
    bool clicked[2];

    void Render(void);
    void Render_Hero(const Game::HeroState * _current, const Game::HeroState * _next);

    void HandleInput(void);

    inline CoreResult GetResult(void) {
      if (graphics_context_->ShouldClose()) return CoreState::EXIT;
      else return CoreState::CONTINUE;
    }
  };
}
}

#endif