#ifndef ENGINE_PHYSICS_COLLISION_H_
#define ENGINE_PHYSICS_COLLISION_H_

#include "Engine\Types.h"
#include "Engine\Physics\Shapes.h"

namespace Engine {
namespace Physics {
  struct Manifold;
  struct Body;

  typedef void(*CollisionCallback)(Manifold *m, Body *a, Body *b);

  extern CollisionCallback Dispatch[(uint32)ShapeType::Count][(uint32)ShapeType::Count];

  void CircleToCircle(Manifold *m, Body *a, Body *b);
  void CircleToPolygon(Manifold *m, Body *a, Body *b);
  void PolygonToCircle(Manifold *m, Body *a, Body *b);
  void PolygonToPolygon(Manifold *m, Body *a, Body *b);
}
}

#endif