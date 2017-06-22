#ifndef GUARD_FIRST_ORDINATE_H_
#define GUARD_FIRST_ORDINATE_H_

#include "algorithm.h"

namespace integration
{

  namespace integrators
  {

    template<typename T>
    T first_ordinate( const T& in
                    , const T& step_size
                    , const integration::Algorithm<T>& a
                    )
    {
      return a.execute(in) * step_size;
    }

  } // ! namespace integrators

} // ! namespace integration

#endif // ! GUARD_FIRST_ORDINATE_H_
