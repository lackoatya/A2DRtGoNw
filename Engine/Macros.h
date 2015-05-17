#ifndef ENGINE_MACROS_H_
#define ENGINE_MACROS_H_

#define _WIN32_WINNT 0x0501

// TODO Let the bytes go! :(
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Empty_Base_Optimization
// https://www.youtube.com/watch?v=6fZwJFjiA0A

#ifdef DEBUG
  #include "Engine/Utility/ObjectCounter.hpp"
  template < typename Derived >
  class BaseClass : public Engine::Utility::ObjectCounter < Derived > {
  };
#else
  template < typename Derived >
  class BaseClass {
  };
#endif

#endif
