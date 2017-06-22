#include <iostream>
#include <cstdlib>
#include <cmath>
#include <array>
#include <iomanip>
#include <functional>
#include <cstddef>

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
  };

  template<typename T>
  using Integrator = std::function<T ( const T&
                                     , const T&
                                     , const Algorithm<T>&
                                     )
                                  >;

  template<typename T>
  T first_ordinate( const T& in
                  , const T& step_size
                  , const Algorithm<T>& a
                  )
  {
    return a.execute(in) * step_size;
  }

  template<typename T>
  T last_ordinate( const T& in
                 , const T& step_size
                 , const Algorithm<T>& a
                 )
  {
    return a.execute(in + step_size) * step_size;
  }

  template<typename T>
  T mid_ordinate( const T& in
                , const T& step_size
                , const Algorithm<T>& a
                )
  {
    return a.execute(in + (step_size/2.0)) * step_size;
  }

  template<typename T>
  T trapezium( const T& in
             , const T& step_size
             , const Algorithm<T>& a
             )
  {
    return 0.5 * (a.execute(in) + a.execute(in + step_size)) * step_size;
  }

  template<typename T>
  T weighted_mo_trap( const T& in
                    , const T& step_size
                    , const Algorithm<T>& a
                    )
  {
    static const double weight = 1.0/3.0;
    return (1.0 - weight) * mid_ordinate<T>(in, step_size, a) +
           weight * trapezium<T>(in, step_size, a);
  }

  template<typename T>
  T integrate( const T& start
             , const T& finish
             , std::size_t N
             , const Algorithm<T>& a
             , Integrator<T> integrator
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

namespace example
{
  struct x4DoubleAlgorithm final : public integration::Algorithm<double>
  {
    double execute(const double& in) const { return std::pow(in, 4.0); }
    const char* name() const {return "X^4";}
  };

  struct x5DoubleAlgorithm final : public integration::Algorithm<double>
  {
    double execute(const double& in) const { return std::pow(in, 5.0); }
    const char* name() const {return "X^5";}
  };

  struct cosDoubleAlgorithm final : public integration::Algorithm<double>
  {
    double execute(const double& in) const { return std::cos(in); }
    const char* name() const {return "COS";}
  };

  struct ExpDoubleAlgorithm final : public integration::Algorithm<double>
  {
    double execute(const double& in) const { return std::exp(in); }
    const char* name() const {return "EXP";}
  };

  void print_results( std::ostream& os
                    , double calculated_result
                    , double actual_result
                    , const std::string& algorithm_name
                    , int precision
                    )
  {
    os << algorithm_name << ": "
       << std::setprecision(precision)
       << calculated_result
       << std::endl;

    os << algorithm_name << " % Error: "
       <<  std::setprecision(precision)
       << 100.0*fabs((calculated_result - actual_result)/actual_result)
       << std::endl;
  }

} // ! namespace example

int main(int argc, char *argv[])
{
  example::x4DoubleAlgorithm a;
  example::x5DoubleAlgorithm b;
  example::cosDoubleAlgorithm c;
  example::ExpDoubleAlgorithm d;

  std::array<integration::Algorithm<double>*, 4> arr {&a, &b, &c, &d};
  constexpr std::array<double, 4> actual_result {6.4, 10.66666667, 0.90929743, 6.389056};

  constexpr double START = 0.0;
  constexpr double FINISH = 2.0;
  constexpr std::array<std::size_t, 3> step_size {10, 100, 1000};
  constexpr int precision = 8;

  for (std::size_t i = 0; i < arr.size(); ++i)
  {
    const auto& al = arr[i];
    const auto& ar = actual_result[i];
    std::cout << al->name() << std::endl;
    std::cout << "Actual result: " << ar << std::endl;
    std::cout << std::endl;

    double cr;
    /*
    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::first_ordinate<double>);
      example::print_results(std::cout, cr, ar, "First Ordinate", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::last_ordinate<double>);
      example::print_results(std::cout, cr, ar, "Last Ordinate", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::mid_ordinate<double>);
      example::print_results(std::cout, cr, ar, "Mid Ordinate", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::trapezium<double>);
      example::print_results(std::cout, cr, ar, "Trapezium", 8);
    }
    std::cout << std::endl;
    */
    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::weighted_mo_trap<double>);
      example::print_results(std::cout, cr, ar, "Weighted Mid Ordinate & Trapezium", 8);
    }
    std::cout << std::endl;

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
