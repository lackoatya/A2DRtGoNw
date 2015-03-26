#include "Engine\Physics\Body.h"

#include "Engine\Physics\Shapes.h"

Engine::Physics::Body::Body(ShapeInterface * _shape, uint32 const& _x, uint32 const& _y)
  : shape(_shape->Clone()) {
  shape->body = this;
  position.Set((real32)_x, (real32)_y);
  velocity.Set(0, 0);
  angularVelocity = 0;
  torque = 0.;
  orient = 0.;
  force.Set(0., 0.);
  staticFriction = 0.5f;
  dynamicFriction = 0.3f;
  restitution = 0.2f;
  shape->Initialize();
}

void Engine::Physics::Body::SetOrient(real32 const& _radians) {
  orient = _radians;
  shape->SetOrient(_radians);
}