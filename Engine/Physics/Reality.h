#pragma once

#include <vector>

#include "Engine\Types.h"
#include "Engine\Core\Processable.h"
#include "Engine\Physics\Manifold.h"

namespace Engine
{
	namespace Physics
	{
		struct Body;
		struct Shape;

		class Reality // :
			//public Core::Processable
		{
		public:
			Reality() = delete;
			Reality(real32 const& _interval);
			Reality(Reality const&) = delete;
			Reality & operator=(Reality const&) = delete;
			~Reality(void) = default;

			inline uint8 Valid(void) { return true; }
			void Process(void);

			Body *Add(Shape *shape, uint32 x, uint32 y);

		private:
			const real32 interval;

			// QUESTION: what is this?
			uint32 m_iterations = 10;
			std::vector< Body * > bodies;
			std::vector< Manifold > contacts;
		};
	}
}