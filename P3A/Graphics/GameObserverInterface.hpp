#ifndef P3A_GRAPHICS_GAME_OBSERVER_INTERFACE_H_
#define P3A_GRAPHICS_GAME_OBSERVER_INTERFACE_H_

#include "Engine/Types.h"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Container/IntervalBuffer.hpp"

// TODO this is OpenGL GraphicsContext dependant!
#include "P3A/Graphics/GraphicsContext.h"
#include "P3A/Graphics/GameArtSource.h"

namespace P3A {
namespace Graphics {
template < class Snapshot, class Observed, class Result >
class GameObserverInterface : public NonCopyable,
                              public Engine::Updater::NonDeterministicProcessInterface < Result > {
  public:
    real32 internal_time = 0.f;

    // TODO this is OpenGL GraphicsContext dependant!
    GameObserverInterface(real32 const& _interval
                        , Observed * _observed
                        , GraphicsContext * _graphics_context
                        , GameArtSource * _art_source
                        , Engine::Container::IntervalBuffer < Snapshot > * _state_buffer)
        : Engine::Updater::NonDeterministicProcessInterface < Result >(_interval)
        , observed_(_observed)
        , graphics_context_(_graphics_context)
        , art_source_(_art_source)
        , state_buffer_(_state_buffer) { }
    inline virtual ~GameObserverInterface(void) = default;

    virtual Result Process(real32 const& _elapsed_time) {
      internal_time += _elapsed_time;

      // TODO this is OpenGL GraphicsContext dependant!
      graphics_context_->PollEvents();

      Render();
      HandleInput();

      // TODO this is OpenGL GraphicsContext dependant!
      graphics_context_->SwapBuffers();

      return GetResult();
    }

  protected:
    Observed * observed_ = nullptr;

    GraphicsContext * graphics_context_ = nullptr;
    GameArtSource * art_source_ = nullptr;

    Engine::Container::IntervalBuffer < Snapshot > * state_buffer_ = nullptr;

    virtual void Render(void) = 0;
    virtual void HandleInput(void) = 0;
    virtual Result GetResult(void) = 0;
};
}
}

#endif*/