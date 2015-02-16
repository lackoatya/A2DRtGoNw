#pragma once

#include "Engine\Types.h"

namespace Engine
{
	namespace Physics
	{
		struct Shape;

		struct Body
		{
			Body() = delete;
			Body(Shape * _shape, uint32 const& _x, uint32 const& _y);
			Body(Body const& _other) = delete;
			Body & operator=(Body const& _other) = delete;
			// QUESTION: Should this be custom? Like release shape?
			~Body() = default;

			inline void ApplyForce(Vector2 const& _f) { force += _f; }
			inline void ApplyImpulse(Vector2 const& _impulse, Vector2 const& _contact) { velocity += im * _impulse; angularVelocity += iI * Cross(_contact, _impulse); }

			// QUESTION: Is this called multiple times?
			void SetStatic(void)
			{
				I = 0.0f;
				iI = 0.0f;
				m = 0.0f;
				im = 0.0f;
			}

			void SetOrient(real32 const& _radians);

			Vector2 position;
			Vector2 velocity;

			real32 angularVelocity;
			real32 torque;
			real32 orient; // radians

			Vector2 force;

			// Set by shape
			real32 I;  // moment of inertia
			real32 iI; // inverse inertia
			real32 m;  // mass
			real32 im; // inverse masee

			real32 staticFriction;
			real32 dynamicFriction;
			real32 restitution;

			// Shape interface
			Shape * shape;
		};
	}
}