/*#include "P3A/Sole/SoleObserver.h"

#include "BOOST/lexical_cast.hpp"

#include "GLM/gtc/type_ptr.hpp"

#include "Engine/Numerics/LinearInterpolation.hpp"

namespace P3A {
namespace Sole {
SoleObserver::SoleObserver(real32 const& _interval
                         , Game::Hero * _observed
                         , Graphics::GraphicsContext * _graphics_context
                         , Graphics::GameArtSource * _art_source
                         , Engine::Container::IntervalBuffer < SoleSnapshot > * _state_buffer)
    : ObserverInterface(_interval, _observed, _graphics_context, _art_source, _state_buffer) {
  memset(pressed, 0, sizeof(pressed));
}

void SoleObserver::Render(void) {
  glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  real32 chc_internal = internal_time;
  uint32 current_index = state_buffer_->get_index(internal_time);
  SoleSnapshot * current = state_buffer_->get(current_index);
  SoleSnapshot * next    = state_buffer_->get(state_buffer_->next(current_index));

  real32 alpha = fmod(internal_time, state_buffer_->interval()) / state_buffer_->interval();
  Vector2 interpolated_location = Engine::Numerics::LinearInterpolation<Vector2>(current->character.body.position(), alpha, next->character.body.position());

  graphics_context_->UpdateCameraAndView(interpolated_location);

  graphics_context_->PrepareBoxDraw();
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("view"), 1, GL_FALSE,
                     glm::value_ptr(graphics_context_->view_matrix()));
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("projection"), 1, GL_FALSE,
                     glm::value_ptr(graphics_context_->projection_matrix()));

  Render_Hero(&(current->character), &(next->character));

  graphics_context_->DrawBox(art_source_->textures_[0], Vector2(0.f, 0.f), 0.f);

  //graphics_context_->PrepareStringDraw();
  //std::string time1 = boost::lexical_cast<std::string>(game_->internal_time - internal_time);
  //std::string time2 = boost::lexical_cast<std::string>() + " " + boost::lexical_cast<std::string>(current_index);
  //graphics_context_->DrawString(Graphics::Font::ARIAL_BLACK, time1, -400.f, 300.f, glm::vec4(0.f, 1.f, 0.f, 1.f), StringAlignment::LEFT);
  //graphics_context_->DrawString(Font::ARIAL_BLACK, time2, -400.f, 264.f, glm::vec4(0.f, 1.f, 1.f, 1.f), StringAlignment::LEFT);

  //game_->unit0.Render(graphics_context_, game_->unit0.position());
  //graphics_context_->DrawBox(world_->wall1.texture(), world_->wall1.position(), 0.f);
  //graphics_context_->DrawBox(world_->wall2.texture(), world_->wall2.position(), 0.f);

  glBindVertexArray(0);
}

void SoleObserver::Render_Hero(const Game::HeroState * _current, const Game::HeroState * _next) {
  real32 alpha = fmod(internal_time, state_buffer_->interval()) / state_buffer_->interval();
  Vector2 interpolated_location = Engine::Numerics::LinearInterpolation<Vector2>(_current->body.position(), alpha, _next->body.position());
  graphics_context_->DrawBox(art_source_->textures_[0], interpolated_location, 0.f);
}

void SoleObserver::HandleInput(void) {
  Handle_Keys();
  Handle_Mouse();
}

void SoleObserver::Handle_Keys(void) {
  // TODO Use KeyBindings

  int32 direction = -1;
  Game::HeroInput input = Game::HeroInput::STOP;

  if (graphics_context_->GetKey(GLFW_KEY_W) == GLFW_PRESS) {
    pressed[0] = true;
    direction = 0;
    input = Game::HeroInput::MOVE_UP;
  }
  else {
    pressed[0] = false;
  }

  if (graphics_context_->GetKey(GLFW_KEY_S) == GLFW_PRESS) {
    pressed[1] = true;
    direction = 1;
    input = Game::HeroInput::MOVE_DOWN;
  }
  else {
    pressed[1] = false;
  }

  if (graphics_context_->GetKey(GLFW_KEY_A) == GLFW_PRESS) {
    pressed[2] = true;
    direction = 2;
    input = Game::HeroInput::MOVE_LEFT;
  }
  else {
    pressed[2] = false;
  }

  if (graphics_context_->GetKey(GLFW_KEY_D) == GLFW_PRESS) {
    pressed[3] = true;
    direction = 3;
    input = Game::HeroInput::MOVE_RIGHT;
  }
  else {
    pressed[3] = false;
  }

  if (last_direction != -1 && pressed[last_direction]) return;
  last_direction = direction;
  observed_->input_buffer.add(input);
  inp_cnt++;

  if (inp_cnt == 32) {
    inp_cnt = 0;
  }
}

void SoleObserver::Handle_Mouse(void) {
  if (graphics_context_->GetMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    if (!pressed[4]) {
      pressed[4] = true;
      //game_->unit0.Animate(1);
    }
  }
  else {
    pressed[4] = false;
  }

  if (graphics_context_->GetMouse(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    if (!pressed[5]) {
      pressed[5] = true;
      //game_->unit0.Animate(3);
    }
  }
  else {
    pressed[5] = false;
  }
}
}
}*/