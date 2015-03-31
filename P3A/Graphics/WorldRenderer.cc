#include "P3A/Graphics/WorldRenderer.h"

#include <string>

#include "BOOST/bind.hpp"

#include "GLM/gtc/type_ptr.hpp"

P3A::Graphics::WorldRenderer::WorldRenderer(P3A::Game::World * _world,
                                            P3A::Graphics::GraphicsContext * _graphics_context)
    : world_(_world),
      graphics_context_(_graphics_context) {
  meshes_ = new Engine::Graphics::Mesh*[1];
  meshes_[0] = new Engine::Graphics::Mesh(std::string("P3A\\Data\\Meshes\\samurai.mesh"));

  appearances_ = new Engine::Graphics::Appearance*[1];
  appearances_[0] = new Engine::Graphics::Appearance(
    std::string("P3A\\Data\\Appearances\\samurai.appearance"), std::string("P3A\\Data\\Textures"));

  model_ = new Model(meshes_[0], appearances_[0], 0, Vector2(0.f, 0.f), graphics_context_);

  clicked[0] = false; clicked[1] = false;
}

P3A::CoreResult P3A::Graphics::WorldRenderer::Process(real32 const& _elapsed_time) {
  graphics_context_->PollEvents();

  HandleKeys();
  HandleMouse();

  Update(_elapsed_time);
  Render();

  graphics_context_->SwapBuffers();

  if (graphics_context_->ShouldClose()) return P3A::CoreState::EXIT;
  else return P3A::CoreState::CONTINUE;
}

void P3A::Graphics::WorldRenderer::Update(real32 const& _elapsed_time) {
  model_->Update(_elapsed_time);
}

void P3A::Graphics::WorldRenderer::Render(void) {
  glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  graphics_context_->UpdateCameraAndView(Vector2(0.0f, 0.0f));

  graphics_context_->PrepareBoxDraw();
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("view"), 1, GL_FALSE,
    glm::value_ptr(graphics_context_->view_matrix()));
  glUniformMatrix4fv(graphics_context_->shader_box()->GetLocation("projection"), 1, GL_FALSE,
    glm::value_ptr(graphics_context_->projection_matrix()));

  model_->Render();

  glBindVertexArray(0);
}

void P3A::Graphics::WorldRenderer::HandleKeys(void)
{
  //if (glfwGetKey(context.window, GLFW_KEY_SPACE) == GLFW_PRESS) pau
}

void P3A::Graphics::WorldRenderer::HandleMouse(void)
{
  if (graphics_context_->GetMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    if (!clicked[GLFW_MOUSE_BUTTON_LEFT]) {
      clicked[GLFW_MOUSE_BUTTON_LEFT] = true;
      model_->Animate(1);
    }
  }
  else {
    clicked[GLFW_MOUSE_BUTTON_LEFT] = false;
  }

  if (graphics_context_->GetMouse(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    if (!clicked[GLFW_MOUSE_BUTTON_RIGHT]) {
      clicked[GLFW_MOUSE_BUTTON_RIGHT] = true;
      model_->Animate(3);
    }
  }
  else {
    clicked[GLFW_MOUSE_BUTTON_RIGHT] = false;
  }
}
