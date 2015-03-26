#include "Engine/Graphics/ModelBase.h"

#include <assert.h>
#include <iostream>

namespace Engine {
namespace Graphics {
/*void ModelBase::SetFrame(uint32 const& _frame) {
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
}*/

void ModelBase::Animate(uint32 const& _animation) {
  typedef Engine::Graphics::Mesh::Element Element;
  typedef Engine::Graphics::Mesh::Animation Animation;
  typedef Engine::Graphics::Mesh::Animation::Frame Frame;
  typedef Engine::Graphics::Mesh::Animation::Frame::Transformation Transformation;

  Motion * motion = motion_;
  while (motion->next != nullptr) motion = motion->next;
  motion->next = new Motion(_animation);
  motion = motion->next;

  Animation * animation = mesh_->animations[motion->animation];
  Frame * frame = animation->frames[motion->frame];

  uint32 level = 0;
  Motion * current_motion = motion_;
  while (current_motion->next != nullptr) {
    level++;
    current_motion = current_motion->next;
  }

  for (uint32 current = 0; current < frame->transformations_count; ++current) {
    Transformation * transformation = frame->transformations[current];
    interpolation_->bases_[transformation->index]->Interpolate(level, frame->duration,
        transformation->rotation);

    Element * element = mesh_->elements[transformation->index];
    for (uint32 binding = 0; binding < element->bindings_count; ++binding) {
      interpolation_->bases_[element->bindings[binding]->target_index]->Interpolate(level,
          frame->duration, transformation->rotation + element->bindings[binding]->angle);
    }
  }
}

void ModelBase::Animate_Loop(uint32 const& _animation) {
  typedef Engine::Graphics::Mesh::Element Element;
  typedef Engine::Graphics::Mesh::Animation Animation;
  typedef Engine::Graphics::Mesh::Animation::Frame Frame;
  typedef Engine::Graphics::Mesh::Animation::Frame::Transformation Transformation;

  Motion * motion = motion_;
  (*motion) = Motion(_animation);

  Animation * animation = mesh_->animations[motion->animation];
  Frame * frame = animation->frames[motion->frame];

  for (uint32 current = 0; current < frame->transformations_count; ++current) {
    Transformation * transformation = frame->transformations[current];
    interpolation_->bases_[transformation->index]->Interpolate(0, frame->duration,
                                                               transformation->rotation);

    Element * element = mesh_->elements[transformation->index];
    for (uint32 binding = 0; binding < element->bindings_count; ++binding) {
      interpolation_->bases_[element->bindings[binding]->target_index]->Interpolate(0, frame->duration,
        transformation->rotation + element->bindings[binding]->angle);
    }
  }
}

void ModelBase::Update(real32 const& _elapsed_time) {
  typedef Engine::Graphics::Mesh::Element Element;
  typedef Engine::Graphics::Mesh::Animation Animation;
  typedef Engine::Graphics::Mesh::Animation::Frame Frame;
  typedef Engine::Graphics::Mesh::Animation::Frame::Transformation Transformation;

  {
    Animation * animation = mesh_->animations[motion_->animation];
    Frame * frame = animation->frames[motion_->frame];

    motion_->time += _elapsed_time;

    if (frame->duration < motion_->time) {
      motion_->time -= frame->duration;
      (motion_->frame) = ((motion_->frame) + 1) == animation->frames_count ? 0 : (motion_->frame) + 1;

      Update_Interpolation(motion_, 0, false);
    }
    else
      Update_Interpolation_CurrentTime(motion_);
  }

  Motion * previous_motion = motion_;
  Motion * current_motion = previous_motion->next;

  uint32 level = 1;
  while (current_motion != nullptr) {
    Animation * animation = mesh_->animations[current_motion->animation];
    Frame * frame = animation->frames[current_motion->frame];

    current_motion->time += _elapsed_time;

    if (frame->duration < current_motion->time) {
      current_motion->time -= frame->duration;
      ++(current_motion->frame);
      frame = animation->frames[current_motion->frame];

      if (animation->frames_count == current_motion->frame) {
        if (current_motion->next == nullptr) {
          frame = animation->frames[(current_motion->frame) - 1];

          level = 0;
          Motion * forced_motion = motion_;
          while (forced_motion->next != nullptr) {
            Update_Interpolation(forced_motion, level, true);

            ++level;
            forced_motion = forced_motion->next;
          }

          /*for (uint32 current = 0; current < frame->transformations_count; ++current) {
            Transformation * transformation = frame->transformations[current];
            if (interpolation_->bases_[transformation->index]->level <= level) {
              interpolation_->bases_[transformation->index]->end.time = 0.f;
              //Interpolate(level, frame->duration, transformation->rotation);

              Element * element = mesh_->elements[transformation->index];
              for (uint32 binding = 0; binding < element->bindings_count; ++binding) {
                interpolation_->bases_[element->bindings[binding]->target_index]->end.time = 0.f;
                  //Interpolate(level,
                  //frame->duration, transformation->rotation + element->bindings[binding]->angle);
              }
            }*/
        } else {
          ++level;
        }

        previous_motion->next = current_motion->next;
        delete current_motion;
        current_motion = previous_motion->next;
      } else {
        Update_Interpolation(current_motion, level, false);

        ++level;
        previous_motion = current_motion;
        current_motion = current_motion->next;
      }
    } else {
      Update_Interpolation_CurrentTime(current_motion);

      ++level;
      previous_motion = current_motion;
      current_motion = current_motion->next;
    }
  }

  for (uint32 element = 0; element < mesh_->elements_count; ++element) {
    Interpolation::Interpolator * base = interpolation_->bases_[element];
    if (base->end.time != 0.f) {
      real32 dt = (base->current.time - base->start.time) / (base->end.time - base->start.time);
      base->current.rotation = base->start.rotation + (base->end.rotation - base->start.rotation) * dt;
    }
  }

  Update_ElementCenters(0);
}

void ModelBase::Update_Interpolation(Motion * _motion, uint32 const& _level, bool const& _force) {
  typedef Engine::Graphics::Mesh::Element Element;
  typedef Engine::Graphics::Mesh::Animation Animation;
  typedef Engine::Graphics::Mesh::Animation::Frame Frame;
  typedef Engine::Graphics::Mesh::Animation::Frame::Transformation Transformation;

  Animation * animation = mesh_->animations[_motion->animation];
  Frame * frame = animation->frames[_motion->frame];

  for (uint32 current = 0; current < frame->transformations_count; ++current) {
    Transformation * transformation = frame->transformations[current];
    if (_force || interpolation_->bases_[transformation->index]->level <= _level) {
      interpolation_->bases_[transformation->index]->Interpolate(_level, _motion->time, frame->duration,
        transformation->rotation);

      Element * element = mesh_->elements[transformation->index];
      for (uint32 binding = 0; binding < element->bindings_count; ++binding) {
        interpolation_->bases_[element->bindings[binding]->target_index]->Interpolate(_level,
          _motion->time, frame->duration, transformation->rotation + element->bindings[binding]->angle);
      }
    }
  }
}

void ModelBase::Update_Interpolation_CurrentTime(Motion * _motion) {
  typedef Engine::Graphics::Mesh::Element Element;
  typedef Engine::Graphics::Mesh::Animation Animation;
  typedef Engine::Graphics::Mesh::Animation::Frame Frame;
  typedef Engine::Graphics::Mesh::Animation::Frame::Transformation Transformation;

  Animation * animation = mesh_->animations[_motion->animation];
  Frame * frame = animation->frames[_motion->frame];

  for (uint32 current = 0; current < frame->transformations_count; ++current) {
    Transformation * transformation = frame->transformations[current];
    interpolation_->bases_[transformation->index]->current.time = _motion->time;

    Element * element = mesh_->elements[transformation->index];
    for (uint32 binding = 0; binding < element->bindings_count; ++binding) {
      interpolation_->bases_[element->bindings[binding]->target_index]->current.time = _motion->time;
    }
  }
}

void ModelBase::Update_ElementCenters(uint32 const& _element_index) {
  typedef Engine::Graphics::Mesh::Element Element;
  Element * element = mesh_->elements[_element_index];

  for (uint32 current = 0; current < element->joints_count; ++current)
    Update_ElementJoint(_element_index, element->joints[current]);

  for (uint32 current = 0; current < element->bindings_count; ++current)
    Update_ElementJoint(_element_index, element->bindings[current]);
}

void ModelBase::Update_ElementJoint(uint32 const& _element_index, Mesh::Element::Joint * _joint) {
  uint32 target_index = _joint->target_index;

  Vector2 owner = _joint->owner_location;
  owner.Rotate_Degree(interpolation_->bases_[_element_index]->current.rotation);

  Vector2 target = _joint->target_location;
  target.Rotate_Degree(interpolation_->bases_[target_index]->current.rotation);

  element_centers_[target_index] = owner - target + element_centers_[_element_index];

  Update_ElementCenters(target_index);
}
}
}
