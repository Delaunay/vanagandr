#include "../Enum.h"

namespace vanagandr
{
class Rectangle
{
    public:
        template <class F>
        Real operator() (F f, Real a, Real b)
        {
            return (b - a) *  f( (a + b)/2.0 );
        }
};

class Trapezoidal
{
    public:
        template <class F>
        Real operator() (F f, Real a, Real b)
        {
            return (b - a) * ( f(a) + f(b) )/2.0;
        }
};

class Simpson
{
    public:
        template <class F>
        Real operator() (F f, Real a, Real b)
        {
            return ( ( (b - a) / 6.0 ) * (f(a)  + 4.0 * f( (a + b) / 2.0 ) + f(b) ) );
        }
};


template <class E, class F>
Real integrate(F f, Real a, Real b, Index n = 100)
{
    Real sum = 0;
    Real h = ( b - a ) /n ;
    Real buf = 0;

    E m;

    for (int i = 0; i < n; i++)
    {
        buf = a + i * h;
        sum = sum + m(f, buf, buf + h);
    }

    return sum;
}

// Integration Engine
// Function we are going to integrate
// a lower
// b upper
// n number of intervals

template <class E, class F>
Real integrate(Real a, Real b, Index n = 100)
{
    Real sum = 0;
    Real h = ( b - a ) /n ;
    Real buf = 0;

    E m;
    F f;

    for (int i = 0; i < n; i++)
    {
        buf = a + i * h;
        sum = sum + m(f, buf, buf + h);
    }

    return sum;
}

}
