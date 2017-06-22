#ifndef GUARD_ALGORITHM_H_
#define GUARD_ALGORITHM_H_

namespace integration
{

  template<typename T>
  struct Algorithm
  {
    Algorithm() = default;
    ~Algorithm() = default;
    Algorithm(const Algorithm&) = default;
    Algorithm(Algorithm&&) = delete;
    Algorithm& operator=(const Algorithm&) = default;
    Algorithm& operator=(Algorithm&&) = delete;

    virtual T execute(const T& in) const = 0;
    virtual const char* name() const = 0;

  }; // ! class Algorithm

} // ! namespace integration

#endif // ! GUARD_ALGORITHM_H_
