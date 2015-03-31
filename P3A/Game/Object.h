#ifndef P3A_GAME_OBJECT_H_
#define P3A_GAME_OBJECT_H_

#include "Engine/Graphics/TextureBase.h"
#include "Engine/Physics/DescriptorInterfaces.h"
#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Game {
class Object : public Engine::Physics::DescriptorInterface {
  public:
    inline Object(Vector2 const& _center, Engine::Graphics::TextureBase * _texture,
                  P3A::Graphics::GraphicsContext * _context)
        : Engine::Physics::DescriptorInterface(_center, static_cast<real32>(_texture->width()),
                                                        static_cast<real32>(_texture->height())),
          texture_(_texture),
          context_(_context) { }
    inline virtual ~Object(void) = default;

    void Describe(uint8 * _segment) { memcpy(_segment, this, sizeof(this)); };

  private:
    Engine::Graphics::TextureBase * texture_ = nullptr;
    P3A::Graphics::GraphicsContext * context_ = nullptr;
};
}
}

#endif