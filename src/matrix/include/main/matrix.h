#ifndef GUARD_MATRIX_H_
#define GUARD_MATRIX_H_

#include <array>
#include <cstddef>
#include <type_traits>
#include <string>
#include <cmath>
#include <initializer_list>
#include <iostream>

namespace matrix
{

  template<typename T, std::size_t R, std::size_t C>
  class Matrix
  {
  public:

    static_assert(R != 0, "Zero rows are not permitted.");
    static_assert(C != 0, "Zero columns are not permitted.");
    static_assert( std::is_arithmetic<T>::value
                   , "Data type must be of arithmetic type."
      );

    // aliases
    using row_sz = typename std::array<std::array<T,C>, R>::size_type;
    using col_sz = typename std::array<T,C>::size_type;

    // structors
    Matrix();
    Matrix(const std::initializer_list<T>& data);
    Matrix(const T data[R][C]);
    Matrix(std::array<std::array<T, C>, R>&& data);
    Matrix(const Matrix& m) = default;
    Matrix& operator=(const Matrix& m) = default;
    Matrix(Matrix&& m) = default;
    Matrix& operator=(Matrix&& m) = default;
    ~Matrix() = default;

    // accessors and mutators
    const T& element(row_sz r, col_sz c) const;
    T& element(row_sz, col_sz);

    void clear();
    row_sz num_rows() const;
    col_sz num_cols() const;

    // Other methods
    T det() const;
    void print(std::ostream& os) const;

    // static methods
    static Matrix identity();

    // compound assignment arithmetic operators
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const T& t);

  private:
    std::array<std::array<T, C>, R> m_data;

  }; // ! class Matrix

