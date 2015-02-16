#pragma once

#include <boost\chrono.hpp>

#include "Engine\Types.h"

namespace Engine
{
	namespace Core
	{
		template < class Deterministic_Processable, class NonDeterministic_Processable >
		static void Interpolated(real32 const& _deterministic_interval, real32 const& _nondeterministic_interval)
		{
			Deterministic_Processable model(_deterministic_interval);
			NonDeterministic_Processable < Deterministic_Processable > view;

			real32 elapsed_time = 0., elapsed_model_time = 0., elapsed_view_time = 0.;
			boost::chrono::steady_clock::time_point now, last_time = boost::chrono::steady_clock::now();

			do
			{
				now = boost::chrono::steady_clock::now();
				elapsed_frame_time = (now - last_time).count();
				elapsed_model_time += elapsed_frame_time;
				elapsed_view_time += elapsed_frame_time;	// boost::chrono::duration<float> difference = ;
				last_time = now;

				while (_deterministic_interval < elapsed_model_time)
				{
					model.Process();

					elapsed_model_time -= _interval;
				}

				if (_nondeterministic_interval < elapsed_view_time)
				{
					view.Process();

					elapsed_view_time = 0.;
				}
			} while (model.Valid() && view.Valid());
		}
	}
}