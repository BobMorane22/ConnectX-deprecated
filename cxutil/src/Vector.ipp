template<typename T, std::size_t N>
math::Vector<T, N>::Vector()
    : m_origin{math::Point<T, N>()}
    , m_destination{math::Point<T, N>()}
{
}


template<typename T, std::size_t N>
math::Vector<T, N>::Vector(math::Point<T, N> p_origin, Point<T, N> p_destination)
    : m_origin{p_origin}
    , m_destination{p_destination}
{
}


template<typename T, std::size_t N>
inline T math::Vector<T, N>::x() const
{
    static_assert(N >= 1 && N < 4, "Invalid dimension.");

    return m_destination.x() - m_origin.x();
}


template<typename T, std::size_t N>
inline T math::Vector<T, N>::y() const
{
    static_assert(N >= 2 && N < 4, "Invalid dimension.");

    return m_destination.y() - m_origin.y();
}


template<typename T, std::size_t N>
inline T math::Vector<T, N>::z() const
{
    static_assert(N == 3, "Invalid dimension.");

    return m_destination.z() - m_origin.z();
}


template<typename T, std::size_t N>
inline const T math::Vector<T, N>::operator[](int p_index) const
{
    return m_destination[p_index] - m_origin[p_index];
}


template<typename T, std::size_t N>
math::Vector<T, N> math::Vector<T, N>::operator-() const
{
    return math::Vector<T, N>{m_destination, m_origin};
}


template<typename T, std::size_t N>
math::Vector<T, N>& math::Vector<T, N>::operator+=(const math::Vector<T, N>& p_vector)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = m_destination[i] + p_vector[i];
    }

    return *this;
}


template<typename T, std::size_t N>
math::Vector<T, N>& math::Vector<T, N>::operator-=(const Vector<T, N>& p_vector)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = m_destination[i] - p_vector[i];
    }

    return *this;
}


template<typename T, std::size_t N>
math::Vector<T, N>& math::Vector<T, N>::operator*=(const T& p_scalar)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = m_origin[i] + p_scalar * (*this)[i];
    }

    return *this;
}


template<typename T, std::size_t N>
T math::dotProduct(const math::Vector<T, N>& p_v1, const math::Vector<T, N>& p_v2)
{
    // Attention: on assume que T() veut dire zéro!
    T product = T();

    for(std::size_t i{0}; i < N; ++i)
    {
        product += (p_v1[i] * p_v2[i]);
    }

    return product;
}


template<typename T, std::size_t N>
const math::Vector<T, N>& math::additionIdentity()
{
    static const math::Vector<T, N> identity;

    return identity;
}


template<typename T, std::size_t N>
bool math::operator==(const math::Vector<T, N>& p_v1, const math::Vector<T, N>& p_v2)
{
    bool areEqual{true};

    for(std::size_t i{0}; i < N; ++i)
    {
        areEqual &= (p_v1[i] == p_v2[i]);
    }

    return areEqual;
}


template<typename T, std::size_t N>
bool math::operator!=(const math::Vector<T, N>& p_v1, const math::Vector<T, N>& p_v2)
{
    return !(p_v1 == p_v2);
}


template<typename T, std::size_t N>
math::Vector<T, N> math::operator+(const math::Vector<T, N>& p_v1, const math::Vector<T, N>& p_v2)
{
    return math::Vector<T, N>{p_v1} += p_v2;
}


template<typename T, std::size_t N>
math::Vector<T, N> math::operator-(const math::Vector<T, N>& p_v1, const math::Vector<T, N>& p_v2)
{
    return math::Vector<T, N>{p_v1} -= p_v2;
}


template<typename T, std::size_t N>
math::Vector<T, N> math::operator*(const T& p_scalar, const Vector<T, N>& p_vector)
{
    math::Vector<T, N> temp{p_vector};
    return temp *= p_scalar;
}


template<typename T, std::size_t N>
math::Vector<T, N> math::operator*(const Vector<T, N>& p_vector, const T& p_scalar)
{
    math::Vector<T, N> temp{p_vector};
    return temp *= p_scalar;
}