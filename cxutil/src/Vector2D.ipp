// See: https://stackoverflow.com/questions/243945/calculating-a-2d-vectors-cross-product

template<typename T>
void math::crossProduct(const math::Vector<T, 2>& p_v1, const math::Vector<T, 2>& p_v2, T& p_result)
{
    p_result = (p_v1.x() * p_v2.y()) - (p_v1.y() * p_v2.x());
}