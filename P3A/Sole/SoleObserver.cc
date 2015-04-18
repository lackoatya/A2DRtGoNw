#include "P3A/Sole/SoleObserver.h"

#include "BOOST/lexical_cast.hpp"

#include "GLM/gtc/type_ptr.hpp"

#include "Engine/Numerics/LinearInterpolation.hpp"

namespace P3A {
namespace Sole {
void SoleObserver::Render(void) {
  glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  graphics_context_->UpdateCameraAndView(Vector2(0.0f, 0.0f));

  graphics_context_->PrepareBoxDraw();
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("view"), 1, GL_FALSE,
                     glm::value_ptr(graphics_context_->view_matrix()));
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("projection"), 1, GL_FALSE,
                     glm::value_ptr(graphics_context_->projection_matrix()));

  uint32 current_index = state_buffer_->get_index(internal_time);
  SoleSnapshot * current = state_buffer_->get(current_index);
  SoleSnapshot * next    = state_buffer_->get(state_buffer_->next(current_index));

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

}
}
}