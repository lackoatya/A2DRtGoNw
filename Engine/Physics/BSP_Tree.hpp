#ifndef ENGINE_PHYSICS_BSP_TREE_HPP_
#define ENGINE_PHYSICS_BSP_TREE_HPP_

#include <list>

// #include "BOOST/shared_ptr.hpp"
// #include "BOOST/lexical_cast.hpp"

#include "Engine/Types.h"
#include "Engine/Physics/SeparatableLinkedList.hpp"

namespace Engine {
namespace Physics {
template< class T >
class BSP_Tree : public NonCopyable {
  private:
    enum class Partition {
      VERTICAL = 0,
      HORIZONTAL,

      Count
    };

    template< class T >
    class BSP_Separator : public NonCopyable {
    public:
      inline BSP_Separator(Partition const& _partition, real32 const& _value)
          : partition_(_partition),
            value(_value) { }
      BSP_Separator(SLL<T> * _sll, Vector2 const& _p1, Vector2 const& _p2) {
        // Create the two possible geometrically optimal separation
        real32 vertical_optimum = (_p1.x + _p2.x) / 2.f;
        real32 best_vertical_cut = _p1.x;
        real32 best_vertical_distance = std::numeric_limits<real32>::infinity();
        real32 horizontal_optimum = (_p1.y + _p2.y) / 2.f;
        real32 best_horizontal_cut = _p2.y;
        real32 best_horizontal_distance = std::numeric_limits<real32>::infinity();

        // Calculate the most optimal separation along the edges
        SLL_Node<T> * current = _sll->first;
        while (current) {
          SLL_Node<T> * member = current->member;

          if (_p1.x < member->center.x - member->width && member->center.x - member->width < _p2.x &&
            abs(vertical_optimum - (member->center.x - member->width)) < best_vertical_distance){
            best_vertical_cut = member->center.x - member->width;
            best_vertical_distance = abs(vertical_optimum - best_vertical_cut);
          }
          if (_p1.x < member->center.x + member->width && member->center.x + member->width < _p2.x &&
            abs(vertical_optimum - (member->center.x + member->width)) < best_vertical_distance) {
            best_vertical_cut = member->center.x + member->width;
            best_vertical_distance = abs(vertical_optimum - best_vertical_cut);
          }
          if (_p2.y < member->center.y - member->height && member->center.y - member->height < _p1.y &&
            abs(horizontal_optimum - (member->center.y - member->height)) < best_horizontal_distance) {
            best_horizontal_cut = member->center.y - member->height;
            best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut);
          }
          if (_p2.y < member->center.y + member->height && member->center.y + member->height < _p1.y &&
            abs(horizontal_optimum - (member->center.y + member->height)) < best_horizontal_distance) {
            best_horizontal_cut = member->center.y + member->height;
            best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut);
          }

          current = current->next;
        }

        assert(!(best_horizontal_distance == std::numeric_limits<real32>::infinity() ||
          best_vertical_distance == std::numeric_limits<real32>::infinity()));

        // Select best separation
        if ((best_vertical_cut == std::numeric_limits<real32>::infinity()) ||
          best_horizontal_distance < best_vertical_distance) {
          type = Partition::HORIZONTAL;
          value = best_horizontal_cut;
        }
        else {
          type = Partition::VERTICAL;
          value = best_vertical_cut;
        }
      }
      inline virtual ~BSP_Separator(void) = default;

      inline bool operator<(T _object) const {
        return type == Partition::HORIZONTAL ?
          value < _object->center.y - _object->height || value < _object->center.y + _object->height
          :
          value < _object->center.x - _object->width || value < _object->center.x + _object->width;
      }
      inline bool operator>(T _object) const {
        return type == Partition::HORIZONTAL ?
          _object->center.y - _object->height < value || _object->center.y + _object->height < value
          :
          _object->center.x - _object->width < value || _object->center.x + _object->width < value;
      }

      inline bool operator<(const Vector2 _point) const {
        return type == Partition::HORIZONTAL ? value < _point.y : value < _point.x;
      }
      inline bool operator>(const Vector2 _point) const {
        return type == Partition::HORIZONTAL ? _point.y < value : _point.x < value
      }

      inline real32 value(void) const { return value_; }
      inline Partition partition(void) const { return partition_; }

