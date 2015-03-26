#include "Engine\Physics\Manifold.h"

#include "Engine\Physics\Body.h"
#include "Engine\Physics\Shapes.h"
#include "Engine\Physics\Collision.h"

void Engine::Physics::Manifold::Solve(void) {
  Dispatch[(uint32)A->shape->GetType()][(uint32)B->shape->GetType()](this, A, B);
}

void Engine::Physics::Manifold::Initialize(void) {
  // Calculate average restitution
  e = std::min(A->restitution, B->restitution);

  // Calculate static and dynamic friction
  sf = std::sqrt(A->staticFriction * A->staticFriction);
  df = std::sqrt(A->dynamicFriction * A->dynamicFriction);

  for (uint32 i = 0; i < contact_count; ++i) {
    // Calculate radii from COM to contact
    Vector2 ra = contacts[i] - A->position;
    Vector2 rb = contacts[i] - B->position;

    Vector2 rv = B->velocity + Cross(B->angularVelocity, rb) -
      A->velocity - Cross(A->angularVelocity, ra);


    // Determine if we should perform a resting collision or not
    // The idea is if the only thing moving this object is gravity,
    // then the collision should be performed without any restitution
    if (rv.LenSqr() < (dt * gravity).LenSqr() + EPSILON) e = 0.0f;
  }
}

void Engine::Physics::Manifold::ApplyImpulse(void) {
  // Early out and positional correct if both objects have infinite mass
  if (Equal(A->im + B->im, 0)) {
    InfiniteMassCorrection();
    return;
  }

  for (uint32 i = 0; i < contact_count; ++i) {
    // Calculate radii from COM to contact
    Vector2 ra = contacts[i] - A->position;
    Vector2 rb = contacts[i] - B->position;

    // Relative velocity
    Vector2 rv = B->velocity + Cross(B->angularVelocity, rb) -
        A->velocity - Cross(A->angularVelocity, ra);

    // Relative velocity along the normal
    real32 contactVel = Dot(rv, normal);

    // Do not resolve if velocities are separating
    if (contactVel > 0) return;

    real32 raCrossN = Cross(ra, normal);
    real32 rbCrossN = Cross(rb, normal);
    real32 invMassSum = A->im + B->im + Sqr(raCrossN) * A->iI + Sqr(rbCrossN) * B->iI;

    // Calculate impulse scalar
    real32 j = -(1.0f + e) * contactVel;
    j /= invMassSum;
    j /= (real32)contact_count;

    // Apply impulse
    Vector2 impulse = normal * j;
    A->ApplyImpulse(-impulse, ra);
    B->ApplyImpulse(impulse, rb);

    // Friction impulse
    rv = B->velocity + Cross(B->angularVelocity, rb) - A->velocity - Cross(A->angularVelocity, ra);

    Vector2 t = rv - (normal * Dot(rv, normal));
    t.Normalize();

    // j tangent magnitude
    real32 jt = -Dot(rv, t);
    jt /= invMassSum;
    jt /= (real32)contact_count;

    // Don't apply tiny friction impulses
    if (Equal(jt, 0.0f)) return;

    // Coulumb's law
    Vector2 tangentImpulse;
    if (std::abs(jt) < j * sf) tangentImpulse = t * jt;
    else tangentImpulse = t * -j * df;

    // Apply friction impulse
    A->ApplyImpulse(-tangentImpulse, ra);
    B->ApplyImpulse(tangentImpulse, rb);
  }
}

void Engine::Physics::Manifold::PositionalCorrection(void) {
  const real32 k_slop = 0.05f; // Penetration allowance
  const real32 percent = 0.4f; // Penetration percentage to correct
  Vector2 correction = (std::max(penetration - k_slop, 0.0f) / (A->im + B->im)) * normal * percent;
  A->position -= correction * A->im;
  B->position += correction * B->im;
}

void Engine::Physics::Manifold::InfiniteMassCorrection(void) {
  A->velocity.Set(0, 0);
  B->velocity.Set(0, 0);
}
