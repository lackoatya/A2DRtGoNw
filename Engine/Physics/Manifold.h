#ifndef ENGINE_PHYSICS_MANIFOLD_H_
#define ENGINE_PHYSICS_MANIFOLD_H_

#include "Engine\Types.h"

namespace Engine {
namespace Physics {
struct Body;

struct Manifold {
  public:
    Body * A;
    Body * B;

    real32  penetration;    // Depth of penetration from collision
    Vector2 normal;	    // From A to B
    Vector2 contacts[2];    // Points of contact during collision
    uint32 contact_count;   // Number of contacts that occured during collision
    real32  e;              // Mixed restitution
    real32  df;             // Mixed dynamic friction
    real32  sf;             // Mixed static friction

    inline Manifold(Body *a, Body *b) : A(a), B(b) { }
    inline Manifold(void) = delete;
    //inline Manifold(Manifold && _other) = delete;
    inline Manifold(Manifold const& _other) = default;
    inline Manifold & operator=(Manifold && _other) = delete;
    inline Manifold & operator=(Manifold const& _other) = delete;
    inline virtual ~Manifold(void) = default;

    void Solve(void);                 // Generate contact information
    void Initialize(void);            // Precalculations for impulse solving
    void ApplyImpulse(void);          // Solve impulse and apply
    void PositionalCorrection(void);  // Naive correction of positional penetration
    void InfiniteMassCorrection(void);
};
}
}

#endif