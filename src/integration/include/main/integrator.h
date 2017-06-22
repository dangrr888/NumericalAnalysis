#ifndef GUARD_INTEGRATOR_H_
#define GUARD_INTEGRATOR_H_

#include <functional>

namespace integration
{
  template<typename T>
  class Algorithm;

  template<typename T>
  using Integrator = std::function<T ( const T&
                                     , const T&
                                     , const integration::Algorithm<T>&
                                     )
                                  >;
} // ! namespace integration

#endif // ! GUARD_INTEGRATOR_H_
