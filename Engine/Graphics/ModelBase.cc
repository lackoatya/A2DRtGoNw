#include "Engine/Graphics/ModelBase.h"

namespace Engine {
namespace Graphics {
void ModelBase::SetFrame(uint32 const& _frame) {
  frame_ = _frame;

  interpolation_end->time = mesh_->animations[animation_]->frames[frame_]->end;
  Mesh::Animation::Frame * current_frame = mesh_->animations[animation_]->frames[frame_];
  for (uint32 current = 0; current < current_frame->transformations_count; ++current)
    interpolation_end->rotations[current_frame->transformations[current]->index]
        = current_frame->transformations[current]->rotation;
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
  for (uint32 current = 0; current < mesh_->elements[_element_index]->joints_count; ++current) {
    uint32 target_index = mesh_->elements[_element_index]->joints[current]->target_index;

    Vector2 owner = mesh_->elements[_element_index]->joints[current]->owner_location;
    owner.Rotate_Degree(interpolation_current->rotations[_element_index]);

    Vector2 target = mesh_->elements[_element_index]->joints[current]->target_location;
    target.Rotate_Degree(interpolation_current->rotations[target_index]);

    element_centers[target_index] = owner - target + element_centers[_element_index];

    Update_ElementCenters(target_index);
  }
}

}
}
