#ifndef ENGINE_NETWORK_HANDLER_HPP_
#define ENGINE_NETWORK_HANDLER_HPP_

#include "Engine/Platform.h"

namespace Engine { namespace Network {

template < typename ... T >
class IHandler : public NonCopyable {
public:
  virtual void Handle( T ... ) = 0;
};

template < typename ... T >
using Handler = shared_ptr < IHandler < T ... > >;

template < typename ... T >
using ThreadSafeHandler = atomic < Handler < T ... > >;

} }

#endif