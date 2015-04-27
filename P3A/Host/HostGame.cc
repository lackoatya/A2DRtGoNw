#include "P3A/Host/HostGame.h"

namespace P3A {
namespace Host {
void HostGame::Process_Inputs(void) {
  // Process Player

  // Process Connections

  // Process Agents
}

void HostGame::Process_Ninja_Input_Buffer(Game::Ninja * _ninja) {
  /*uint32 last_input = character_->input_buffer.last();
  while (last_character_input != last_input) {
    last_character_input = character_->input_buffer.next(last_character_input);
    // Process_Hero_Input(&(current->character), character_->input_buffer.get(last_character_input));
  }*/

  // Process each unhandled command @ Process_Ninja_Command
}

void HostGame::Process_Ninja_Command(Game::Ninja_State * _state, const Game::Ninja_Command * _command) {
  /*switch (*_input) {
    case Game::HeroInput::MOVE_UP: {
      _current->body.set_velocity(Vector2(0.f, 1.f) * _current->speed);
      // TODO set animation
    } break;

    case Game::HeroInput::MOVE_DOWN: {
      _current->body.set_velocity(Vector2(0.f, -1.f) * _current->speed);
      // TODO set animation
    } break;

    case Game::HeroInput::MOVE_LEFT: {
      _current->body.set_velocity(Vector2(-1.f, 0.f) * _current->speed);
      // TODO set animation
    } break;

    case Game::HeroInput::MOVE_RIGHT: {
      _current->body.set_velocity(Vector2(1.f, 0.f) * _current->speed);
      // TODO set animation
    } break;

    case Game::HeroInput::STOP: {
      _current->body.set_velocity(Vector2(0.f, 0.f) * _current->speed);
      // TODO set animation
    } break;
  }*/
}

void HostGame::Process_States(void) {
  HostSnapshot * current = m_state_buffer->get_last();
  HostSnapshot * next = m_state_buffer->get_next();

    // Process_Hero_State(&(current->character), &(next->character));

    /*for (uint32 hero = 0; hero < current->hero_state_count; ++hero) {
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

  next->hero_state_count = current->hero_state_count;*/

  // Process Player

  // Process Connections

  // Process Agents

  // Process Missiles

  m_state_buffer->procede();
}

void HostGame::Process_Ninja_State(const Game::Ninja_State * _current, Game::Ninja_State * _next) {
  /*_next->copy(*_current);
  integrator_.Integrate(_current->body, &(_next->body));

  uint32 motions_count = 0;
  for (uint32 motion = 0; motion < _current->motions_count; ++motion) {
    real32 end = _current->motions[motion].start_time + _current->motions[motion].duration;
    if (internal_time < end) {
      ++motions_count;
      _next->motions[motions_count] = _current->motions[motion];
    }
  }
  _next->motions_count = motions_count;*/
}

void HostGame::Process_Missile_State(const Game::Missile_State * _current, Game::Missile_State * _next) {
}
}
}
