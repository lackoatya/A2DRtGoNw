#ifndef ENGINE_PHYSICS_COLLISION_H_
#define ENGINE_PHYSICS_COLLISION_H_

#include "Engine/Physics/DescriptorInterfaces.h"

namespace Engine {
namespace Physics {
namespace Collision {
enum class Type {
  NONE = 0,
  INSIDE,
  TOP,
  BOTTOM,
  RIGHT,
  LEFT,

  Count
};


//template< class T1, class T2 > Collision_Type::Type Resolve(const T1 &_current, const T2 &_other);
//template< > Collision_Type::Type Resolve< Descriptor, Descriptor >(const Descriptor &_current, const Descriptor &_other);
Type Resolve(DescriptorInterface const& _current, DynamicDescriptor const& _other);
/*Collision_Type::Type Resolve(const Wall_Descriptor &_wall, const Hero_Descriptor &_hero)
{
return Resolve< Descriptor, Descriptor >(_wall, _hero);
}*/
//template< > Collision_Type::Type Resolve< Hero_Descriptor, Wall_Descriptor>(const Hero_Descriptor &_)

//template< class T1, class T2 > Collision_Type::Type Attachment(const T1 &_current, const T2 &_other);
Type Attachment(DescriptorInterface const& _current, DescriptorInterface const& _other);
}
}
}
#endif