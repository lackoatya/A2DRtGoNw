#pragma once

#include "Engine\Types.h"
#include "Engine\Physics\Body.h"

// TODO Remove this!
#define MaxPolyVertexCount 64

namespace Engine
{
	namespace Physics
	{
		enum class ShapeType
		{
			Circle,
			Polygon,
			Count
		};

		///
		struct Shape
		{
			// TODO Replace this and add?
			/*Shape() { }
			virtual ~Shape() { }*/

			virtual Shape *Clone(void) const = 0;
			virtual void Initialize(void) = 0;
			virtual void ComputeMass(real32 const& _density) = 0;
			virtual void SetOrient(real32 const& _radians) = 0;
			virtual ShapeType GetType(void) const = 0;

			Body * body = nullptr;

			// TODO I don't like this at all!
			// For circle shape
			real32 radius = 0.f;

			// For Polygon shape
			Mat2 u; // Orientation matrix from model to world
		};


		///
		struct Circle :
			public Shape
		{
			inline Circle() = delete;
			inline Circle(real32 const& _r) { radius = _r; }
			inline Circle(Circle const& _other) = delete;
			inline Circle & operator=(Circle const& _other) = delete;
			inline ~Circle() = default;

			Shape * Clone(void) const { return new Circle(radius); }

			// TODO move this to constructor?
			inline void Initialize(void) { ComputeMass(1.0f); }
			inline void ComputeMass(real32 const& _density)
			{
				body->m = PI * radius * radius * _density;
				body->im = (body->m) ? 1.0f / body->m : 0.0f;
				body->I = body->m * radius * radius;
				body->iI = (body->I) ? 1.0f / body->I : 0.0f;
			}

			inline void SetOrient(real32 const& _radians) { }
			inline ShapeType GetType(void) const { return ShapeType::Circle; }
		};
		
