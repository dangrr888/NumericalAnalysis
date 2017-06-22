#ifndef GUARD_INTEGRATION_H_
#define GUARD_INTEGRATION_H_

#include <functional>
#include <cstddef>

#include "integrator.h"

namespace integration
{

  template<typename T>
  class Algorithm;

  template<typename T>
  T integrate( const T& start
             , const T& finish
             , std::size_t N
             , const integration::Algorithm<T>& a
             , integration::Integrator<T> integrator
             )
  {
    T ret = T();
    const T step_size = (finish - start) / static_cast<T>(N);
    T in = start;
    for (std::size_t i = 0; i < N; ++i)
    {
      ret += integrator(in, step_size, a);
      in += step_size;
    }

    return ret;
  }

} // ! namespace integration

#endif // ! GUARD_INTEGRATION_H_
