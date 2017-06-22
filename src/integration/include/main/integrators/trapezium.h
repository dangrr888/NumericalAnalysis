#ifndef GUARD_TRAPEZIUM_H_
#define GUARD_TRAPEZIUM_H_

#include "algorithm.h"

namespace integration
{

  namespace integrators
  {

    template<typename T>
    T trapezium( const T& in
                 , const T& step_size
                 , const Algorithm<T>& a
      )
    {
      return 0.5 * (a.execute(in) + a.execute(in + step_size)) * step_size;
    }

  } // ! namespace integrators

} // ! namespace integration

#endif // ! GUARD_TRAPEZIUM_H_
