#include <iostream>
#include <cstdlib>
#include <array>
#include <iomanip>
#include <cstddef>
#include <string>
#include <cmath>

#include "integration.h"
#include "algorithm.h"
#include "integrators/first_ordinate.h"
#include "integrators/last_ordinate.h"
#include "integrators/mid_ordinate.h"
#include "integrators/trapezium.h"
#include "integrators/simpson.h"

namespace testing
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

} // ! namespace testing

int main(int argc, char *argv[])
{
  testing::x4DoubleAlgorithm a;
  testing::x5DoubleAlgorithm b;
  testing::cosDoubleAlgorithm c;
  testing::ExpDoubleAlgorithm d;

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

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::integrators::first_ordinate<double>);
      testing::print_results(std::cout, cr, ar, "First Ordinate", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::integrators::last_ordinate<double>);
      testing::print_results(std::cout, cr, ar, "Last Ordinate", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::integrators::mid_ordinate<double>);
      testing::print_results(std::cout, cr, ar, "Mid Ordinate", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::integrators::trapezium<double>);
      testing::print_results(std::cout, cr, ar, "Trapezium", 8);
    }
    std::cout << std::endl;

    for (size_t N : step_size)
    {
      std::cout << "N: " << N << std::endl;
      cr = integration::integrate<double>(START, FINISH, N, *al, integration::integrators::simpson<double>);
      testing::print_results(std::cout, cr, ar, "Simpson", 8);
    }
    std::cout << std::endl;

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
