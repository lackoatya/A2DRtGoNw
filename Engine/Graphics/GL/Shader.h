#ifndef ENGINE_GRAPHICS_GL_SHADER_H_
#define ENGINE_GRAPHICS_GL_SHADER_H_

#define GLEW_STATIC
#include "GLEW/glew.h"

#include "Engine/Types.h"
#include "Engine/Graphics/IShader.h"

namespace Engine {
namespace Graphics {
namespace GL {
class Shader : public IShader {
public:
  Shader(const GLchar * _vertex_path, const GLchar * _fragment_path);
  
  inline virtual ~Shader(void) {
    glDeleteProgram(m_shader_program);
  }

  inline GLuint operator()(void) const {
    return m_shader_program;
  }

protected:
  GLuint m_shader_program = 0;
};

class StaticShader : Shader {
public:
  inline StaticShader( const GLchar * _vertex_path, const GLchar * _fragment_path
              , const GLchar ** _uniforms, uint32 const& _uniforms_count )
      : Shader(_vertex_path, _fragment_path)
      , m_uniforms_count(_uniforms_count)
      , m_uniforms(new GLint[_uniforms_count]) {
    for (uint32 current = 0; current < m_uniforms_count; ++current) {
      m_uniforms[current] = glGetUniformLocation(m_shader_program, _uniforms[current]);
    }
  }

  inline ~StaticShader(void) {
    delete m_uniforms;
    m_uniforms = nullptr;
  }

  inline GLint operator[](uint32 const& _uniform_index) const {
    assert(m_uniforms && _uniform_index < m_uniforms_count);
    return m_uniforms[_uniform_index];
  }

  inline GLint operator[](const GLchar * _name) const {
    return glGetUniformLocation(m_shader_program, _name);
  }

protected:
  uint32 m_uniforms_count = 0;
  GLint * m_uniforms = nullptr;
};
}
}
}

#endif