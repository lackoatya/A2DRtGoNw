#ifndef P3A_GRAPHICS_TEST_H_
#define P3A_GRAPHICS_TEST_H_

#include "Engine/Types.h"
#include "Engine/Core/ProcessableInterface.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/Appearance.h"

#include "P3A/Core/State.h"
#include "P3A/Graphics/Model.h"
#include "P3A/Graphics/GraphicsContext.h"

namespace P3A {
namespace Graphics {
class Test : public Engine::Core::ProcessableInterface<P3A::Core::State> {
  public:
    Test(P3A::Graphics::GraphicsContext & _context);
    inline Test(void) = delete;
    inline Test(Test && _other) = delete;
    inline Test(Test const& _other) = delete;
    inline Test & operator=(Test && _other) = delete;
    inline Test & operator=(Test const& _other) = delete;
    inline virtual ~Test(void) = default;

    P3A::Core::State Process(real32 const& _elapsed_time);

    void Update(real32 const& _elapsed_time);
    void Render(void);

    void HandleKeys(void);
    void HandleMouse(void);

  private:
    bool clicked = false;
    Engine::Graphics::Mesh ** meshes_ = nullptr;
    Engine::Graphics::Appearance ** appearances_ = nullptr;

    P3A::Graphics::Model * model_ = nullptr;
    P3A::Graphics::GraphicsContext & context_;
  };
}
}

#endif