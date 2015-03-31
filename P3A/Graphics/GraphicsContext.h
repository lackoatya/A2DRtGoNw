#ifndef P3A_GRAPHICS_GRAPHICSCONTEXT_H_
#define P3A_GRAPHICS_GRAPHICSCONTEXT_H_

#include <string>

#include "Engine/Types.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/TextureBase.h"
#include "Engine/Graphics/ContextBase.h"

namespace P3A {
namespace Graphics {
enum class StringAlignment
{
  LEFT = 0,
  MIDDLE,
  RIGHT,

  Count
};

enum class Font
{
  ARIAL_BLACK = 0,
  Count
};

class GraphicsContext : public Engine::Graphics::ContextBase {
  public:

  public:
    GraphicsContext(uint32 const& _window_width, uint32 const& _window_height)
      : GraphicsContext(_window_width, _window_height, 0.01f, 64.0f) { }
    GraphicsContext(uint32 const& _window_width, uint32 const& _window_height,
      real32 _camera_min_distance, real32 _camera_max_distance);
    ~GraphicsContext(void);

    void PrepareBoxDraw(void) const { shader_box_->Use(); }
    void PrepareStringDraw(void) const { shader_text_->Use(); }

    void DrawBox(Engine::Graphics::TextureBase const* _texture, Vector2 const& _center,
                 real32 const& _rotation);
    void DrawString(Font const& _font, std::string const& _text, float const& _x, float const& _y,
                    glm::vec4 const& _color, StringAlignment const& _alignment);

    inline Engine::Graphics::Shader * shader_box(void) const { return shader_box_; }
    inline Engine::Graphics::Shader * shader_text(void) const { return shader_text_; }

    inline Engine::Graphics::TextureBase * font_arial_black(void) const { return font_arial_black_; }

  private:
    Engine::Graphics::Shader * shader_box_ = nullptr;
    Engine::Graphics::Shader * shader_text_ = nullptr;

    Engine::Graphics::TextureBase * font_arial_black_ = nullptr;
};
}
}

#endif