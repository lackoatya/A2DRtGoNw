#ifndef P3A_HOST_HOST_GAME_H_
#define P3A_HOST_HOST_GAME_H_

#include "Engine/Game/IGame.hpp"
#include "Engine/Numerics/SymplecticEulerIntegrator.hpp"

#include "P3A/GameResult.h"
#include "P3A/Game/Ninja.h"
#include "P3A/Game/Missile.h"
#include "P3A/Host/HostSnapshot.h"

namespace P3A {
namespace Host {
class HostGame : public Engine::Game::IGame < HostSnapshot, GameResult > {
public:
  inline HostGame(Engine::Container::IntervalBuffer < HostSnapshot > * _state_buffer)
      : Engine::Game::IGame < HostSnapshot, GameResult >(_state_buffer)
      , integrator_(_state_buffer->interval()) {
    assert(_state_buffer);
  }
  inline virtual ~HostGame(void) = default;

protected:
  // TODO This should be a template parameter!
  Engine::Numerics::SymplecticEulerIntegrator < Engine::Physics::Body < Engine::Physics::AABB > > integrator_;

  void Process_Inputs(void);
  void Process_Ninja_Input_Buffer(Game::Ninja * _ninja);
  void Process_Ninja_Command(Game::Ninja_State * _state, const Game::Ninja_Command * _command);

  void Process_States(void);
  void Process_Ninja_State(const Game::Ninja_State * _current, Game::Ninja_State * _next);
  void Process_Missile_State(const Game::Missile_State * _current, Game::Missile_State * _next);

  inline GameResult GetResult(void) { return GameState::CONTINUE; }
};
}
}

#endif