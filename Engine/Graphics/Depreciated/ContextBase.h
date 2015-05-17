#ifndef ENGINE_GRAPHICS_CONTEXTBASE_H_
#define ENGINE_GRPAHICS_CONTEXTBASE_H_

#define GLEW_STATIC
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#define OPENGL_MAJOR_VERSION	3
#define OPENGL_MINOR_VERSION	3
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Engine/Types.h"
#include "Engine/Graphics/Camera.h"

namespace Engine {
namespace Graphics {
class ContextBase : public NonCopyable {
  public:
    inline ContextBase(uint32 const& _window_width, uint32 const& _window_height)
        : ContextBase(_window_width, _window_height, 0.01f, 64.0f) { }
    ContextBase(uint32 const& _window_width, uint32 const& _window_height,
                real32 _camera_min_distance, real32 _camera_max_distance);
    virtual ~ContextBase(void);

    inline void PollEvents(void) const { glfwPollEvents(); }
    inline void SwapBuffers(void) const { glfwSwapBuffers(window_); }
    inline int ShouldClose(void) const { return glfwWindowShouldClose(window_); }
    inline void Close(void) const { glfwSetWindowShouldClose(window_, true); }

    inline int GetKey(int _key) const { return glfwGetKey(window_, _key); }
    inline int GetMouse(int _button) const { return glfwGetMouseButton(window_, _button); }

    inline void UpdateCameraAndView(Vector2 const& _position){
      camera_.UpdateVectors(*this, _position);
      view_matrix_ = glm::lookAt(camera_.center(), camera_.eye(), camera_.up());
    }

    inline glm::mat4 view_matrix(void) const { return view_matrix_; }
    inline glm::mat4 projection_matrix(void) const { return projection_matrix_; }

    inline uint32 window_width(void) const { return window_width_; }
    inline uint32 window_height(void) const { return window_height_; }

  protected:
    GLuint VAO_ = 0;
    GLuint VBO_ = 0;
    GLuint EBO_ = 0;

    glm::mat4 view_matrix_ = glm::mat4();
    glm::mat4 projection_matrix_ = glm::mat4();

    Camera camera_;

  private:
    uint32 window_width_ = 800, window_height_ = 600;
    GLFWwindow * window_ = nullptr;
};
}
}

#endif