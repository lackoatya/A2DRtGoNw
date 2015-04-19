#ifndef P3A_GAME_GAME_INTERFACE_H_
#define P3A_GAME_GAME_INTERFACE_H_

#include "Engine/Container/Buffer.hpp"
#include "Engine/Container/IntervalBuffer.hpp"
#include "Engine/Updater/Deterministic.hpp"

namespace P3A {
namespace Game {
template < class Snapshot, class Result >
class GameInterface : public Engine::Updater::DeterministicProcessInterface < Result > {
  public:
    real32 internal_time = 0.f;

    GameInterface(Engine::Container::IntervalBuffer < Snapshot > * _state_buffer)
        : Engine::Updater::DeterministicProcessInterface < Result >( _state_buffer->interval() )
        , state_buffer_(_state_buffer) { }
    inline virtual ~GameInterface(void) = default;

    Result Process(void) {
      internal_time += interval_;
      Process_Inputs();
      Process_States();

      return GetResult();
    }

  protected:
    Engine::Container::IntervalBuffer < Snapshot > * state_buffer_ = nullptr;

    virtual void Process_Inputs(void) = 0;
    virtual void Process_States(void) = 0;
    virtual Result GetResult(void) = 0;
};
}
}

#endif