#ifndef P3A_GRAPHICS_MODEL_H_
#define P3A_GRAPHICS_MODEL_H_

#include "Engine/Graphics/ModelBase.h"

namespace P3A {
namespace Graphics {
class GraphicsContext;

class Model : public Engine::Graphics::ModelBase {
  public:
    inline Model(Engine::Graphics::Mesh * _mesh, Engine::Graphics::Appearance * _appearance,
                 uint32 const& _animation)
        : ModelBase(_mesh, _appearance, _animation) { }
    inline virtual ~Model(void) = default;

    void Render(GraphicsContext * _context, Vector2 const& _location);
  };
}
}

#endif