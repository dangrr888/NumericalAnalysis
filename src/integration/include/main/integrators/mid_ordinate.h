#ifndef GUARD_MID_ORDINATE_H_
#define GUARD_MID_ORDINATE_H_

#include "algorithm.h"

namespace integration
{

  namespace integrators
  {

    template<typename T>
    T mid_ordinate( const T& in
                  , const T& step_size
                  , const integration::Algorithm<T>& a
                  )
    {
      return a.execute(in + (step_size/2.0)) * step_size;
    }

  } // ! namespace integrators

} // ! namespace integration

#endif // ! GUARD_MID_ORDINATE_H_
