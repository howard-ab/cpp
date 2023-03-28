#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  explicit Matrix();
  explicit Matrix(T elem);
  explicit Matrix(const std::vector<std::vector<T>>& nums);
  Matrix& operator+=(const Matrix<N, M, T>& other);
  Matrix& operator-=(const Matrix& other);
  template <size_t L>
  Matrix<N, L, T> operator*=(const Matrix<M, L, T>& del);
  Matrix<N, M, T> operator*(const T& number);
  T& operator()(const size_t& i_num, const size_t& j_num);
  const T& operator()(const size_t& i_num, const size_t& j_num) const;
  Matrix<M, N, T> Transposed();
  T Trace();

 private:
  std::vector<std::vector<T>> matrix_;
};
template <size_t N, size_t M, typename T>
template <size_t L>
Matrix<N, L, T> Matrix<N, M, T>::operator*=(const Matrix<M, L, T>& del) {
  Matrix<N, L, T> res(0);
  for (size_t k = 0; k < L; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        res(i, k) += matrix_[i][j] * del(j, k);
      }
    }
  }
  return res;
}

template <size_t N, size_t M, typename T>
const T& Matrix<N, M, T>::operator()(const size_t& i_num,
                                     const size_t& j_num) const {
  return matrix_[i_num][j_num];
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(const T& number) {
  Matrix copy(*this);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      copy(i, j) *= number;
    }
  }
  return copy;
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(const size_t& i_num, const size_t& j_num) {
  return matrix_[i_num][j_num];
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const std::vector<std::vector<T>>& nums) {
  matrix_ = nums;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() {
  std::vector<std::vector<T>> new_matrix(N, std::vector<T>(M, 0));
  matrix_ = new_matrix;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T elem) {
  matrix_.resize(N, std::vector<T>(M));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] = elem;
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] += other(i, j);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, size_t M, size_t L, typename T>
Matrix<N, L, T> operator*(const Matrix<N, M, T>& first,
                          const Matrix<M, L, T>& second) {
  Matrix res(first);
  return res *= second;
}

template <size_t N, size_t M, typename T, typename P>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& first,
                          const Matrix<N, M, P>& second) {
  Matrix res(first);
  return res += second;
}

template <size_t N, size_t M, typename T, typename P>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& k_first,
                          const Matrix<N, M, P> kSecond) {
  Matrix<N, M, T> res(k_first);
  return res -= kSecond;
};

template <size_t N, size_t M, typename T>
bool operator==(const Matrix<N, M, T>& first, const Matrix<N, M, T>& second) {
  for (size_t i = 0; i < N; ++i) {
    if (first[i] != second[i]) {
      return false;
    }
  }
  return true;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& operator!=(const Matrix<N, M, T>& first,
                            const Matrix<N, M, T>& second) {
  return !(first == second);
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() {
  Matrix<M, N, T> res;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      res(i, j) = matrix_[j][i];
    }
  }
  return res;
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::Trace() {
  T count = 0;
  for (size_t i = 0; i < M; ++i) {
    count += matrix_[i][i];
  }
  return count;
}
