#include "Engine\Physics\Manifold.h"
#include "Engine\Physics\Collision.h"

Engine::Physics::CollisionCallback Engine::Physics::Dispatch[(uint32)ShapeType::Count][(uint32)ShapeType::Count] =
{
	{
		Engine::Physics::CircletoCircle, Engine::Physics::CircletoPolygon
	},
	{
		Engine::Physics::PolygontoCircle, Engine::Physics::PolygontoPolygon
	},
};

void Engine::Physics::CircletoCircle(Manifold *m, Body *a, Body *b)
{
	Circle *A = reinterpret_cast<Circle *>(a->shape);
	Circle *B = reinterpret_cast<Circle *>(b->shape);

	// Calculate translational vector, which is normal
	Vector2 normal = b->position - a->position;

	real32 dist_sqr = normal.LenSqr();
	real32 radius = A->radius + B->radius;

	// Not in contact
	if (dist_sqr >= radius * radius)
	{
		m->contact_count = 0;
		return;
	}

	real32 distance = std::sqrt(dist_sqr);

	m->contact_count = 1;

	if (distance == 0.0f)
	{
		m->penetration = A->radius;
		m->normal = Vector2(1, 0);
		m->contacts[0] = a->position;
	}
	else
	{
		m->penetration = radius - distance;
		m->normal = normal / distance; // Faster than using Normalized since we already performed sqrt
		m->contacts[0] = m->normal * A->radius + a->position;
	}
}

