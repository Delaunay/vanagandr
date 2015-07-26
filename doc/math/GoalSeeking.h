#ifndef GOALSEEKING_H
#define GOALSEEKING_H

#include "../Enum.h"

namespace vanagandr
{
	// Golden Section
    template <class F>
    Real goldenSection	(F f, Real a = 0, Real b = 1, Real Precision = 0.00001)
    {
        Real to = (pow(5.0, 0.5) - 1.0)/2.0;
        Real a2;
        Real b2;

        while(abs(b - a) > Precision)
        {
            a2 = a + ( 1.0 - to) * (b - a);
            b2 = a +  to * (b - a);

            if( f(a2) < f(b2))
            {
                b = b2;
            }
            else
            {
                if(f(a2) > f(b2))
                    a = a2;
                else
                {
                    a = a2;
                    b = b2;
                }
            }
        }

        return (a + b)/2.0;
    }

	// Méthode du gradient avec pas fixe
    template <class F>
    Real gradient		(F f, Real x = 0, Real step = 0.1, Real Precision = 0.00001)
    {
        while(abs(f.derivate(x, 1)) > Precision)
        {
            x = x - step * f.derivate(x, 1);
        }

        return x;
    }

	// Méthode de Newton-Raphson
    template <class F>
    Real newtonRaphson	(F f, Real x = 0, Real Precision = 0.00001)
    {
        while( abs(f.derivate(x, 1)) > Precision)
        {
            x = x -  f.derivate(x, 1)/f.derivate(x, 2);
        }

        return x;
    }

	// Méthode de bisection
    template <class F>
    Real bisection		(F f, Real target = 0, Real a = 0, Real b = 1, Real Precision = 0.00001)
    {
        Real x = 0;

        while (abs(a - b) > Precision)
        {
            x = a + (b - a)/2;

            if ( ( f(a) - target ) * ( f(x) - target ) < 0)
                b = x;
            else
                a = x;
        }

        return x;
    }

	// Méthode de point fixe
    template <class F>
    Real fixedPoint		(F f, Real target = 0, Real Precision = 0.00001)
    {
        Real x;

        while (abs(f(x) - target) > Precision)
        {
            x = f(x);
        }

        return x;
    }

	// Méthode de bisection
    template <class F>
    Real secante		(F f, Real target = 0, Real a = 0, Real b = 1, Real Precision = 0.00001)
    {
        Real x = 0;

        while(abs(a - b) > Precision)
        {
            x = a - ( f(a) - target) * (b - a) / (f(b) - f(a));

            if( ( f(x)  - target ) * ( f(b) - target ) > 0)
                b = x;
            else
                a = x;
        }

        return x;
    }

}
#endif // GOALSEEKING_H
