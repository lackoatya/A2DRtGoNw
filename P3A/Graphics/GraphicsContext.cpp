#include "P3A/Graphics/GraphicsContext.h"

#include <assert.h>

#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace P3A{
namespace Graphics{
GraphicsContext::GraphicsContext(uint32 const& _window_width, uint32 const& _window_height,
                                 real32 _camera_min_distance, real32 _camera_max_distance)
    : Engine::Graphics::ContextBase(_window_width, _window_height, _camera_min_distance,
                                    _camera_max_distance) {
  shader_box_ = new Engine::Graphics::Shader("P3A\\Shaders\\Box.vs", "P3A\\Shaders\\Box.frag");
  shader_text_ = new Engine::Graphics::Shader("P3A\\Shaders\\Text.vs", "P3A\\Shaders\\Text.frag");

  font_arial_black_ = new Engine::Graphics::TextureBase("P3A\\Data\\Fonts\\arial_black.png");
}

void GraphicsContext::DrawBox(Engine::Graphics::TextureBase const* _texture, Vector2 const& _center,
                              real32 const& _rotation) {
  glBindTexture(GL_TEXTURE_2D, _texture->id());

  glm::mat4 modelMatrix = glm::mat4();
  modelMatrix = glm::translate(modelMatrix, glm::vec3(_center.x, _center.y, -10.0f)) *
      glm::rotate(modelMatrix, _rotation, glm::vec3(0.f, 0.f, 1.f));
  GLint modelLoc = glGetUniformLocation(shader_box_->shader_program(), "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  // TODO These aren't used!
  real32 shapeWidth = (real32)(_texture->width() / 2.0f);
  real32 shapeHeight = (real32)(_texture->height() / 2.0f);
  real32 textureWidthRatio = 1.f; // (real32)(shapeWidth * 2 / _texture->width);
  real32 textureHeightRatio = 1.f; //(real32)(shapeHeight * 2 / _texture->height);

  struct ModelShape {
    public:
      GLfloat vertices[28];
      GLuint indices[6];
  } modelShape;

  // TOP RIGHT:
  // Position Coords:
  modelShape.vertices[0] = shapeWidth;
  modelShape.vertices[1] = shapeHeight;

  // Colors:
  modelShape.vertices[2] = 1.0f;
  modelShape.vertices[3] = 0.0f;
  modelShape.vertices[4] = 0.0f;

  // Texture Coords:
  modelShape.vertices[5] = textureWidthRatio;
  modelShape.vertices[6] = textureHeightRatio;
  // ----------------------------

  // BOTTOM RIGHT:
  // Position Coords:
  modelShape.vertices[7] = shapeWidth;
  modelShape.vertices[8] = -shapeHeight;

  // Colors:
  modelShape.vertices[9] = 0.0f;
  modelShape.vertices[10] = 1.0f;
  modelShape.vertices[11] = 0.0f;

  // Texture Coords:
  modelShape.vertices[12] = textureWidthRatio;
  modelShape.vertices[13] = 0.0f;
  // ----------------------------

  // BOTTOM LEFT:
  // Position Coords:
  modelShape.vertices[14] = -shapeWidth;
  modelShape.vertices[15] = -shapeHeight;

  // Colors:
  modelShape.vertices[16] = 0.0f;
  modelShape.vertices[17] = 0.0f;
  modelShape.vertices[18] = 1.0f;

  // Texture Coords:
  modelShape.vertices[19] = 0.0f;
  modelShape.vertices[20] = 0.0f;
  // ----------------------------

  // TOP LEFT:
  // Position Coords:
  modelShape.vertices[21] = -shapeWidth;
  modelShape.vertices[22] = shapeHeight;

  // Colors:
  modelShape.vertices[23] = 1.0f;
  modelShape.vertices[24] = 1.0f;
  modelShape.vertices[25] = 0.0f;

  // Texture Coords:
  modelShape.vertices[26] = 0.0f;
  modelShape.vertices[27] = textureHeightRatio;
  // ----------------------------

  modelShape.indices[0] = 0;
  modelShape.indices[1] = 1;
  modelShape.indices[2] = 3;
  modelShape.indices[3] = 1;
  modelShape.indices[4] = 2;
  modelShape.indices[5] = 3;

  glBindVertexArray(VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(modelShape.vertices), modelShape.vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelShape.indices), modelShape.indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
                       (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
                       (GLvoid*)(5 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GraphicsContext::DrawString(Font const& _font, std::string const& _text, float const& _x,
                                 float const& _y, glm::vec4 const& _color,
                                 StringAlignment const& _alignment) {
  const uint32 glyph_count = 16;

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
  }
}

GraphicsContext::~GraphicsContext(void) {
  delete shader_box_;
  shader_box_ = nullptr;
  delete shader_text_;
  shader_text_ = nullptr;

  delete font_arial_black_;
  font_arial_black_ = nullptr;
}
}
}