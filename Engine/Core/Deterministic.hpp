#pragma once

#include <boost\chrono.hpp>

#include "Engine\Types.h"

namespace Engine
{
	namespace Core
	{
		template < class Processable >
		static void Deterministic(real32 const& _interval)
		{
			Processable instance;

			real32 elapsed_time = 0.;
			boost::chrono::steady_clock::time_point now, last_time = boost::chrono::steady_clock::now();

			do
			{
				now = boost::chrono::steady_clock::now();
				elapsed_time += (now - last_time).count(); // boost::chrono::duration<float> difference = ;
				last_time = now;

				while (_interval < elapsed_time)
				{
					instance.Update();

					elapsed_time -= _interval;
				}
			} while (instance.Valid());
		}
	}
}