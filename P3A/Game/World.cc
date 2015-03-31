#include "P3A/Game/World.h"

#include "BOOST/bind.hpp"

P3A::Game::World::World(void) {
  stage_ = new Stage();
}

P3A::GameResult P3A::Game::World::Process(void) {
  return P3A::GameState::CONTINUE;
}

