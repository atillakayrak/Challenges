#include "Matrix.h"


template <typename T, size_t Rows, size_t Columns>
constexpr core::Matrix<T, Rows, Columns>::Matrix(T(&&values)[Rows][Columns])
{
    std::copy_n(*values, Columns * Rows, begin());
}


template <typename T, size_t Rows, size_t Columns>
constexpr core::Matrix<T, Rows, Columns>::Matrix(const T fillValue)
{
    std::fill(begin(), end(), fillValue);
}


template <typename T, size_t Rows, size_t Columns>
constexpr auto core::Matrix<T, Rows, Columns>::begin() -> T *
{
    return *m_data;
}


template <typename T, size_t Rows, size_t Columns>
constexpr auto core::Matrix<T, Rows, Columns>::end() -> T *
{
    return *m_data + Columns * Rows;
}


template <typename T, size_t Rows, size_t Columns>
constexpr auto core::Matrix<T, Rows, Columns>::begin() const -> T const *
{
    return *m_data;
}


template <typename T, size_t Rows, size_t Columns>
constexpr auto core::Matrix<T, Rows, Columns>::end() const -> T const *
{
    return *m_data + Columns * Rows;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::cast() const -> SameSizeMatrix<T2>
{
    if constexpr (std::is_same<T, T2>::value)
    {
        return *this;
    }
    else
    {
        auto out = SameSizeMatrix<T2>();
        std::copy(begin(), end(), out.begin());
        return out;
    }
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator+=(const SameSizeMatrix<T2> &m2) -> Matrix &
{
    std::transform(m2.begin(), m2.end(), begin(), begin(), std::plus<T>());
    return *this;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator+(const SameSizeMatrix<T2> &m2) const
    -> SameSizeMatrix<ArithmeticResult<T2>>
{
    auto out = m2.cast<ArithmeticResult<T2>>();
    return out += *this;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator-=(const SameSizeMatrix<T2> &m2)
    -> SameSizeMatrix<ArithmeticResult<T2>> &
{
    std::transform(m2.begin(), m2.end(), begin(), begin(), std::minus<T>());
    return *this;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator-(const SameSizeMatrix<T2> &m2) const
    -> SameSizeMatrix<ArithmeticResult<T2>>
{
    auto out = m2.cast<ArithmeticResult<T2>>();
    return out -= *this;
}


template <typename T, size_t Rows, size_t Columns>
constexpr auto core::Matrix<T, Rows, Columns>::operator[](const size_t i) -> T (&)[Columns]
{
    return m_data[i];
}


template <typename T, size_t Rows, size_t Columns>
constexpr auto core::Matrix<T, Rows, Columns>::operator[](const size_t i) const -> T
    const (&)[Columns]
{
    return m_data[i];
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator==(const SameSizeMatrix<T2> &m2) const
    -> bool
{
    return std::find_if(begin(), end(), [it2 = m2.begin()](const T v1) mutable {
               return v1 != *(it2++);
           }) == end();
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator!=(const SameSizeMatrix<T2> &m2) const
    -> bool
{
    return !operator==(m2);
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator*(const TransposedMatrix<T2> &m2) const
    -> SquareMatrix<ArithmeticResult<T2>, Rows>
{
    auto out = SquareMatrix<ArithmeticResult<T2>, Rows>(0);

    for (int r = 0; r < Rows; ++r)
    {
        for (int c = 0; c < Rows; ++c)
        {
            for (int i = 0; i < Columns; ++i)
                out[r][c] += (*this)[r][i] * m2[i][c];
        }
    }

    return out;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator*=(const T2 &value)
    -> SameSizeMatrix<ArithmeticResult<T2>> &
{
    for (auto &v : *this)
        v *= value;
    return *this;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator*(const T2 &value) const
    -> SameSizeMatrix<ArithmeticResult<T2>>
{
    auto out = cast<ArithmeticResult<T2>>();
    return out *= value;
}


template <typename T, size_t Rows, size_t Columns, typename T2>
constexpr auto operator*(const T2 &value, const core::Matrix<T, Rows, Columns> &matrix)
{
    return matrix * value;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator/=(const T2 &value)
    -> SameSizeMatrix<ArithmeticResult<T2>> &
{
    for (auto &v : *this)
        v /= value;
    return *this;
}


template <typename T, size_t Rows, size_t Columns>
template <typename T2>
constexpr auto core::Matrix<T, Rows, Columns>::operator/(const T2 &value) const
    -> SameSizeMatrix<ArithmeticResult<T2>>
{
    auto out = cast<ArithmeticResult<T2>>();
    return out /= value;
}


template <typename T, size_t Rows, size_t Columns>
auto core::Matrix<T, Rows, Columns>::toStr() const -> std::string
{
    auto ss = std::stringstream();

    ss << '[';

    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Columns; ++j)
        {
            ss << m_data[i][j];
            if (j < Columns - 1)
                ss << ' ';
        }

        if (i < Rows - 1)
            ss << "\n ";
    }

    ss << ']';

    return ss.str();
}
