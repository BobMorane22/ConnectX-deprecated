template<typename T, std::size_t N>
math::Point<T, N>::Point()
{
    static_assert(N >= 1 && N < 4, "Invalid number of coordinates.");

    std::fill(m_coordinates.begin(), m_coordinates.end(), T());
}


template<typename T, std::size_t N>
math::Point<T, N>::Point(const T& p_x)
{
    static_assert(N == 1, "A one dimensional point must have exactly one coordinate.");
    
    x() = p_x;
}


template<typename T, std::size_t N>
math::Point<T, N>::Point(const T& p_x, const T& p_y)
{
    static_assert(N == 2, "A two dimensional point must have exactly two coordinates.");
    
    x() = p_x;
    y() = p_y;
}


template<typename T, std::size_t N>
math::Point<T, N>::Point(const T& p_x, const T& p_y, const T& p_z)
{
    static_assert(N == 3, "A three dimensional point must have exactly three coordinates.");
    
    x() = p_x;
    y() = p_y;
    z() = p_z;
}


template<typename T, std::size_t N>
math::Point<T, N>::~Point() = default;


template<typename T, std::size_t N>
inline T math::Point<T, N>::x() const
{
    static_assert(N >= 1 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[0];
}


template<typename T, std::size_t N>
inline T math::Point<T, N>::y() const
{
    static_assert(N >= 2 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[1];
}


template<typename T, std::size_t N>
inline T math::Point<T, N>::z() const
{
    static_assert(N == 3, "Invalid number of coordinates.");

    return m_coordinates[2];
}


template<typename T, std::size_t N>
inline T& math::Point<T, N>::x()
{
    static_assert(N >= 1 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[0];
}


template<typename T, std::size_t N>
inline T& math::Point<T, N>::y()
{
    static_assert(N >= 2 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[1];
}


template<typename T, std::size_t N>
inline T& math::Point<T, N>::z()
{
    static_assert(N == 3, "Invalid number of coordinates.");

    return m_coordinates[2];
}


template<typename T, std::size_t N>
inline const T& math::Point<T, N>::operator[](int p_index) const
{
    return m_coordinates[p_index];
}


template<typename T, std::size_t N>
inline T& math::Point<T, N>::operator[](int p_index)
{
    return const_cast<T&>(const_cast<const math::Point<T, N>&>(*this)[p_index]);
}