      private:
        real32 value_;
        Partition partition_;
    };

    template< class T >
    class BSP_Node : public NonCopyable {
      public:
        inline explicit BSP_Node< T >(T _object) : object(_object) { }
        BSP_Node< T >(SLL< T > * _sll, Vector2 const& _p1, Vector2 const& _p2) {
          if (_sll->count == 1) {
            BSP_Node *current = this;
            current->object = _sll->first->member;

            if (_p1.x < current->object->center.x - current->object->width) {
              T object_copy = current->object;
              current->object = nullptr;
              current->separator = new BSP_Separator< T >(Partition::VERTICAL,
                                                          object_copy->center.x - object_copy->width);
              current->right = new BSP_Node(object_copy);
              current = current->right;
            }
            if (current->object->center.x + current->object->width < _p2.x) {
              T object_copy = current->object;
              current->object = nullptr;
              current->separator = new BSP_Separator< T >(Partition::VERTICAL,
                                                          object_copy->center.x + object_copy->width);
              current->left = new BSP_Node(object_copy);
              current = current->left;
            }
            if (_p2.y < current->object->center.y - current->object->height) {
              T object_copy = current->object;
              current->object = nullptr;
              current->separator = new BSP_Separator< T >(Partition::HORIZONTAL,
                                                          object_copy->center.y - object_copy->height);
              current->right = new BSP_Node(object_copy);
              current = current->right;
            }
            if (current->object->center.y + current->object->height < _p1.y) {
              T object_copy = current->object;
              current->object = nullptr;
              current->separator = new BSP_Separator< T >(Partition::HORIZONTAL,
                                                          object_copy->center.y + object_copy->height);
              current->left = new BSP_Node(object_copy);
              current = current->left;
            }
          } else {
            // Create optimal separation
            separator = new BSP_Separator< T >(_sll, _p1, _p2);

            // Separate list
            SLL< T > * lesser = _sll->Separate< BSP_Separator< T > >(separator);

            // Recursive calls
            if (lesser->count != 0) left = new BSP_Node(lesser, separator->type == Partition::HORIZONTAL ? Vector2(_p1.x, separator->value) : _p1, separator->type == Partition::HORIZONTAL ? _p2 : Vector2(separator->value, _p2.y));
            if (_sll->count != 0)	right = new BSP_Node(_sll, separator->type == Partition::HORIZONTAL ? _p1 : Vector2(separator->value, _p1.y), separator->type == Partition::HORIZONTAL ? Vector2(_p2.x, separator->value) : _p2);
          }
        }
        inline virtual ~BSP_Node(void) {
          delete left;
          left = nullptr;
          delete right;
          right = nullptr;
          delete separator;
          separator = nullptr;

          object = nullptr;
        }

      private:
        BSP_Node< T > * left = nullptr, * right = nullptr;
        BSP_Separator< T > * separator = nullptr;
        T object;
    };

  public:
    explicit BSP_Tree(SLL<T> * _objects) {
      assert(_objects);
      assert(_objects->first);

      // Determine bounding box of the objects;
      SLL_Node<T> * current = _objects->first->member;
      Vector2 p1(member->center.x -current->width,current->center.y +current->height);
      Vector2 p2(member->center.x +current->width,current->center.y -current->height);

      current = _objects->first;
      while (current) {
        SLL_Node<T> * member = current->member;
        if (member->center.x - member->width < p1.x) p1.x = member->center.x - member->width;
        if (p1.y < member->center.y + member->height) p1.y = member->center.y + member->height;
        if (p2.x < member->center.x + member->width) p2.x = member->center.x + member->width;
        if (member->center.y - member->height < p2.y) p2.y = member->center.y - member->height;

        current = current->next;
      }

      // Create the BSP Tree
      root = new BSP_Node<T (_objects, p1, p2);
    }
    inline virtual ~BSP_Tree(void) { delete root; root = nullptr; }

    T * Collision(Vector2 const& _point) {
      BSP_Node<T> * current = root;
      while (current) {
        if (current->separator) {
          if (*(current->separator) < _point) current = current->right;
          else current = current->left;
        } else {
          assert(current->object);
          return current->object;
        }
      }
      return nullptr;
    }

  private:
    BSP_Node< T > * root = nullptr;
};
}
}
#endif
