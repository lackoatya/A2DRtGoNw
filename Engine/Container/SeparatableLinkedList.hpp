#ifndef ENGINE_CONTAINER_SEPARATABLE_LINKED_LIST_HPP_
#define ENGINE_CONTAINER_SEPARATABLE_LINKED_LIST_HPP_

#include <list>

#include "BOOST/foreach.hpp"

#include "Engine/Platform.h"

namespace Engine {
namespace Container {
template< class T >
struct SLL : public NonCopyable {
  private:
    template< class T >
    struct SLL_Node : public NonCopyable {
      public:
        SLL_Node * prev = nullptr, *next = nullptr;
        T member;

        SLL_Node(SLL_Node * _prev, T const& _member) : prev(_prev), member(_member) { }
        SLL_Node(T const& _member) : member(_member) { }
        SLL_Node(T const& _member, SLL_Node * _next) : member(_member), next(_next) { }
        SLL_Node(SLL_Node * _prev, T const& _member, SLL_Node * _next)
            : prev(_prev),
              member(_member),
              next(_next) { }
        inline virtual ~SLL_Node(void) { delete next; next = nullptr; }
    };

  public:
    SLL_Node<T> * first =  nullptr, * last = nullptr;

    inline explicit SLL<T>(std::list< T > const& _list) {
      BOOST_FOREACH(T& current, _list) {
        Insert_Last(current);
      }
    }
    inline SLL(void) = default;
    inline virtual ~SLL(void) { delete first; first = nullptr; }

    SLL_Node< T > * Insert_Last(T const& _member) {
      ++count;

      if (first) {
        last->next = new SLL_Node< T >(last, _member);
        last = last->next;
        return last;
      } else {
        first = new SLL_Node< T >(_member);
        last = first;
        return last;
      }
    }

    SLL_Node< T > * Insert_Last(SLL_Node< T > * _node) {
      ++count;

      if (first) {
        last->next = _node;
        _node->prev = last;
      } else {
        first = _node;
        _node->prev = nullptr;
      }

      last = _node;
      _node->next = nullptr;
      return last;
    }

    template< class S >
    SLL< T > * Separate(S * _separator) {
      // Allocate the list of the separated elements
      SLL< T > * lesser = new SLL< T >();

      SLL_Node< T > * current = first, * previous = nullptr;
      while (current) {
        if ((*_separator) > current->member) {
          if ((*_separator) < current->member) {
            // This element is in both lists, so copy to the other
            lesser->Insert_Last(current->member);
            current = current->next;
          } else {
            // We need to separate this element
            if (current->prev) {
              // This is not the first element
              if (current->next) {
                // This is an intermediate element
                current->prev->next = current->next;
                current->next->prev = current->prev;
              } else {
                // This is the last element
                current->prev->next = 0;
                last = current->prev;
              }
            } else {
              // This is the first element
              if (current->next) {
                // This is not the last element
                current->next->prev = 0;
                first = current->next;
              } else {
                // This is the only element in the list
                first = 0;
                last = 0;
              }
            }

            // Remove from this list
            SLL_Node< T > * current_copy = current;
            current = current->next;
            lesser->Insert_Last(current_copy);
            count--;
          }
        } else {
          current = current->next;
        }
      }

      return lesser;
    }

    inline uint32 count(void) const { return count_; }

  private:
    uint32 count_ = 0;
};
}
}
#endif