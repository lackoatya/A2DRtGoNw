#ifndef ENGINE_GAME_IGAME_HPP_
#define ENGINE_GAME_IGAME_HPP_

#include "Engine/Container/Buffer.hpp"
#include "Engine/Container/IntervalBuffer.hpp"
#include "Engine/Updater/Deterministic.hpp"

namespace Engine {
namespace Game {
template < class Snapshot, class Result >
class IGame : public Updater::DeterministicProcessInterface < Result > {
public:
  real32 internal_time = 0.f;

  inline Result Process(void) {
    internal_time += interval_;

    Process_Inputs();
    Process_States();

    return GetResult();
  }

protected:
  Engine::Container::IntervalBuffer < Snapshot > * m_state_buffer = nullptr;

  inline IGame(Engine::Container::IntervalBuffer < Snapshot > * _state_buffer)
      : Engine::Updater::DeterministicProcessInterface < Result >(_state_buffer->interval())
      , m_state_buffer(_state_buffer) { }
  inline virtual ~IGame(void) { };

  virtual void Process_Inputs(void) = 0;
  virtual void Process_States(void) = 0;

  virtual Result GetResult(void) = 0;
};
}
}

#endif