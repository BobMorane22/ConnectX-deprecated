#include "Point.h"

namespace math
{

template<typename T, std::size_t N>
class Vector
{
public:
    Vector();
    Vector(Point<T, N> p_origin, Point<T, N> p_destination);

    Point<T, N> origin() const { return m_origin; }
    Point<T, N> destination() const { return m_destination; }

    T x() const;
    T y() const;
    T z() const;

    const T operator[](int p_index) const;

    Vector<T, N> operator-() const;

    Vector<T, N>& operator+=(const Vector<T, N>& p_vector);
    Vector<T, N>& operator-=(const Vector<T, N>& p_vector);
    Vector<T, N>& operator*=(const T& p_scalar);

private:
    Point<T, N> m_origin;
    Point<T, N> m_destination;
};

using Vector1D = Vector<double, 1>;
using Vector2D = Vector<double, 2>;
using Vector3D = Vector<double, 3>;

/*************************************** 2D-Specific Operations ***************************************/
template<typename T>
void crossProduct(const Vector<T, 2>& p_v1, const Vector<T, 2>& p_v2, T& p_result);

/*************************************** 3D-Specific Operations ***************************************/
template<typename T>
void crossProduct(const Vector<T, 3>& p_v1, const Vector<T, 3>& p_v2, Vector<T, 3>& p_result);

/*************************************** nD-Specific Operations ***************************************/

template<typename T, std::size_t N>
const Vector<T, N>& additionIdentity();

template<typename T, std::size_t N>
bool operator==(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
bool operator!=(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
Vector<T, N> operator+(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
Vector<T, N> operator-(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
Vector<T, N> operator*(const T& p_scalar, const Vector<T, N>& p_vector);

template<typename T, std::size_t N>
Vector<T, N> operator*(const Vector<T, N>& p_vector, const T& p_scalar);

template<typename T, std::size_t N>
T dotProduct(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

}// namespace math

#include "Vector.ipp"
#include "Vector2D.ipp"
#include "Vector3D.ipp"