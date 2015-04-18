/*#include "P3A/Graphics/GameObserver.h"

#include <string>

#include "BOOST/bind.hpp"
#include "BOOST/lexical_cast.hpp"

#include "GLM/gtc/type_ptr.hpp"

#include "Engine/Numerics/LinearInterpolation.hpp"

namespace P3A {
namespace Graphics {
GameObserver::GameObserver(real32 const& _interval,Game::Game * _game, GraphicsContext * _graphics_context,
                           GameArtSource * _art_source,
                           Engine::Container::IntervalBuffer<Game::Snapshot> * _state_buffer,
                           Engine::Container::Buffer<Game::Input> * _input_buffer)
    : Engine::Processor::NonDeterministicProcessInterface<CoreResult>(_interval),
      game_(_game),
      graphics_context_(_graphics_context),
      art_source_(_art_source),
      state_buffer_(_state_buffer),
      input_buffer_(_input_buffer) {
  clicked[0] = false; clicked[1] = false;
}

CoreResult GameObserver::Process(real32 const& _elapsed_time) {
  internal_time += _elapsed_time;

  graphics_context_->PollEvents();

  Render();

  Game::Input * next_input = input_buffer_->get_next();
  next_input->Reset();
  HandleKeys(next_input);
  HandleMouse(next_input);
  input_buffer_->procede();

  graphics_context_->SwapBuffers();

  if (graphics_context_->ShouldClose()) return CoreState::EXIT;
  else return CoreState::CONTINUE;
}

void GameObserver::Render(void) {
  glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  graphics_context_->UpdateCameraAndView(Vector2(0.0f, 0.0f));

  graphics_context_->PrepareBoxDraw();
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("view"), 1, GL_FALSE,
    glm::value_ptr(graphics_context_->view_matrix()));
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("projection"), 1, GL_FALSE,
    glm::value_ptr(graphics_context_->projection_matrix()));

  graphics_context_->DrawBox(art_source_->textures_[0], Vector2(0.f, 0.f), 0.f);

  // TODO...
  uint32 current_index = state_buffer_->get_index(internal_time);
  Game::Snapshot * current = state_buffer_->get(current_index);
  Game::Snapshot * next = state_buffer_->get(state_buffer_->next(current_index));
  for (uint32 hero = 0; hero < current->hero_state_count; ++hero) {
    RenderHero(&(current->hero_states[hero]), &(next->hero_states[hero]));
  }

  graphics_context_->PrepareStringDraw();
  std::string time1 = boost::lexical_cast<std::string>(game_->internal_time - internal_time);
  //std::string time2 = boost::lexical_cast<std::string>() + " " + boost::lexical_cast<std::string>(current_index);
  graphics_context_->DrawString(Font::ARIAL_BLACK, time1, -400.f, 300.f, glm::vec4(0.f, 1.f, 0.f, 1.f), StringAlignment::LEFT);
  //graphics_context_->DrawString(Font::ARIAL_BLACK, time2, -400.f, 264.f, glm::vec4(0.f, 1.f, 1.f, 1.f), StringAlignment::LEFT);

  //game_->unit0.Render(graphics_context_, game_->unit0.position());
  //graphics_context_->DrawBox(world_->wall1.texture(), world_->wall1.position(), 0.f);
  //graphics_context_->DrawBox(world_->wall2.texture(), world_->wall2.position(), 0.f);

  glBindVertexArray(0);
}

void GameObserver::RenderHero(Game::HeroState * _current, Game::HeroState * _next) {
  real32 alpha = fmod(internal_time, state_buffer_->interval()) / state_buffer_->interval();
  graphics_context_->DrawBox(art_source_->textures_[0], 
    Engine::Numerics::LinearInterpolation<Vector2>(_current->body.position(), alpha, _next->body.position()), 0.f);
}

void GameObserver::HandleKeys(Game::Input * _input) {
  if (graphics_context_->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
    _input->Set(Game::Input::Command::JUMP);
}

void GameObserver::HandleMouse(Game::Input * _input) {
  if (graphics_context_->GetMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    if (!clicked[GLFW_MOUSE_BUTTON_LEFT]) {
      clicked[GLFW_MOUSE_BUTTON_LEFT] = true;
      //game_->unit0.Animate(1);
    }
  } else {
    clicked[GLFW_MOUSE_BUTTON_LEFT] = false;
  }

  if (graphics_context_->GetMouse(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    if (!clicked[GLFW_MOUSE_BUTTON_RIGHT]) {
      clicked[GLFW_MOUSE_BUTTON_RIGHT] = true;
      //game_->unit0.Animate(3);
    }
  } else {
    clicked[GLFW_MOUSE_BUTTON_RIGHT] = false;
  }
}
}
}
*/