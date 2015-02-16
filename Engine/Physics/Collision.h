#pragma once

#include "Engine\Types.h"
#include "Engine\Physics\Shape.h"

namespace Engine
{
	namespace Physics
	{
		struct Manifold;
		struct Body;

		typedef void(*CollisionCallback)(Manifold *m, Body *a, Body *b);

		extern CollisionCallback Dispatch[(uint32)ShapeType::Count][(uint32)ShapeType::Count];

		void CircletoCircle(Manifold *m, Body *a, Body *b);
		void CircletoPolygon(Manifold *m, Body *a, Body *b);
		void PolygontoCircle(Manifold *m, Body *a, Body *b);
		void PolygontoPolygon(Manifold *m, Body *a, Body *b);
	}
}