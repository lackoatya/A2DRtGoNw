#include "Engine/Physics/Collision.h"

Engine::Physics::Collision::Type Engine::Physics::Collision::Resolve(DescriptorInterface const& _current, DynamicDescriptor const& _other) {
  //   ^
  //   |      6 \ |    1    | / 5
  //   |      ___\|_________|/___
  //   |          |p1       |
  //   |       4  |    0    |  3
  //   |      ____|_______p2|____
  //   |         /|         |\      |
  //   |      7 / |    2    | \ 8
  //   |
  // (0,0)---------------------->

  Vector2 my_p1(_current.center.x - _current.width, _current.center.y + _current.height);
  Vector2 my_p2(_current.center.x + _current.width, _current.center.y - _current.height);
  Vector2 ur_p1(_other.center.x - _other.width, _other.center.y + _other.height);
  Vector2 ur_p2(_other.center.x + _other.width, _other.center.y - _other.height);

  // case 0:
  if (my_p1.x < _other.center.x && _other.center.x < my_p2.x &&
      my_p2.y < _other.center.y && _other.center.y < my_p1.y) return Type::INSIDE;

  // case 1:
  if (my_p1.y < _other.center.y && my_p1.x <= _other.center.x && _other.center.x <= my_p2.x) {
    if (ur_p2.y <= my_p1.y) return Type::TOP;
    else return  Type::NONE;
  }

  // case 2:
  if (_other.center.y < my_p2.y && my_p1.x <= _other.center.x && _other.center.x <= my_p2.x) {
    if (my_p2.y <= ur_p1.y) return Type::BOTTOM;
    else return  Type::NONE;
  }

  // case 3:
  if (my_p2.x < _other.center.x && my_p2.y <= _other.center.y && _other.center.y <= my_p1.y) {
    if (ur_p1.x <= my_p2.x) return Type::RIGHT;
    else return  Type::NONE;
  }

  // case 4:
  if (_other.center.x < my_p1.x && my_p2.y <= _other.center.y && _other.center.y <= my_p1.y) {
    if (my_p1.x <= ur_p2.x) return Type::LEFT;
    else return  Type::NONE;
  }

  // case 5:
  if (my_p2.x < _other.center.x && my_p1.y < _other.center.y) {
    if (ur_p1.x < my_p2.x && ur_p2.y < my_p1.y) {
      float ur_m = _other.velocity.x / _other.velocity.y;
      float my_m = (_other.center.x - my_p2.x) / (_other.center.y - my_p1.y);

      if (ur_m < my_m) return Type::RIGHT;
      else return Type::TOP;
    }
    return Type::NONE;
  }

  // case 6:
  if (_other.center.x < my_p1.x && my_p1.y < _other.center.y) {
    if (my_p1.x < ur_p2.x && my_p1.y < ur_p2.y) {
      float ur_m = _other.velocity.x / _other.velocity.y;
      float my_m = (_other.center.x - my_p1.x) / (_other.center.y - my_p1.y);

      if (ur_m < my_m) return Type::TOP;
      else return Type::LEFT;
    }
    return Type::NONE;
  }

  // case 7:
  if (_other.center.x < my_p1.x && _other.center.y < my_p2.y) {
    if (my_p1.x < ur_p2.x && my_p2.y < ur_p1.y) {
      float ur_m = _other.velocity.x / _other.velocity.y;
      float my_m = (_other.center.x - my_p1.x) / (_other.center.y - my_p2.y);

      if (ur_m < my_m) return Type::LEFT;
      else return Type::BOTTOM;
    }
    return Type::NONE;
  }

  // case 8:
  if (my_p2.x < _other.center.x && _other.center.y < my_p2.y) {
    if (ur_p1.x < my_p2.x && my_p2.y < ur_p1.y) {
      float ur_m = _other.velocity.x / _other.velocity.y;
      float my_m = (_other.center.x - my_p2.x) / (_other.center.y - my_p2.y);

      if (ur_m < my_m) return Type::BOTTOM;
      else return Type::RIGHT;
    }
    return Type::NONE;
  }

  return Type::NONE;
}

Engine::Physics::Collision::Type Engine::Physics::Collision::Attachment(DescriptorInterface const& _current, DescriptorInterface const& _other) {
  Vector2 my_p1(_current.center.x - _current.width, _current.center.y + _current.height);
  Vector2 my_p2(_current.center.x + _current.width, _current.center.y - _current.height);

  // case 1:
  if (my_p2.x + _other.width == _other.center.x) {
    if (my_p2.y - _other.height < _other.center.y && _other.center.y < my_p1.y + _other.height) return Type::RIGHT;
    return Type::NONE;
  }

  // case 2:
  if (my_p1.y + _other.height == _other.center.y) {
    if (my_p1.x - _other.width < _other.center.x && _other.center.x < my_p2.x + _other.width) return Type::TOP;
    return Type::NONE;
  }

  // case 3:
  if (my_p1.x - _other.width == _other.center.x) {
    if (my_p2.y - _other.height < _other.center.y && _other.center.y < my_p1.y + _other.height) return Type::LEFT;
    return Type::NONE;
  }

  return Type::NONE;
}
