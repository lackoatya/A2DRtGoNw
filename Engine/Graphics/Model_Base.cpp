#include <iostream>

#include "Engine\Graphics\Model_Base.h"

void Engine::Graphics::Model_Base::SetFrame(uint32 const& _frame)
{
	std::cout << "Setting Frame " << _frame << std::endl;

	frame = _frame;
	/*uint32 next_frame = frame + 1;
	if (next_frame == mesh->animations[animation]->frames_count)
	{
		next_frame = 0;
		interpolation_current->time -= interpolation_start->time;
	}*/

	interpolation_end->time = mesh->animations[animation]->frames[frame]->end;
	for (uint32 current = 0; current < mesh->animations[animation]->frames[frame]->transformations_count; ++current)
		interpolation_end->rotations[mesh->animations[animation]->frames[frame]->transformations[current]->index] = mesh->animations[animation]->frames[frame]->transformations[current]->rotation;
}

void Engine::Graphics::Model_Base::Animate(uint32 const& _animation)
{
	animation = _animation;

	SetFrame(0);
}


void Engine::Graphics::Model_Base::Update(real32 const& _elapsed_time)
{
	interpolation_current->time += _elapsed_time;

	if (interpolation_end->time < interpolation_current->time)
	{
		// TODO Handle loop/single animation

		uint32 next_frame = frame +1;
		if (next_frame == mesh->animations[animation]->frames_count)
		{
			next_frame = 0;
			interpolation_current->time -= interpolation_end->time;
		}

		Interpolation_Base * swap = interpolation_start;
		interpolation_start = interpolation_end;
		interpolation_end = swap;

		SetFrame(next_frame);
	}

	real32 dt = (interpolation_current->time - interpolation_start->time) / (interpolation_end->time - interpolation_start->time);
	for (uint32 element = 0; element < mesh->elements_count; ++element)
		interpolation_current->rotations[element] = interpolation_start->rotations[element] + (interpolation_end->rotations[element] - interpolation_start->rotations[element]) * dt;
}