#include <fstream>

#include "Engine\Graphics\Model_Base.h"
#include "Engine\Graphics\Texture_Base.h"

Engine::Graphics::Element_Base::Element_Base(uint8 const& _index, uint8 const& _depth, std::string const& _texture_path) :
	index(_index),
	depth(_depth),
	texture(new Engine::Graphics::Texture_Base(_texture_path.c_str()))
{

}

Engine::Graphics::Model_Base::Model_Base(std::string const& _path, std::string const& _name, Vector2 const& _location) :
	location(_location)
{
	std::ifstream file(_path + "\\" + _name + "\\" + _name + ".model");
	// TODO assert file

	// Elements
	uint32 element_count = 0, main_index; file >> element_count >> main_index;
	for (uint32 current = 0; current < element_count; ++current)
	{
		std::string texture_name; uint32 depth; file >> texture_name >> depth;
		elements.push_back(new Element_Base(current, depth, _path + "\\" + _name + "\\" + texture_name));
	}

	main_element = elements[main_index];

	// Joints
	uint32 joint_count = 0; file >> joint_count;
	for (uint32 current = 0; current < joint_count; ++current)
	{
		uint32 owner = 0, target = 0;
		real32 owner_x = 0.f, owner_y = 0.f, target_x = 0.f, target_y = 0.f;
		file >> owner >> owner_x >> owner_y >> target >> target_x >> target_y;
		elements[owner]->joints.push_back(new Element_Base::Joint_Base(Vector2(owner_x, owner_y), elements[target], Vector2(target_x, target_y)));
	}

	// Animation
	uint32 animation_count = 0; file >> animation_count;
	for (uint32 current = 0; current < animation_count; ++current)
	{
		Animation_Base * animation = new Animation_Base();

		uint32 frame_count = 0; file >> frame_count;
		for (uint32 current_frame = 0; current_frame < frame_count; ++current_frame)
		{
			real32 duration = 0.f; file >> duration;
			Animation_Base::Frame_Base * frame = new Animation_Base::Frame_Base(duration);

			uint32 transformation_count = 0; file >> transformation_count;
			for (uint32 current_transformation = 0; current_transformation < transformation_count; ++current_transformation)
			{
				uint32 index = 0; real32 rotation = 0.f; file >> index >> rotation;
				frame->transformations.push_back(new Animation_Base::Frame_Base::Frame_Transformation(index, rotation));
			}

			animation->frames.push_back(frame);
		}

		animations.push_back(animation);
	}

	file.close();
}

Engine::Graphics::Model_Base::~Model_Base()
{
	delete main_element;
	main_element = nullptr;
}