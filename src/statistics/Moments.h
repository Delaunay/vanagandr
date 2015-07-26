#ifndef VANAGANDR_STATISTIC_MOMENTS_HEADER
#define VANAGANDR_STATISTIC_MOMENTS_HEADER

template<typename T, typename Index = unsigned int>
T sum(const T* array, const Index& n)
{
    T m = 0;
    for (Index i = 0; i < n; i++)
        m += array[i];

    return m;
}

template<typename T, typename Index = unsigned int>
T mean(const T* array, const Index& n)
{
    return sum(array, n) / T(n);
}

/*!
 * Complexity
 * -----------
 *  O(n)
 *
 * Implementation
 * --------------
 *
 * We are using the following property Var(X + C) = Var(X)
 * we substract the first observation to increase stability
 * while computing variance of large numbers.
 *
 */
template<typename T, typename Index = unsigned int>
T variance(const T* array, const Index& n)
{
    T m1 = 0,
      m2 = 0,
      m0 = array[0];

    for (Index i = 1; i < n; i++)
    {
        T t = array[i] - m0;
        m1 += t;
        m2 += t * t;
    }

    return (m2 - m1 * m1) / T(n);
}

#include<tuple>

template<typename T, typename Index = unsigned int>
std::pair<T, T> variance_mean(const T* array, const Index& n)
{
    T m1 = 0,
      m2 = 0,
      m0 = array[0];

    for (Index i = 1; i < n; i++)
    {
        T t = array[i] - m0;
        m1 += t;
        m2 += t * t;
    }

    return std::pair<T, T>(m1 / T(n) + m0, (m2 - m1 * m1) / T(n));
}

// Kurtosis

// Skew

#endif