// Definitions of Matrix methods
  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>::Matrix()
  {
    for (Matrix::row_sz r = 0; r < R; ++r)
    {
      for (Matrix::col_sz c = 0; c < C; ++c)
      {
        m_data[r][c] = T();
      }
    }
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>::Matrix(const std::initializer_list<T>& data)
  {
    row_sz row = 0;
    col_sz col = 0;
    typename std::initializer_list<T>::size_type count = 0;
    for(const auto& t : data)
    {
      if(++count > R*C)
      {
        std::cout << "Warning: Truncating " << data.size()
                  << " elements to " << R*C << " elements."
                  << std::endl;
        return;
      }

      if (col >= C)
      {
        col = 0;
        ++row;
      }

      m_data[row][col++] = t;
    }
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>::Matrix(const T data[R][C])
  {
    for (Matrix::row_sz r = 0; r < R; ++r)
    {
      for (Matrix::col_sz c = 0; c < C; ++c)
      {
        m_data[r][c] = data[r][c];
      }
    }
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>::Matrix(std::array<std::array<T,C>,R>&& data)
    : m_data(data)
  {}

  template<typename T, std::size_t R, std::size_t C>
  const T& Matrix<T,R,C>::element(row_sz r, col_sz c) const
  {
    return m_data[r][c];
  }

  template<typename T, std::size_t R, std::size_t C>
  T& Matrix<T,R,C>::element(row_sz r, col_sz c)
  {
    return const_cast<T&>((static_cast<const Matrix<T,R,C>&>(*this)).element(r,c));
  }

  template<typename T, std::size_t R, std::size_t C>
  void Matrix<T,R,C>::clear()
  {
    for(auto& row : m_data)
    {
      row->fill(T());
    }
  }

  template<typename T, std::size_t R, std::size_t C>
  typename Matrix<T,R,C>::row_sz
  Matrix<T,R,C>::num_rows() const
  {
    return static_cast<row_sz>(R);
  }

  template<typename T, std::size_t R, std::size_t C>
  typename Matrix<T,R,C>::col_sz
  Matrix<T,R,C>::num_cols() const
  {
    return static_cast<col_sz>(C);
  }

  template<>
  int Matrix<int,2,2>::det() const
  {
    return element(0,0)*element(1,1) - element(0,1)*element(1,0);
  }

  template<>
  int Matrix<int,1,1>::det() const
  {
    return element(0,0);
  }

  template<>
  double Matrix<double,2,2>::det() const
  {
    return element(0,0)*element(1,1) - element(0,1)*element(1,0);
  }

  template<>
  double Matrix<double,1,1>::det() const
  {
    return element(0,0);
  }

  template<typename T, std::size_t R, std::size_t C>
  T Matrix<T,R,C>::det() const
  {
    static_assert(R == C, "Cannot calculate determinant for rectangular matrix.");

    T determinant = T();

    for(col_sz col = 0; col < R; ++col)
    {
      const double coefficient = std::pow(-1.0, 0+col)*element(0,col);

      Matrix<T, R-1, C-1> v;
      for (row_sz r = 1; r < R; ++r)
      {
        for(col_sz c = 0; c < col; ++c)
        {
          v.element(r-1,c) = element(r,c);
        }

        for(col_sz c = col+1; c < C; ++c)
        {
          v.element(r-1,c-1) = element(r,c);
        }
      }

      determinant += coefficient * v.det();
    }

    return determinant;
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>& Matrix<T,R,C>::operator+=(const Matrix& other)
  {
    if (this != &other)
    {
      for (Matrix::row_sz r = 0; r < R; ++r)
      {
        for (Matrix::col_sz c = 0; c < C; ++c)
        {
          m_data[r][c] += other.m_data[r][c];
        }
      }
    }

    return *this;
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>& Matrix<T,R,C>::operator-=(const Matrix& other)
  {
    if (this != &other)
    {
      for (Matrix::row_sz r = 0; r < R; ++r)
      {
        for (Matrix::col_sz c = 0; c < C; ++c)
        {
          m_data[r][c] -= other.m_data[r][c];
        }
      }
    }

    return *this;
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>& Matrix<T,R,C>::operator*=(const Matrix& other)
  {
    static_assert(R == C, "Cannot compound multiply rectangular Matix.");

    Matrix m;

    for (Matrix::row_sz curr_r = 0; curr_r < R; ++curr_r)
    {
      for (Matrix::col_sz curr_c = 0; curr_c < C; ++curr_c)
      {
        for (Matrix::row_sz k = 0; k < R; ++k)
        {
          m.m_data[curr_r][curr_c] += m_data[curr_r][k]*other.m_data[k][curr_c];
        }
      }
    }

    m_data.swap(m.m_data);

    return *this;
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C>& Matrix<T,R,C>::operator*=(const T& t)
  {
    for (Matrix::row_sz r = 0; r < R; ++r)
    {
      for (Matrix::col_sz c = 0; c < C; ++c)
      {
        m_data[r][c] *= t;
      }
    }

    return *this;
  }

  template<typename T, std::size_t R, std::size_t C>
  void Matrix<T,R,C>::print(std::ostream& os) const
  {
    const std::string header = "--" + std::string(2*C-1,' ') + "--";

    os << "\n" << header << "\n";
    for (Matrix::row_sz r = 0; r < R; ++r)
    {
      os << "|";
      for (Matrix::col_sz c = 0; c < C; ++c)
      {
        const T t = m_data[r][c];
        if (t >= T())
        {
          os << " ";
        }
        os << m_data[r][c];
      }
      os << " |" << "\n";
    }

    os << header << std::endl;
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C> Matrix<T,R,C>::identity()
  {
    Matrix<T,R,C> I;
    for (Matrix::row_sz r = 0; r < R; ++r)
    {
      for (Matrix::col_sz c = 0; c < C; ++c)
      {
        I.m_data[r][c] = r == c ? T(1) : T(0);
      }
    }

    return I;
  }

// Matrix non-member functions
  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C> operator+(const Matrix<T,R,C>& lhs, const Matrix<T,R,C>& rhs)
  {
    Matrix<T,R,C> m = lhs;
    m += rhs;
    return m;
  }

  template<typename T, std::size_t R, std::size_t C>
  Matrix<T,R,C> operator-(const Matrix<T,R,C>& lhs, const Matrix<T,R,C>& rhs)
  {
    Matrix<T,R,C> m = lhs;
    m -= rhs;
    return m;
  }

  template<typename T, std::size_t R, std::size_t C, std::size_t OC>
  Matrix<T,R,OC> operator*(const Matrix<T,R,C>& m, const Matrix<T,C,OC>& other)
  {
    static_assert(R == OC, "Cannot compound multiply rectangular Matix.");

    Matrix<T,R,OC> ret;
    for (typename Matrix<T,R,OC>::row_sz curr_r = 0; curr_r < R; ++curr_r)
    {
      for (typename Matrix<T,R,OC>::col_sz curr_c = 0; curr_c < OC; ++curr_c)
      {
        ret.element(curr_r, curr_c) = T();
        for (typename Matrix<T,R,C>::row_sz k = 0; k < R; ++k)
        {
          ret.element(curr_r, curr_c) += m.element(curr_r, k)*other.element(k, curr_c);
        }
      }
    }

    return ret;
  }

// Insertion operator
  template<typename T, std::size_t R, std::size_t C>
  std::ostream& operator<< (std::ostream& os, const Matrix<T,R,C>& m)
  {
    m.print(os);
    return os;
}

} // ! namespace matrix

#endif // ! GUARD_MATRIX_H_
