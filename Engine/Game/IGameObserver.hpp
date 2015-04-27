#ifndef ENGINE_GAME_IGAMEOBSERVER_HPP_
#define ENGINE_GAME_IGAMEOBSERVER_HPP_

#include "Engine/Types.h"
#include "Engine/Updater/NonDeterministic.hpp"
#include "Engine/Container/IntervalBuffer.hpp"

namespace Engine {
namespace Game {
template < class Snapshot, class Observed, class Result >
class IGameObserver : public NonCopyable
                    , public Updater::NonDeterministicProcessInterface < Result > {
public:
  IGameObserver(real32 const& _interval
                , Observed * _observed
                , Engine::Container::IntervalBuffer < Snapshot > * _state_buffer)
      : Engine::Updater::NonDeterministicProcessInterface < Result >(_interval)
      , m_observed(_observed)
      , m_state_buffer(_state_buffer) { }
  inline virtual ~IGameObserver(void) { }

  virtual Result Process(real32 const& _elapsed_time) {
    m_internal_time += _elapsed_time;

    Render();
    HandleInput();

    return GetResult();
  }

protected:
  real32 m_internal_time = 0.f;

  Observed * m_observed = nullptr;

  Engine::Container::IntervalBuffer < Snapshot > * m_state_buffer = nullptr;

  virtual void Render(void) = 0;
  virtual void HandleInput(void) = 0;
  virtual Result GetResult(void) = 0;
};
}
}

#endif*/