#include "Engine/Graphics/ModelBase.h"

namespace Engine {
namespace Graphics {
void ModelBase::SetFrame(uint32 const& _frame) {
  frame_ = _frame;

  interpolation_end->time = mesh_->animations[animation_]->frames[frame_]->end;
  Mesh::Animation::Frame * current_frame = mesh_->animations[animation_]->frames[frame_];
  for (uint32 current = 0; current < current_frame->transformations_count; ++current) {
    Mesh::Animation::Frame::Transformation * current_transformation =
        current_frame->transformations[current];

    interpolation_end->rotations[current_transformation->index] = current_transformation->rotation;

    for (uint32 binding = 0;
         binding < mesh_->elements[current_transformation->index]->bindings_count;
         ++binding) {
      Mesh::Element * curr_bind = mesh_->elements[current_transformation->index];

      interpolation_end->rotations[curr_bind->bindings[binding]->target_index] =
        current_transformation->rotation + curr_bind->bindings[binding]->angle;
    }
  }
}

void ModelBase::Animate(uint32 const& _animation) {
  animation_ = _animation;
  SetFrame(0);
}

void ModelBase::Update(real32 const& _elapsed_time) {
  interpolation_current->time += _elapsed_time;

  if (interpolation_end->time < interpolation_current->time) {
    uint32 next_frame = frame_ + 1;
    int32 last_frame = mesh_->animations[animation_]->frames_count - 1;

    if (next_frame == mesh_->animations[animation_]->frames_count) {
      next_frame = 0;
      interpolation_current->time -= interpolation_end->time;
      interpolation_end->time -= mesh_->animations[animation_]->frames[last_frame]->end;
    }

    InterpolationBase * swap = interpolation_start;
    interpolation_start = interpolation_end;
    interpolation_end = swap;

    SetFrame(next_frame);
  }

  real32 dt = (interpolation_current->time - interpolation_start->time) /
      (interpolation_end->time - interpolation_start->time);

  for (uint32 element = 0; element < mesh_->elements_count; ++element)
    interpolation_current->rotations[element] = interpolation_start->rotations[element] +
        (interpolation_end->rotations[element] - interpolation_start->rotations[element]) * dt;

  Update_ElementCenters(0);
}

void ModelBase::Update_ElementCenters(uint32 const& _element_index) {
  for (uint32 current = 0; current < mesh_->elements[_element_index]->joints_count; ++current)
    Update_ElementJoint(_element_index, mesh_->elements[_element_index]->joints[current]);

  for (uint32 current = 0; current < mesh_->elements[_element_index]->bindings_count; ++current)
    Update_ElementJoint(_element_index, mesh_->elements[_element_index]->bindings[current]);
}

void ModelBase::Update_ElementJoint(uint32 const& _element_index, Mesh::Element::Joint * _joint) {
  uint32 target_index = _joint->target_index;

  Vector2 owner = _joint->owner_location;
  owner.Rotate_Degree(interpolation_current->rotations[_element_index]);

  Vector2 target = _joint->target_location;
  target.Rotate_Degree(interpolation_current->rotations[target_index]);

  element_centers[target_index] = owner - target + element_centers[_element_index];

  Update_ElementCenters(target_index);
}
}
}
