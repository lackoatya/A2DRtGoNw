#include "Engine/Graphics/ContextBase.h"

#include <assert.h>

#include "GLM/gtc/matrix_transform.hpp"

namespace Engine {
namespace Graphics {
ContextBase::ContextBase(uint32 const& _window_width, uint32 const& _window_height,
                         real32 _camera_min_distance, real32 _camera_max_distance)
    : window_width_(_window_width),
      window_height_(_window_height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  assert(window_ = glfwCreateWindow(window_width_, window_height_, "Game", nullptr, nullptr));
  glfwMakeContextCurrent(window_);

  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, window_width_, window_height_);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  projection_matrix_ = glm::ortho(0.0f, static_cast<real32>(window_width_), 0.0f,
                                  static_cast<real32>(window_height_), _camera_min_distance,
                                  _camera_max_distance);

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);
  glGenBuffers(1, &EBO_);
}

ContextBase::~ContextBase(void)
{
  glfwTerminate();
}
}
}