#pragma once

#include <algorithm>
#include <functional>
#include <sstream>
#include <vector>

#include "Tools.h"


namespace core
{
template <typename T, size_t Rows, size_t Columns>
class Matrix
{
    template <typename T2>
    using SameSizeMatrix = Matrix<T2, Rows, Columns>;

    template <typename T2>
    using TransposedMatrix = Matrix<T2, Columns, Rows>;

    template <typename T2, size_t Length>
    using SquareMatrix = Matrix<T2, Length, Length>;

    template <typename T2>
    using ArithmeticResult = decltype(T{} * T2{});

 public:
    constexpr Matrix(T fillValue = {});
    constexpr Matrix(T(&&values)[Rows][Columns]);

    template <typename T2>
    constexpr auto cast() const -> SameSizeMatrix<T2>;

    constexpr auto begin() -> T *;
    constexpr auto end() -> T *;

    constexpr auto begin() const -> T const *;
    constexpr auto end() const -> T const *;

    template <typename T2>
    constexpr auto operator+=(const SameSizeMatrix<T2> &m2) -> Matrix &;

    template <typename T2>
    constexpr auto operator+(const SameSizeMatrix<T2> &m2) const
        -> SameSizeMatrix<ArithmeticResult<T2>>;

    template <typename T2>
    constexpr auto operator-=(const SameSizeMatrix<T2> &m2)
        -> SameSizeMatrix<ArithmeticResult<T2>> &;

    template <typename T2>
    constexpr auto operator-(const SameSizeMatrix<T2> &m2) const
        -> SameSizeMatrix<ArithmeticResult<T2>>;

    template <typename T2>
    constexpr auto operator*(const TransposedMatrix<T2> &m2) const
        -> SquareMatrix<ArithmeticResult<T2>, Rows>;

    template <typename T2>
    constexpr auto operator*=(const T2 &value) -> SameSizeMatrix<ArithmeticResult<T2>> &;

    template <typename T2>
    constexpr auto operator*(const T2 &value) const -> SameSizeMatrix<ArithmeticResult<T2>>;

    template <typename T2>
    constexpr auto operator/=(const T2 &value) -> SameSizeMatrix<ArithmeticResult<T2>> &;

    template <typename T2>
    constexpr auto operator/(const T2 &value) const -> SameSizeMatrix<ArithmeticResult<T2>>;

    constexpr auto operator[](size_t i) -> T (&)[Columns];
    constexpr auto operator[](size_t i) const -> T const (&)[Columns];

    template <typename T2>
    constexpr auto operator==(const SameSizeMatrix<T2> &m2) const -> bool;

    template <typename T2>
    constexpr auto operator!=(const SameSizeMatrix<T2> &m2) const -> bool;

    auto toStr() const -> std::string;

 private:
    T m_data[Rows][Columns];
};

}  // namespace core

template <typename T, size_t Rows, size_t Columns, typename T2>
constexpr auto operator*(const T2 &value, const core::Matrix<T, Rows, Columns> &matrix);


#include "Matrix.tpp"
