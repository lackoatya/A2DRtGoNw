#include "Labyrinth/Graphics/GL/Context.h"

namespace Labyrinth {
namespace Graphics {
namespace GL {
Context::Context( uint32 const& _window_width, uint32 const& _window_height
                , real32 _camera_min_distance, real32 _camera_max_distance )
    : Graphics::IContext(_window_width, _window_height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  assert(m_window = glfwCreateWindow(m_window_width, m_window_height, "Game", nullptr, nullptr));
  glfwMakeContextCurrent(m_window);

  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, m_window_width, m_window_height);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /*
  projection_matrix_ = glm::ortho(0.0f, static_cast<real32>(window_width_), 0.0f,
                                  static_cast<real32>(window_height_), _camera_min_distance,
                                  _camera_max_distance);

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);
  glGenBuffers(1, &EBO_);
  */
}

void Context::DrawString( Font const& _font, std::string const& _text, Vector2 const& _position
                        , Color const& _color, StringAlignment const& _alignment ) {
  /*const uint32 glyph_count = 16;

  Engine::Graphics::TextureBase * font_texture = nullptr;

  switch (_font) {
    case Font::ARIAL_BLACK:
    font_texture = font_arial_black_;
    break;

    default:
    assert(false && "Unkown Font enumerator member!");
  }

  glBindTexture(GL_TEXTURE_2D, font_texture->id());

  glUniformMatrix4fv(shader_text_->GetLocation("projection"), 1, GL_FALSE,
                     glm::value_ptr(projection_matrix_));
  glUniformMatrix4fv(shader_text_->GetLocation("view"), 1, GL_FALSE, glm::value_ptr(view_matrix_));
  glUniform4fv(shader_text_->GetLocation("color"), 1, glm::value_ptr(_color));

  float glyph_Width = static_cast<real32>(font_texture->width()) / glyph_count;
  float glyph_Height = static_cast<real32>(font_texture->height()) / glyph_count;
  float glyph_WidthRatio = 1.0 / glyph_count;
  float glyph_HeightRatio = 1.0 / glyph_count;

  float calculated_x = _x;
  switch (_alignment) {
    case StringAlignment::LEFT:
    break;
    case StringAlignment::MIDDLE:
    calculated_x -= (_text.length() * glyph_Width) / 2.0f;
    break;
    case StringAlignment::RIGHT:
    calculated_x -= _text.length() * glyph_Width;
    break;

    default: assert(false && "Unkown StringAlignment enumerator member!");
  }

  for (unsigned int current = 0; current < _text.length(); current++) {
    float glyph_x = (float)(_text[current] % glyph_count);
    float glyph_y = (float)glyph_count - _text[current] / glyph_count - 1;

    glm::mat4 modelMatrix = glm::mat4();
    modelMatrix = glm::translate(modelMatrix, glm::vec3(calculated_x + glyph_Width * current,
      _y, -5.0f));
    glUniformMatrix4fv(shader_text_->GetLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    struct GlyphShape {
    public:
      GLfloat vertices[16];
      GLuint indices[6];
    } glyph;

    // TOP RIGHT:
    // Position Coords:
    glyph.vertices[0] = glyph_Width;
    glyph.vertices[1] = glyph_Height;

    // Texture Coords:
    glyph.vertices[2] = (glyph_x + 1) * glyph_WidthRatio;
    glyph.vertices[3] = (glyph_y + 1) * glyph_HeightRatio;
    // ----------------------------

    // BOTTOM RIGHT:
    // Position Coords:
    glyph.vertices[4] = glyph_Width;
    glyph.vertices[5] = 0.0f;

    // Texture Coords:
    glyph.vertices[6] = (glyph_x + 1) * glyph_WidthRatio;
    glyph.vertices[7] = (glyph_y + 0) * glyph_HeightRatio;
    // ----------------------------

    // BOTTOM LEFT:
    // Position Coords:
    glyph.vertices[8] = 0.0f;
    glyph.vertices[9] = 0.0f;

    // Texture Coords:
    glyph.vertices[10] = (glyph_x + 0) * glyph_WidthRatio;
    glyph.vertices[11] = (glyph_y + 0) * glyph_HeightRatio;
    // ----------------------------

    // TOP LEFT:
    // Position Coords:
    glyph.vertices[12] = 0.0f;
    glyph.vertices[13] = glyph_Height;

    // Texture Coords:
    glyph.vertices[14] = (glyph_x + 0) * glyph_WidthRatio;
    glyph.vertices[15] = (glyph_y + 1) * glyph_HeightRatio;
    // ----------------------------

    glyph.indices[0] = 0;
    glyph.indices[1] = 1;
    glyph.indices[2] = 3;
    glyph.indices[3] = 1;
    glyph.indices[4] = 2;
    glyph.indices[5] = 3;

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glyph.vertices), glyph.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glyph.indices), glyph.indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                          (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }*/
}

Context::~Context(void) {
  glfwTerminate();
}
}
}
}