void Engine::Physics::CircletoPolygon(Manifold *m, Body *a, Body *b)
{
	Circle *A = reinterpret_cast<Circle *>      (a->shape);
	PolygonShape *B = reinterpret_cast<PolygonShape *>(b->shape);

	m->contact_count = 0;

	// Transform circle center to Polygon model space
	Vector2 center = a->position;
	center = B->u.Transpose() * (center - b->position);

	// Find edge with minimum penetration
	// Exact concept as using support points in Polygon vs Polygon
	real32 separation = -FLT_MAX;
	uint32 faceNormal = 0;
	for (uint32 i = 0; i < B->m_vertexCount; ++i)
	{
		real32 s = Dot(B->m_normals[i], center - B->m_vertices[i]);

		if (s > A->radius)
			return;

		if (s > separation)
		{
			separation = s;
			faceNormal = i;
		}
	}

	// Grab face's vertices
	Vector2 v1 = B->m_vertices[faceNormal];
	uint32 i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
	Vector2 v2 = B->m_vertices[i2];

	// Check to see if center is within polygon
	if (separation < EPSILON)
	{
		m->contact_count = 1;
		m->normal = -(B->u * B->m_normals[faceNormal]);
		m->contacts[0] = m->normal * A->radius + a->position;
		m->penetration = A->radius;
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	real32 dot1 = Dot(center - v1, v2 - v1);
	real32 dot2 = Dot(center - v2, v1 - v2);
	m->penetration = A->radius - separation;

	// Closest to v1
	if (dot1 <= 0.0f)
	{
		if (DistSqr(center, v1) > A->radius * A->radius)
			return;

		m->contact_count = 1;
		Vector2 n = v1 - center;
		n = B->u * n;
		n.Normalize();
		m->normal = n;
		v1 = B->u * v1 + b->position;
		m->contacts[0] = v1;
	}

	// Closest to v2
	else if (dot2 <= 0.0f)
	{
		if (DistSqr(center, v2) > A->radius * A->radius)
			return;

		m->contact_count = 1;
		Vector2 n = v2 - center;
		v2 = B->u * v2 + b->position;
		m->contacts[0] = v2;
		n = B->u * n;
		n.Normalize();
		m->normal = n;
	}

	// Closest to face
	else
	{
		Vector2 n = B->m_normals[faceNormal];
		if (Dot(center - v1, n) > A->radius)
			return;

		n = B->u * n;
		m->normal = -n;
		m->contacts[0] = m->normal * A->radius + a->position;
		m->contact_count = 1;
	}
}

void Engine::Physics::PolygontoCircle(Manifold *m, Body *a, Body *b)
{
	CircletoPolygon(m, b, a);
	m->normal = -m->normal;
}

real32 FindAxisLeastPenetration(uint32 *faceIndex, Engine::Physics::PolygonShape *A, Engine::Physics::PolygonShape *B)
{
	real32 bestDistance = -FLT_MAX;
	uint32 bestIndex;

	for (uint32 i = 0; i < A->m_vertexCount; ++i)
	{
		// Retrieve a face normal from A
		Vector2 n = A->m_normals[i];
		Vector2 nw = A->u * n;

		// Transform face normal into B's model space
		Mat2 buT = B->u.Transpose();
		n = buT * nw;

		// Retrieve support point from B along -n
		Vector2 s = B->GetSupport(-n);

		// Retrieve vertex on face from A, transform into
		// B's model space
		Vector2 v = A->m_vertices[i];
		v = A->u * v + A->body->position;
		v -= B->body->position;
		v = buT * v;

		// Compute penetration distance (in B's model space)
		real32 d = Dot(n, s - v);

		// Store greatest distance
		if (d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	*faceIndex = bestIndex;
	return bestDistance;
}

void FindIncidentFace(Vector2 *v, Engine::Physics::PolygonShape *RefPoly, Engine::Physics::PolygonShape *IncPoly, uint32 referenceIndex)
{
	Vector2 referenceNormal = RefPoly->m_normals[referenceIndex];

	// Calculate normal in incident's frame of reference
	referenceNormal = RefPoly->u * referenceNormal; // To world space
	referenceNormal = IncPoly->u.Transpose() * referenceNormal; // To incident's model space

	// Find most anti-normal face on incident polygon
	int32 incidentFace = 0;
	real32 minDot = FLT_MAX;
	for (uint32 i = 0; i < IncPoly->m_vertexCount; ++i)
	{
		real32 dot = Dot(referenceNormal, IncPoly->m_normals[i]);
		if (dot < minDot)
		{
			minDot = dot;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->body->position;
	incidentFace = incidentFace + 1 >= (int32)IncPoly->m_vertexCount ? 0 : incidentFace + 1;
	v[1] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->body->position;
}

int32 Clip(Vector2 n, real32 c, Vector2 *face)
{
	uint32 sp = 0;
	Vector2 out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c
	real32 d1 = Dot(n, face[0]) - c;
	real32 d2 = Dot(n, face[1]) - c;

	// If negative (behind plane) clip
	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		real32 alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	assert(sp != 3);

	return sp;
}

void Engine::Physics::PolygontoPolygon(Manifold *m, Body *a, Body *b)
{
	PolygonShape *A = reinterpret_cast<PolygonShape *>(a->shape);
	PolygonShape *B = reinterpret_cast<PolygonShape *>(b->shape);
	m->contact_count = 0;

	// Check for a separating axis with A's face planes
	uint32 faceA;
	real32 penetrationA = FindAxisLeastPenetration(&faceA, A, B);
	if (penetrationA >= 0.0f)
		return;

	// Check for a separating axis with B's face planes
	uint32 faceB;
	real32 penetrationB = FindAxisLeastPenetration(&faceB, B, A);
	if (penetrationB >= 0.0f)
		return;

	uint32 referenceIndex;
	bool flip; // Always point from a to b

	PolygonShape *RefPoly; // Reference
	PolygonShape *IncPoly; // Incident

	// Determine which shape contains reference face
	if (BiasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = A;
		IncPoly = B;
		referenceIndex = faceA;
		flip = false;
	}

	else
	{
		RefPoly = B;
		IncPoly = A;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	Vector2 incidentFace[2];
	FindIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);

	//        y
	//        ^  ->n       ^
	//      +---c ------posPlane--
	//  x < | i |\
	  //      +---+ c-----negPlane--
	//             \       v
	//              r
	//
	//  r : reference face
	//  i : incident poly
	//  c : clipped point
	//  n : incident normal

	// Setup reference face vertices
	Vector2 v1 = RefPoly->m_vertices[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->m_vertexCount ? 0 : referenceIndex + 1;
	Vector2 v2 = RefPoly->m_vertices[referenceIndex];

	// Transform vertices to world space
	v1 = RefPoly->u * v1 + RefPoly->body->position;
	v2 = RefPoly->u * v2 + RefPoly->body->position;

	// Calculate reference face side normal in world space
	Vector2 sidePlaneNormal = (v2 - v1);
	sidePlaneNormal.Normalize();

	// Orthogonalize
	Vector2 refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

	// ax + by = c
	// c is distance from origin
	real32 refC = Dot(refFaceNormal, v1);
	real32 negSide = -Dot(sidePlaneNormal, v1);
	real32 posSide = Dot(sidePlaneNormal, v2);

	// Clip incident face to reference face side planes
	if (Clip(-sidePlaneNormal, negSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points

	// Flip
	m->normal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	uint32 cp = 0; // clipped points behind reference face
	real32 separation = Dot(refFaceNormal, incidentFace[0]) - refC;
	if (separation <= 0.0f)
	{
		m->contacts[cp] = incidentFace[0];
		m->penetration = -separation;
		++cp;
	}
	else
		m->penetration = 0;

	separation = Dot(refFaceNormal, incidentFace[1]) - refC;
	if (separation <= 0.0f)
	{
		m->contacts[cp] = incidentFace[1];

		m->penetration += -separation;
		++cp;

		// Average penetration
		m->penetration /= (real32)cp;
	}

	m->contact_count = cp;
}
