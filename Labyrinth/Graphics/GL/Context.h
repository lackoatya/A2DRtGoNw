#ifndef LABYRINTH_GRAPHICS_GL_CONTEXT_H_
#define LABYRINTH_GRAPHICS_GL_CONTEXT_H_

#include <string>

#define GLEW_STATIC
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#define OPENGL_MAJOR_VERSION	3
#define OPENGL_MINOR_VERSION	3
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Engine/Types.h"
#include "Engine/Graphics/IShader.h"
#include "Engine/Graphics/ITexture.h"

#include "Labyrinth/Graphics/IContext.h"

namespace Labyrinth {
namespace Graphics {
namespace GL {
class StaticLabel : public IStaticLabel {
public:
  const std::string text;

  void Render( Vector2 const& _position, Color const& _color
             , StringAlignment const& _alignment );
};

class Font : public IFont {
public:
  Font(std::string const& _name);
  virtual ~Font(void);
  
  StaticLabel * CreateStaticLabel(std::string const& _text) = 0;

private:
  // Engine::
};

class Context : public Labyrinth::Graphics::IContext {
public:
  Context(uint32 const& _window_width, uint32 const& _window_height)
      : Context(_window_width, _window_height, 0.01f, 64.0f) { }
  Context( uint32 const& _window_width, uint32 const& _window_height
         , real32 _camera_min_distance, real32 _camera_max_distance );
  virtual ~Context(void);

  inline void PollEvents(void) const { glfwPollEvents(); }
  inline bool GetKey(Engine::Graphics::VirtualKey const& _key) const {
    return glfwGetKey(m_window, static_cast< int >(_key)) ? true : false;
  }
  inline bool GetMouse(Engine::Graphics::VirtualButton const& _button) const {
    return glfwGetMouseButton(m_window, static_cast< int >(_button)) ? true : false;
  }

  inline void Present(void) const { glfwSwapBuffers(m_window); }
  inline void Clear(void) const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  inline bool ShouldClose(void) const { return glfwWindowShouldClose(m_window) ? true : false; }
  inline void Close(void) const { glfwSetWindowShouldClose(m_window, true); }

  // void PrepareBoxDraw(void) const { shader_box_->Use(); }
  // void PrepareStringDraw(void) const { shader_text_->Use(); }

  // void DrawTexture( Engine::Graphics::TextureBase const* _texture, Vector2 const& _center
  //                , real32 const& _rotation);
  void DrawString( Font const& _font, std::string const& _text, Vector2 const& _position
                 , Color const& _color, StringAlignment const& _alignment );

  // inline Engine::Graphics::TextureBase * font_arial_black(void) const { return font_arial_black_; }

private:
  // Engine::Graphics::TextureBase * font_arial_black_ = nullptr;

  // GLuint VAO_ = 0;
  // GLuint VBO_ = 0;
  // GLuint EBO_ = 0;

  // glm::mat4 view_matrix_ = glm::mat4();
  // glm::mat4 projection_matrix_ = glm::mat4();

  //Camera camera_;

private:
  GLFWwindow * m_window = nullptr;
};
}
}
}

#endif