#ifndef LABYRINTH_GRAPHICS_ICONTEXT_H_
#define LABYRINTH_GRAPHICS_ICONTEXT_H_

#include "Engine/Types.h"
#include "Engine/Graphics/IContext.h"

namespace Labyrinth {
namespace Graphics {
struct Color {
public:
  real32 r, g, b, a;

  inline Color(real32 const& _r, real32 const& _g, real32 const& _b, real32 const& _a)
      : r(_r), g(_g), b(_b), a(_a) {
  }
  virtual ~Color(void) { };
};

enum class StringAlignment {
  LEFT = 0,
  MIDDLE,
  RIGHT,

  Count
};

class IStaticLabel {
public:
  const std::string text;

  virtual void Render( Vector2 const& _position, Color const& _color
                     , StringAlignment const& _alignment ) = 0;
};

class IFont {
public:
  virtual IStaticLabel * CreateStaticLabel(std::string const& _text) = 0;
};

class IContext : public Engine::Graphics::IContext {
public:
  inline IContext(uint32 const& _window_width, uint32 const& _window_height)
      : Engine::Graphics::IContext(_window_width, _window_height) {
  }
  inline ~IContext(void) {
  }
};
}
}

#endif