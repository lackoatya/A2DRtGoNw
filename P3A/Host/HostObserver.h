#ifndef P3A_HOST_HOST_OBSERVER_H_
#define P3A_HOST_HOST_OBSERVER_H_

#include "Engine/Types.h"

#include "P3A/CoreResult.h"
#include "P3A/Game/HeroBase.h"
#include "P3A/Graphics/GameObserverInterface.hpp"
#include "P3A/Host/HostSnapshot.h"

namespace P3A {
namespace Host {
typedef Graphics::GameObserverInterface < HostSnapshot, Game::Hero, CoreResult > ObserverInterface;
class HostObserver : public ObserverInterface {
  public:
    HostObserver( real32 const& _interval
                , Game::Hero * _observed
                , Graphics::GraphicsContext * _graphics_context
                , Graphics::GameArtSource * _art_source
                , Engine::Container::IntervalBuffer < HostSnapshot > * _state_buffer);
    inline virtual ~HostObserver(void) = default;

  protected:
    // TODO Use KeyBindings!
    bool pressed[6];
    uint32 inp_cnt = 0;
    int32 last_direction = -1;

    void Render(void);
    void Render_Hero(const Game::HeroState * _current, const Game::HeroState * _next);

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
#endif