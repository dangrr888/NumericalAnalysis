#include <cstdlib>
#include <iostream>
#include "Matrix.h"

int main(int argc, char *argv[])
{
  /*
  int a[1][3] = {1,1,1};
  matrix::Matrix<int,1,3> A(a);

  int b[3][1] = {{1},{1},{1}};
  matrix::Matrix<int,3,1> B(b);

  std::cout << A << std::endl;
  std::cout << B << std::endl;

  matrix::Matrix<int,1,1> C = A*B;

  std::cout << C << std::endl;

  std::cout << matrix::Matrix<int,10,10>::identity() << std::endl;
  */

/*
  int a[4][4] = {{1,2,3,1},
                 {-1,0,2,1},
                 {2,1,-3,0},
                 {1,1,2,1}};
  matrix::Matrix<int,4,4> A(a);

  std::cout << "A: " << A << std::endl;
  std::cout << "det(A): " << A.det() << std::endl;
*/

  matrix::Matrix<double,3,3> m= {1,2,3,
                                 4,5,6,
                                 7,8,9};
  std::cout << m << std::endl;



  return EXIT_SUCCESS;
}
