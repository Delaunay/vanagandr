
#include "../math/Function.h"

namespace vanagandr
{
/*
    double absolute(double a)
    {
        return pow( a * a, 0.5);
    }*/

	Real combin(Real n, Real i)
	{
		return  boost::math::factorial<double>(n) / ( boost::math::factorial<double>(i) * boost::math::factorial<double>(n - i)	) ;
	}

	Real derivateFiniteDifference(SingleVariableFunction a, Derivative d, Real x, Real h)
	{
		Real sum = 0;

		for( int i = 0; i <= d ; i ++)
			sum = sum + pow( -1.0, (double) i ) * combin(d, i) * a(x + (double) (d/2.0 - (double) i) * h );

		return sum;
	}

	Real derivateNumerical(SingleVariableFunction a, Derivative d, Real x, Real h)
	{
		//if (d == 1)
			return ( a(x + h) - a(x) ) / h;
		//else
		//	return (derivateNumerical(a, d - 1, x + h) - derivateNumerical(a, d - 1, x) ) / h;
	}

	Matrix SingleVariableFunction::createTable(Real Min, Real Max, ID step)
	{
		Matrix S(step, 2);

		Real Slope = (Max - Min)/Real(step - 1);

		for(int i = 0; i < step ; i ++)
		{
			S(i, 0) = Min + Slope * Real(i);
			S(i, 1) = this->operator ()(S(i, 0));
		}

		return S;
	}
}