		///
		struct PolygonShape :
			public Shape
		{
			inline void Initialize(void) { ComputeMass(1.0f); }

			Shape *Clone(void) const
			{
				PolygonShape *poly = new PolygonShape();
				poly->u = u;
				for (uint32 i = 0; i < m_vertexCount; ++i)
				{
					poly->m_vertices[i] = m_vertices[i];
					poly->m_normals[i] = m_normals[i];
				}
				poly->m_vertexCount = m_vertexCount;
				return poly;
			}

			void ComputeMass(real32 const& _density)
			{
				// Calculate centroid and moment of interia
				Vector2 c(0.0f, 0.0f); // centroid
				real32 area = 0.0f;
				real32 I = 0.0f;
				const real32 k_inv3 = 1.0f / 3.0f;

				for (uint32 i1 = 0; i1 < m_vertexCount; ++i1)
				{
					// Triangle vertices, third vertex implied as (0, 0)
					Vector2 p1(m_vertices[i1]);
					uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
					Vector2 p2(m_vertices[i2]);

					real32 D = Cross(p1, p2);
					real32 triangleArea = 0.5f * D;

					area += triangleArea;

					// Use area to weight the centroid average, not just vertex position
					c += triangleArea * k_inv3 * (p1 + p2);

					real32 intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
					real32 inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
					I += (0.25f * k_inv3 * D) * (intx2 + inty2);
				}

				c *= 1.0f / area;

				// Translate vertices to centroid (make the centroid (0, 0)
				// for the polygon in model space)
				// Not really necessary, but I like doing this anyway
				for (uint32 i = 0; i < m_vertexCount; ++i)
					m_vertices[i] -= c;

				// QUESTION: Isn1t this like SetStatic?
				body->m = _density * area;
				body->im = (body->m) ? 1.0f / body->m : 0.0f;
				body->I = I * _density;
				body->iI = body->I ? 1.0f / body->I : 0.0f;
			}

			inline void SetOrient(real32 const& _radians) { u.Set(_radians); }

			inline ShapeType GetType(void) const { return ShapeType::Polygon; }

			// Half width and half height
			void SetBox(real32 hw, real32 hh)
			{
				m_vertexCount = 4;
				m_vertices[0].Set(-hw, -hh);
				m_vertices[1].Set(hw, -hh);
				m_vertices[2].Set(hw, hh);
				m_vertices[3].Set(-hw, hh);
				m_normals[0].Set(0.0f, -1.0f);
				m_normals[1].Set(1.0f, 0.0f);
				m_normals[2].Set(0.0f, 1.0f);
				m_normals[3].Set(-1.0f, 0.0f);
			}

			void Set(Vector2 *vertices, uint32 count)
			{
				// No hulls with less than 3 vertices (ensure actual polygon)
				assert(count > 2 && count <= MaxPolyVertexCount);
				count = std::min((int32)count, MaxPolyVertexCount);

				// Find the right most point on the hull
				int32 rightMost = 0;
				real32 highestXCoord = vertices[0].x;
				for (uint32 i = 1; i < count; ++i)
				{
					real32 x = vertices[i].x;
					if (x > highestXCoord)
					{
						highestXCoord = x;
						rightMost = i;
					}

					// If matching x then take farthest negative y
					else if (x == highestXCoord)
						if (vertices[i].y < vertices[rightMost].y)
							rightMost = i;
				}

				int32 hull[MaxPolyVertexCount];
				int32 outCount = 0;
				int32 indexHull = rightMost;

				for (;;)
				{
					hull[outCount] = indexHull;

					// Search for next index that wraps around the hull
					// by computing cross products to find the most counter-clockwise
					// vertex in the set, given the previos hull index
					int32 nextHullIndex = 0;
					for (int32 i = 1; i < (int32)count; ++i)
					{
						// Skip if same coordinate as we need three unique
						// points in the set to perform a cross product
						if (nextHullIndex == indexHull)
						{
							nextHullIndex = i;
							continue;
						}

						// Cross every set of three unique vertices
						// Record each counter clockwise third vertex and add
						// to the output hull
						// See : http://www.oocities.org/pcgpe/math2d.html
						Vector2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
						Vector2 e2 = vertices[i] - vertices[hull[outCount]];
						real32 c = Cross(e1, e2);
						if (c < 0.0f)
							nextHullIndex = i;

						// Cross product is zero then e vectors are on same line
						// therefor want to record vertex farthest along that line
						if (c == 0.0f && e2.LenSqr() > e1.LenSqr())
							nextHullIndex = i;
					}

					++outCount;
					indexHull = nextHullIndex;

					// Conclude algorithm upon wrap-around
					if (nextHullIndex == rightMost)
					{
						m_vertexCount = outCount;
						break;
					}
				}

				// Copy vertices into shape's vertices
				for (uint32 i = 0; i < m_vertexCount; ++i)
					m_vertices[i] = vertices[hull[i]];

				// Compute face normals
				for (uint32 i1 = 0; i1 < m_vertexCount; ++i1)
				{
					uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
					Vector2 face = m_vertices[i2] - m_vertices[i1];

					// Ensure no zero-length edges, because that's bad
					assert(face.LenSqr() > EPSILON * EPSILON);

					// Calculate normal with 2D cross product between vector and scalar
					m_normals[i1] = Vector2(face.y, -face.x);
					m_normals[i1].Normalize();
				}
			}

			// The extreme point along a direction within a polygon
			Vector2 GetSupport(const Vector2& dir)
			{
				real32 bestProjection = -FLT_MAX;
				Vector2 bestVertex;

				for (uint32 i = 0; i < m_vertexCount; ++i)
				{
					Vector2 v = m_vertices[i];
					real32 projection = Dot(v, dir);

					if (projection > bestProjection)
					{
						bestVertex = v;
						bestProjection = projection;
					}
				}

				return bestVertex;
			}

			uint32 m_vertexCount;
			Vector2 m_vertices[MaxPolyVertexCount];
			Vector2 m_normals[MaxPolyVertexCount];
		};
	}
}
