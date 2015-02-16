#include <iostream>

#include "Engine\Physics\Body.h"
#include "Engine\Physics\Shape.h"
#include "Engine\Physics\Manifold.h"
#include "Engine\Physics\Reality.h"

Engine::Physics::Reality::Reality(real32 const& _interval) :
	interval(_interval)
{
	Circle c(5.0f);
	Body *b = Add(&c, 40, 40);
	b->SetStatic();

	PolygonShape poly;
	poly.SetBox(30.0f, 1.0f);
	b = Add(&poly, 40, 55);
	b->SetStatic();
	b->SetOrient(0);
}

// Acceleration
//    F = mA
// => A = F * 1/m

// Explicit Euler
// x += v * dt
// v += (1/m * F) * dt

// Semi-Implicit (Symplectic) Euler
// v += (1/m * F) * dt
// x += v * dt

// see http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html

void IntegrateForces(Engine::Physics::Body *b, real32 const& _interval)
{
	if (b->im == 0.0f) return;

	b->velocity += (b->force * b->im + gravity) * (_interval / 2.0f);
	b->angularVelocity += b->torque * b->iI * (_interval / 2.0f);
}

void IntegrateVelocity(Engine::Physics::Body *b, real32 const& _interval)
{
	if (b->im == 0.0f) return;

	b->position += b->velocity * _interval;
	b->orient += b->angularVelocity * _interval;
	b->SetOrient(b->orient);
	IntegrateForces(b, _interval);
}

void Engine::Physics::Reality::Process(void)
{
	// Generate new collision info
	contacts.clear();
	for (uint32 i = 0; i < bodies.size(); ++i)
	{
		Body *A = bodies[i];

		for (uint32 j = i + 1; j < bodies.size(); ++j)
		{
			Body *B = bodies[j];
			if (A->im == 0 && B->im == 0)
				continue;
			Manifold m(A, B);
			m.Solve();
			if (m.contact_count)
				contacts.emplace_back(m);
		}
	}

	// Integrate forces
	for (uint32 i = 0; i < bodies.size(); ++i)
		IntegrateForces(bodies[i], interval);

	// Initialize collision
	for (uint32 i = 0; i < contacts.size(); ++i)
		contacts[i].Initialize();

	// Solve collisions
	for (uint32 j = 0; j < m_iterations; ++j)
		for (uint32 i = 0; i < contacts.size(); ++i)
			contacts[i].ApplyImpulse();

	// Integrate velocities
	for (uint32 i = 0; i < bodies.size(); ++i)
		IntegrateVelocity(bodies[i], interval);

	// Correct positions
	for (uint32 i = 0; i < contacts.size(); ++i)
		contacts[i].PositionalCorrection();

	// Clear all forces
	for (uint32 i = 0; i < bodies.size(); ++i)
	{
		Body *b = bodies[i];
		b->force.Set(0, 0);
		b->torque = 0;
	}
}

Engine::Physics::Body * Engine::Physics::Reality::Add(Shape *shape, uint32 x, uint32 y)
{
	assert(shape);
	Body *b = new Body(shape, x, y);
	bodies.push_back(b);
	return b;
}
