#ifndef ENGINE_GRAPHICS_MODELBASE_H_
#define ENGINE_GRAPHICS_MODELBASE_H_

#include "Engine/Types.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/Appearance.h"

namespace Engine {
namespace Graphics {
class ModelBase {
  protected:
    struct Interpolation {
      public:
        struct Interpolator {
          public:
            struct Base {
              public:
                real32 time = 0.f, rotation = 0.f;

                inline Base(real32 const& _time, real32 const& _rotation)
                  : time(_time),
                    rotation(_rotation) { }
                inline Base(void) = default;
                inline Base(Base && _other) = delete;
                inline Base(Base const& _other) = delete;
                inline Base & operator=(Base && _other) = delete;
                inline Base & operator=(Base const& _other) = delete;
                inline virtual ~Base(void) = default;
            };
          public:
            uint32 level = 0;
            Base start, current, end;

            inline Interpolator(void) = default;
            inline Interpolator(Interpolator && _other) = delete;
            inline Interpolator(Interpolator const& _other) = delete;
            inline Interpolator & operator=(Interpolator && _other) = delete;
            inline Interpolator & operator=(Interpolator const& _other) = delete;
            inline virtual ~Interpolator(void) = default;

            inline void Interpolate(uint32 const& _level, real32 const& _end_time,
                                    real32 const& _end_rotation) {
              level = _level;
              start.time = 0.f;
              start.rotation = current.rotation;
              current.time = 0.f;
              end.time = _end_time;
              end.rotation = _end_rotation;
            }

            inline void Interpolate(uint32 const& _level, real32 const& _start_time, 
                                    real32 const& _end_time, real32 const& _end_rotation) {
              level = _level;
              start.time = _start_time;
              start.rotation = current.rotation;
              current.time = _start_time;
              end.time = _end_time;
              end.rotation = _end_rotation;
            }
        };

      public:
        uint32 bases_count_ = 0;
        Interpolator ** bases_ = nullptr;

        inline Interpolation(uint32 const& _bases_count)
            : bases_count_(_bases_count),
              bases_(new Interpolator*[bases_count_]) {
          for (uint32 current = 0; current < bases_count_; ++current)
            bases_[current] = new Interpolator();
        }
        inline Interpolation(void) = delete;
        inline Interpolation(Interpolation && _other) = delete;
        inline Interpolation(Interpolation const& _other) = delete;
        inline Interpolation & operator=(Interpolation && _other) = delete;
        inline Interpolation & operator=(Interpolation const& _other) = delete;
        inline virtual ~Interpolation(void) {
          for (uint32 current = 0; current < bases_count_; ++current)
            delete bases_[current];
          delete[] bases_;
          bases_ = nullptr;
        }
    };

    struct Motion {
      public:
        Motion * next = nullptr;

        real32 time = 0.f;
        uint32 animation = 0, frame = 0;

        inline explicit Motion(uint32 const& _animation)
            : animation(_animation) { }
        inline Motion(void) = default;
        inline Motion(Motion && _other) = delete;
        inline Motion(Motion const& _other) = delete;
        inline Motion & operator=(Motion && _other) {
          time = _other.time;
          animation = _other.animation;
          frame = _other.frame;

          return *this;
        }
        inline Motion & operator=(Motion const& _other) {
          time = _other.time;
          animation = _other.animation;
          frame = _other.frame;

          return *this;
        }
        inline virtual ~Motion(void) = default;
    };

  public:
    inline ModelBase(Mesh * _mesh, Appearance * _appearance, uint32 const& _animation)
        : mesh_(_mesh),
          appearance_(_appearance),
          motion_(new Motion(_animation)),
          element_centers_(new Vector2[_mesh->elements_count]),
          interpolation_(new Interpolation(_mesh->elements_count)){
      Animate_Loop(_animation);
    }
    inline ModelBase(void) = delete;
    inline ModelBase(ModelBase && _other) = delete;
    inline ModelBase(ModelBase const& _other) = delete;
    inline ModelBase & operator=(ModelBase && _other) = delete;
    inline ModelBase & operator=(ModelBase const& _other) = delete;
    inline virtual ~ModelBase(void) {
      delete motion_;
      motion_ = nullptr;

      delete[] element_centers_;
      element_centers_ = nullptr;

      delete interpolation_;
      interpolation_ = nullptr;
    }

    virtual void Animate(uint32 const& _animation);
    virtual void Animate_Loop(uint32 const& _animation);
    virtual void Update(real32 const& _elapsed_time);

  protected:
    Mesh * mesh_ = nullptr;
    Appearance * appearance_ = nullptr;

    Motion * motion_ = nullptr;

    Vector2 * element_centers_ = nullptr;
    Interpolation * interpolation_ = nullptr;
    
  private:
    void Update_ElementCenters(uint32 const& _element_index);
    void Update_ElementJoint(uint32 const& _element_index, Mesh::Element::Joint * _joint);
    void Update_Interpolation(Motion * _motion, uint32 const& _level, bool const& _force);
    void Update_Interpolation_CurrentTime(Motion * _motion);
    // virtual void SetFrame(uint32 const& _frame);
};
}
}

#endif