#ifndef ENGINE_GRAPHICS_SHADER_H_
#define ENGINE_GRAPHICS_SHADER_H_

#define GLEW_STATIC
#include "GLEW/glew.h"

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
class Shader : public NonCopyable {
  public:
    Shader(const GLchar * _vertex_path, const GLchar * _fragment_path);
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