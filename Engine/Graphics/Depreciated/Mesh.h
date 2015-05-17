#ifndef ENGINE_GRAPHICS_MESH_H_
#define ENGINE_GRAPHICS_MESH_H_

#include <string>
#include <fstream>

#include "Engine/Types.h"

namespace Engine {
namespace Graphics {
struct Mesh {
  public:
    struct Element : public NonCopyable {
      public:
        struct Joint : public NonCopyable {
          public:
            Vector2 owner_location, target_location;
            uint32 target_index = 0;

            inline Joint(Vector2 const& _owner_location, uint32 const& _target_index,
                         Vector2 const& _target_location)
                : owner_location(std::move(_owner_location)),
                  target_location(std::move(_target_location)),
                  target_index(_target_index) { }
            inline virtual ~Joint(void) = default;
          };

        struct Binding : public Joint {
          real32 angle = 0.f;

          inline Binding(Vector2 const& _owner_location, uint32 const& _target_index,
                         Vector2 const& _target_location, real32 const& _angle)
              : Joint(_owner_location, _target_index, _target_location), angle(_angle) { }
          inline virtual ~Binding(void) = default;
        };

      public:
        uint32 index, depth = 0;

        uint32 joints_count = 0;
        Joint ** joints = nullptr;

        uint32 bindings_count = 0;
        Binding ** bindings = nullptr;

        inline Element(uint32 const& _index, uint32 const& _depth, uint32 const& _joints_count,
                       Joint ** _joints, uint32 const& _bindings_count, Binding ** _bindings)
            : index(_index),
              depth(_depth),
              joints_count(_joints_count),
              joints(_joints),
              bindings_count(_bindings_count),
              bindings(_bindings) { }
        inline virtual ~Element(void) {
          for (uint32 current = 0; current < joints_count; ++current)
            delete joints[current];
          delete[] joints;
          joints = nullptr;
      }
    };

    struct Animation : public NonCopyable {
      public:
        struct Frame : public NonCopyable {
          public:
            struct Transformation : public NonCopyable {
              public:
                uint32 index = 0;
                real32 rotation = 0.f;

                inline Transformation(uint32 const& _index, real32 const& _rotation)
                    : index(_index),
                      rotation(_rotation) { }
                inline virtual ~Transformation(void) = default;
              };

          public:
            real32 duration = 0.f;

            uint32 transformations_count = 0;
            Transformation ** transformations = nullptr;

            inline Frame(real32 const& _duration, uint32 const& _transformations_count,
                         Transformation ** _transformations)
                : duration(_duration),
                  transformations_count(_transformations_count),
                  transformations(_transformations) { }
            inline virtual ~Frame(void) {
              for (uint32 current = 0; current < transformations_count; ++current)
                delete transformations[current];
              delete[] transformations;
              transformations = nullptr;
            }
        };

      public:
        uint32 frames_count = 0;
        Frame ** frames = nullptr;

        inline Animation(uint32 const& _frames_count, Frame ** _frames)
            : frames_count(_frames_count),
              frames(_frames) { }
        inline virtual ~Animation(void) {
          for (uint32 current = 0; current < frames_count; ++current)
            delete frames[current];
          delete[] frames;
          frames = nullptr;
        }
    };

  public:
    uint32 * depth_indexes = nullptr;

    uint32 elements_count = 0;
    Element ** elements = nullptr;

    uint32 animations_count = 0;
    Animation ** animations = nullptr;

    Mesh(std::string const& _mesh_path);
    virtual ~Mesh(void);

  private:
    void ReadPlaceholder(std::ifstream & _file);
};
}
}

#endif
