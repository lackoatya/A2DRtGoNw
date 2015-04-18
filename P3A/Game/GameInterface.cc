/*#include "P3A/Game/GameBase.h"

namespace P3A {
namespace Game {
GameBase::GameBase(real32 const& _interval, Engine::Container::IntervalBuffer<Snapshot> * _state_buffer,
                   Engine::Container::Buffer<Input> * _input_buffer)
    : Engine::Processor::DeterministicProcessInterface<GameResult>(_interval),
      integrator(Engine::Numerics::SymplecticEulerIntegrator<Engine::Physics::Body<Engine::Physics::AABB>>(interval_)),
      state_buffer_(_state_buffer),
      input_buffer_(_input_buffer) { 
  Snapshot * current = state_buffer_->get_last();
  current->hero_states[0] = Hero(Vector2(0.f, 128.f), Vector2(32.f, -64.f));
  current->hero_state_count = 1;
}

GameResult GameBase::Process(void) {
  internal_time += interval_;

  uint32 last_input = input_buffer_->last();
  while (last_processed_input != last_input) {
    last_processed_input = input_buffer_->next(last_processed_input);
    Process_Input(input_buffer_->get(last_processed_input));
  }

  Snapshot * current = state_buffer_->get_last();
  Snapshot * next = state_buffer_->get_next();

  for (uint32 hero = 0; hero < current->hero_state_count; ++hero) {
    next->hero_states[hero].copy(current->hero_states[hero]);
    integrator.Integrate(current->hero_states[hero].body, &(next->hero_states[hero].body));

    uint32 motions_count = 0;
    for (uint32 motion = 0; motion < current->hero_states[hero].motions_count; ++motion) {
      real32 end = current->hero_states[hero].motions[motion].start_time + current->hero_states[hero].motions[motion].duration;
      if (internal_time < end) {
        ++motions_count;
        next->hero_states[hero].motions[motions_count] = current->hero_states[hero].motions[motion];
      }
    }
    next->hero_states[hero].motions_count = motions_count;
  }

  next->hero_state_count = current->hero_state_count;

  state_buffer_->procede();

  return GameState::CONTINUE;
}

void GameBase::Process_States(void) {

}

void GameBase::Process_States_Heroes(void) {

}

void GameBase::Process_Input(Input * _input) {
  Snapshot * current = state_buffer_->get_last();

  if (_input->Get(Input::Command::JUMP))
    current->hero_states[0].body.set_position(current->hero_states[0].body.position() + Vector2(0.f, 32.f));
}
}
}*/