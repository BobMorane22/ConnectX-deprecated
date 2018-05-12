template<typename T>
void math::crossProduct(const math::Vector<T, 3>& p_v1, const math::Vector<T, 3>& p_v2, math::Vector<T, 3>& p_result)
{
    p_result = math::Vector<T, 3>{
        math::Point<T, 3>{},
        math::Point<T, 3> { p_v1.y() * p_v2.z() - p_v1.z() * p_v2.y(),
                            p_v1.z() * p_v2.x() - p_v1.x() * p_v2.z(),
                            p_v1.x() * p_v2.y() - p_v1.y() * p_v2.x()
                          }
    };
}