#include <fstream>

#include "Engine\Graphics\Mesh.h"

void ReadPlaceholder(std::ifstream & _file)
{
        std::string placeholder;
        _file >> placeholder;
        std::getline(_file, placeholder);
}

Engine::Graphics::Mesh::Mesh(std::string && _mesh_path)
{
        std::string placeholder;

        std::ifstream file(_mesh_path);
	assert(!file.fail() && "Error while opening mesh!");

        ReadPlaceholder(file);

	file >> elements_count;

	elements = new Element*[elements_count];

        depth_indexes = new uint32[elements_count];
        memset(depth_indexes, 0, sizeof(depth_indexes));

	for (uint32 current_element = 0; current_element < elements_count; ++current_element)
	{
                ReadPlaceholder(file);

                int32 depth = 0, joints_count = 0;

		file >> depth >> joints_count;

                depth_indexes[depth] = current_element;

		Element::Joint ** joints = new Element::Joint*[joints_count];

		for (uint32 current_joint = 0; current_joint < joints_count; ++current_joint)
		{
			uint32 target_index = 0;
			real32 owner_x = 0.f, owner_y = 0.f, target_x = 0.f, target_y = 0.f;

			file >> owner_x >> owner_y >> target_index >> target_x >> target_y;

			joints[current_joint] = new Element::Joint(Vector2(owner_x, owner_y), target_index, Vector2(target_x, target_y));
		}

		elements[current_element] = new Element(current_element, depth, joints_count, joints);
	}

        ReadPlaceholder(file);

	file >> animations_count;

	animations = new Animation*[animations_count];

	for (uint32 current_animation = 0; current_animation < animations_count; ++current_animation)
	{
                ReadPlaceholder(file);

		uint32 frames_count = 0;

		file >> frames_count;

		Animation::Frame ** frames = new Animation::Frame*[frames_count];
		for (uint32 current_frame = 0; current_frame < frames_count; ++current_frame)
		{
                        ReadPlaceholder(file);

			real32 end = 0.f;
			uint32 transformations_count = 0;

			file >> end >> transformations_count;

			Animation::Frame::Transformation ** transformations = new Animation::Frame::Transformation*[transformations_count];
			
			for (uint32 current_transformation = 0; current_transformation < transformations_count; ++current_transformation)
			{
				uint32 index = 0;
				real32 rotation = 0.f;

				file >> index >> rotation;

				transformations[current_transformation] = new Animation::Frame::Transformation(index, rotation);
			}

			frames[current_frame] = new Animation::Frame(end, transformations_count, transformations);
		}

		animations[current_animation] = new Animation(frames_count, frames);
	}

	file.close();
}