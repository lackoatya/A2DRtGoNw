#ifndef ENGINE_PHYSICS_REALITY_H_
#define ENGINE_PHYSICS_REALITY_H_

#include <vector>

#include "Engine/Types.h"
#include "Engine/Core/ProcessableInterface.h"
#include "Engine/Physics/Manifold.h"

namespace Engine {
namespace Physics {
struct Body;
struct ShapeInterface;

class Reality {
  public:
    Reality(real32 const& _interval);
    inline Reality(void) = delete;
    inline Reality(Reality && _other) = delete;
    inline Reality(Reality const& _other) = delete;
    inline Reality & operator=(Reality && _other) = delete;
    inline Reality & operator=(Reality const& _other) = delete;
    inline virtual ~Reality(void) = default;

    void Process(void);

    Body * Add(ShapeInterface * shape, uint32 x, uint32 y);

  private:
    const real32 interval_;

    // QUESTION: what is this?
    uint32 m_iterations = 10;
    std::vector<Body *> bodies_;
    std::vector<Manifold> contacts_;

    void IntegrateForces(Engine::Physics::Body *b, real32 const& _interval);
    void IntegrateVelocity(Engine::Physics::Body *b, real32 const& _interval);
};
}
}

#endif