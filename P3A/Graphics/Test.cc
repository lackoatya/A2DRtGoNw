#include "P3A/Graphics/Test.h"

#include <string>

#include "GLM/gtc/type_ptr.hpp"

namespace P3A { 
namespace Graphics {
Test::Test(P3A::Graphics::GraphicsContext & _context)
    : context_(_context) {
  meshes_ = new Engine::Graphics::Mesh*[1];
  meshes_[0] = new Engine::Graphics::Mesh(std::string("P3A\\Data\\Meshes\\dzsoni.mesh"));

  appearances_ = new Engine::Graphics::Appearance*[1];
  appearances_[0] = new Engine::Graphics::Appearance(
      std::string("P3A\\Data\\Appearances\\dzsoni.appearance"), std::string("P3A\\Data\\Textures"));

  model_ = new Model(meshes_[0], appearances_[0], 0, Vector2(0.f, 0.f), context_);
}

P3A::Core::State Test::Process(real32 const& _elapsed_time) {
  context_.PollEvents();

  HandleKeys();
  HandleMouse();

  Update(_elapsed_time);
  Render();

  context_.SwapBuffers();

  return P3A::Core::State(context_.ShouldClose() ?
      P3A::Core::CoreState::EXIT : P3A::Core::CoreState::CONTINUE);
}

void P3A::Graphics::Test::Update(real32 const& _elapsed_time) {
  model_->Update(_elapsed_time);
}

void P3A::Graphics::Test::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  context_.UpdateCameraAndView(Vector2(0.0f, 0.0f));

  context_.PrepareBoxDraw();
  glUniformMatrix4fv(context_.shader_box()->GetLocation("view"), 1, GL_FALSE,
                     glm::value_ptr(context_.view_matrix()));
  glUniformMatrix4fv(context_.shader_box()->GetLocation("projection"), 1, GL_FALSE,
                     glm::value_ptr(context_.projection_matrix()));

  model_->Render();

  glBindVertexArray(0);
}

void P3A::Graphics::Test::HandleKeys(void)
{
  //if (glfwGetKey(context.window, GLFW_KEY_SPACE) == GLFW_PRESS) pau
}

void P3A::Graphics::Test::HandleMouse(void)
{

}
}
}
