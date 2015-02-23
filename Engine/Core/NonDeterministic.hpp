#pragma once

#include <boost\chrono.hpp>

#include "Engine\Types.h"

namespace Engine
{
	namespace Core
	{
		template < class Processable, class Result >
		static Result NonDeterministic(Processable & _instance, real32 const& _interval)
		{
			real32 elapsed_time = 0.;
			boost::chrono::steady_clock::time_point now, last_time = boost::chrono::steady_clock::now();

			do
			{
				now = boost::chrono::steady_clock::now();
				elapsed_time += (now - last_time).count();	//boost::chrono::duration< real32 > difference = ;
				last_time = now;

				if (_interval < elapsed_time)
				{
					Result result = _instance.Process();
					if (result.Valid()) return result;

					elapsed_time = 0.;
				}
			} while (true);
		}
	}
}