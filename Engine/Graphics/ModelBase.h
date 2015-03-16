#ifndef ENGINE_GRAPHICS_MODELBASE_H_
#define ENGINE_GRAPHICS_MODELBASE_H_

#include "Engine/Types.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/Appearance.h"

namespace Engine {
namespace Graphics {
class ModelBase {
  public:
    struct InterpolationBase {
    public:
      real32 time = 0.f;

      uint32 rotations_count = 0;
      real32 * rotations = nullptr;

      inline InterpolationBase(real32 const& _time, uint32 const& _rotations_count)
          : time(_time),
            rotations_count(_rotations_count) {
        rotations = new real32[rotations_count];
        memset(rotations, (uint32)(0.f), rotations_count * sizeof(real32));
      }
      inline InterpolationBase(void) = delete;
      inline InterpolationBase(InterpolationBase && _other) = delete;
      inline InterpolationBase(InterpolationBase const& _other) = delete;
      inline InterpolationBase & operator=(InterpolationBase && _other) = delete;
      inline InterpolationBase & operator=(InterpolationBase const& _other) = delete;
      inline virtual ~InterpolationBase(void) { delete[] rotations; }
    };

  public:
    inline ModelBase(Mesh * _mesh, Appearance * _appearance, uint32 const& _animation)
        : mesh_(_mesh),
          appearance_(_appearance),
          animation_(_animation) {
      element_centers = new Vector2[_mesh->elements_count];

      interpolation_start = new InterpolationBase(0.f, _mesh->elements_count);
      interpolation_current = new InterpolationBase(0.f, _mesh->elements_count);
      interpolation_end = new InterpolationBase(0.f, _mesh->elements_count);

      SetFrame(0);
    }
    inline ModelBase(void) = delete;
    inline ModelBase(ModelBase && _other) = delete;
    inline ModelBase(ModelBase const& _other) = delete;
    inline ModelBase & operator=(ModelBase && _other) = delete;
    inline ModelBase & operator=(ModelBase const& _other) = delete;
    inline virtual ~ModelBase(void) {
      delete[] element_centers;
      element_centers = nullptr;

      delete interpolation_start;
      interpolation_start = nullptr;
      delete interpolation_current;
      interpolation_current = nullptr;
      delete interpolation_end;
      interpolation_end = nullptr;
    }

    virtual void Animate(uint32 const& _animation);
    virtual void Update(real32 const& _elapsed_time);

  protected:
    Mesh * mesh_ = nullptr;
    Appearance * appearance_ = nullptr;

    uint32 frame_ = 0, animation_ = 0;

    Vector2 * element_centers = nullptr;
    InterpolationBase * interpolation_current = nullptr;
    
  private:
    InterpolationBase * interpolation_start = nullptr;
    InterpolationBase * interpolation_end = nullptr;

    virtual void Update_ElementCenters(uint32 const& _element_index);
    virtual void Update_ElementJoint(uint32 const& _element_index, Mesh::Element::Joint * _joint);
    virtual void SetFrame(uint32 const& _frame);
};
}
}

#endif