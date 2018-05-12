#include "Point.h"

namespace math
{

template <typename T, N>
class LineSegment
{

public:
    LineSegment() = delete;
    LineSegment(const Point<T, N>& m_fisrtEndpoint, const Point<T, N>& m_secondEndpoint);

    ~LineSegment();
    
private:
    Point<T, N> m_fisrtEndpoint;
    Point<T, N> m_secondEndpoint;

};

using LineSegment2D = LineSegment<double, 2>;
using LineSegment3D = LineSegment<double, 3>;

bool areParallel(const LineSegment2D& p_first, const LineSegment2D& p_second);
bool arePerpendicular(const LineSegment2D& p_first, const LineSegment2D& p_second);
bool areColinear(const LineSegment2D& p_first, const LineSegment2D& p_second);

bool intersect(const LineSegment2D& p_first, const LineSegment2D& p_second, bool considerEndpoints = false);

} // namespace math

//bool math::areParallel(const math::LineSegment2D& p_first, const math::LineSegment2D& p_second)
//{
//
//}