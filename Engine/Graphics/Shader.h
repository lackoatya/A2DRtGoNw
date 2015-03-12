#ifndef ENGINE_GRAPHICS_SHADER_H_
#define ENGINE_GRAPHICS_SHADER_H_

#define GLEW_STATIC
#include "GLEW/glew.h"

namespace Engine {
namespace Graphics {
class Shader {
  public:
    Shader(const GLchar * _vertex_path, const GLchar * _fragment_path);
    inline Shader(void) = delete;
    inline Shader(Shader && _other) = delete;
    inline Shader(Shader const& _other) = delete;
    inline Shader & operator=(Shader && _other) = delete;
    inline Shader & operator=(Shader const& _other) = delete;
    inline virtual ~Shader(void) { glDeleteProgram(shader_program_); }

    inline void Use(void) const { glUseProgram(shader_program_); }
    inline GLint GetLocation(const GLchar * _name) const {
      return glGetUniformLocation(shader_program_, _name);
    }

    inline GLuint shader_program(void) const { return shader_program_; }

  private:
    GLuint shader_program_ = 0;
};
}
}

#endif