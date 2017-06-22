#ifndef GUARD_SIMPSON_H_
#define GUARD_SIMPSON_H_

#include "algorithm.h"
#include "integrators/mid_ordinate.h"
#include "integrators/trapezium.h"

namespace integration
{

  namespace integrators
  {

    template<typename T>
    T simpson( const T& in
             , const T& step_size
             , const integration::Algorithm<T>& a
             )
    {
      return 2.0/3.0 * integration::integrators::mid_ordinate<T>(in, step_size, a) +
             1.0/3.0 * integration::integrators::trapezium<T>(in, step_size, a);
    }

  } // ! namespace integrators

} // ! namespace integration

#endif // ! GUARD_SIMPSON_H_
