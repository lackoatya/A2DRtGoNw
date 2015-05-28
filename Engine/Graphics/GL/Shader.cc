#include "Engine/Graphics/GL/Shader.h"

#include <string>
#include <fstream>
#include <sstream>

namespace Engine {
namespace Graphics {
namespace GL {
bool Shader::Load( std::string const& _vertex_path
                 , std::string const& _fragment_path ) {
  std::string vertex_code;
  std::string fragment_code;

  std::ifstream vertex_shader_file(_vertex_path), fragment_shader_file(_fragment_path);
  std::stringstream vertex_shader_stream, fragment_shader_stream;

  assert( !vertex_shader_file.fail() && !fragment_shader_file.fail() );

  vertex_shader_stream << vertex_shader_file.rdbuf();
  fragment_shader_stream << fragment_shader_file.rdbuf();

  vertex_shader_file.close();
  fragment_shader_file.close();

  vertex_code = vertex_shader_stream.str();
  fragment_code = fragment_shader_stream.str();

  const GLchar * vertex_shader_code = vertex_code.c_str();
  const GLchar * fragment_shader_code = fragment_code.c_str();

  GLint success;
  GLuint vertex, fragment;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertex_shader_code, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  // assert(success);
  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(vertex, 512, NULL, info_log);
    // Engine::Utility::AbortWithMessageAndData("Vertex Compilation failed:\0", info_log);

    // __asm int 3
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragment_shader_code, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  // assert(success);
  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(fragment, 512, NULL, info_log);
    // Engine::Utility::AbortWithMessageAndData("Fragment Compilation failed:\0", info_log);

    // __asm int 2
  }

  m_shader_program = glCreateProgram();
  glAttachShader(m_shader_program, vertex);
  glAttachShader(m_shader_program, fragment);
  glLinkProgram(m_shader_program);

  glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
  assert(success);
  /*if (!success) {
    GLchar info_log[512];
    glGetProgramInfoLog(shader_program_, 512, NULL, info_log);
    char message[600] = "ERROR::SHADER::VERTEX::LINKING_FAILED\n\0";
    Engine::Utility::AbortWithMessageAndData("Shader Linking failed:\0", info_log);
  }*/

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return true;
}
}
}
}
