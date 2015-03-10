#include "Engine\Graphics\Model_Base.h"

void Engine::Graphics::Model_Base::SetFrame(uint32 const& _frame)
{
	frame = _frame;

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
		uint32 next_frame = frame +1;
		if (next_frame == mesh->animations[animation]->frames_count)
		{
			next_frame = 0;
			interpolation_current->time -= interpolation_end->time;
                        interpolation_end->time -= mesh->animations[animation]->frames[mesh->animations[animation]->frames_count - 1]->end;
		}

		Interpolation_Base * swap = interpolation_start;
		interpolation_start = interpolation_end;
		interpolation_end = swap;

		SetFrame(next_frame);
	}

	real32 dt = (interpolation_current->time - interpolation_start->time) / (interpolation_end->time - interpolation_start->time);
	for (uint32 element = 0; element < mesh->elements_count; ++element)
		interpolation_current->rotations[element] = interpolation_start->rotations[element] + (interpolation_end->rotations[element] - interpolation_start->rotations[element]) * dt;

        Update_ElementCenters(0);
}

void Engine::Graphics::Model_Base::Update_ElementCenters(uint32 const& _element_index)
{
        for (uint32 current = 0; current < mesh->elements[_element_index]->joints_count; ++current)
        {
                Vector2 owner = mesh->elements[_element_index]->joints[current]->owner_location;
                owner.Rotate_Degree(interpolation_current->rotations[_element_index]);
                Vector2 target = mesh->elements[_element_index]->joints[current]->target_location;
                target.Rotate_Degree(interpolation_current->rotations[mesh->elements[_element_index]->joints[current]->target_index]);
                element_centers[mesh->elements[_element_index]->joints[current]->target_index] = owner - target + element_centers[_element_index];

                Update_ElementCenters(mesh->elements[_element_index]->joints[current]->target_index);
        }
}