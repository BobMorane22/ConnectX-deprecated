#include<algorithm>
#include<array>

namespace math
{

template<typename T, typename std::size_t N>
class Point
{

public:

    Point();
    
    Point(const T& p_x);
    Point(const T& p_x, const T& p_y);
    Point(const T& p_x, const T& p_y, const T& p_z);
    
    ~Point();
    
    T x() const;
    T y() const;
    T z() const;
    
    T& x();
    T& y();
    T& z();

    const T& operator[](int p_index) const;
    T& operator[](int p_index);

    Point& operator+(const Point& p_point) = delete;
    Point& operator-(const Point& p_point) = delete;
    Point& operator*(const Point& p_point) = delete;
    Point& operator/(const Point& p_point) = delete;
    Point& operator%(const Point& p_point) = delete;

private:
    std::array<T, N> m_coordinates;

};

using Point1D = Point<double, 1>;
using Point2D = Point<double, 2>;
using Point3D = Point<double, 3>;

} // namespace math

#include "Point.ipp"
