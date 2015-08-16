#include "../finance/Routine.h"

namespace vanagandr
{
namespace BasicFunction
{
	Rate rBey	(Rate BD, double n)
	{
		return 365 * BD  / (360 - (BD  * n));
	}

	Rate rBd	(Rate Bey, double n)
	{
		return 360 * Bey / (365 - (Bey * n));
	}

	Rate rPoly	(Rate r, double n, int output, int input)
	{
		return output * r  / (input - (r  * n));
	}

	Value pv	(Periods n, Rate R,	Value PMT)
	{
		return PMT * exp( - n * R);
	}

	Value pmt(Periods n, Rate R,	Value PV)
	{
		return PV * exp ( n * R);
	}

	Rate r	(Periods n, Value PMT,	Value PV)
	{
		return log( PMT/PV ) / n;
	}

	Periods n	(Rate R, Value PMT,	Value PV)
	{
		return log( PMT/PV ) / R;
	}
/*
	Rate Ri(Rate Rc, int m)
	{
		return (exp(Rc/m) - 1) * m;
	}

	Rate Rf(Rate Ri, int m)
	{
		return 	pow ( (1 + Ri/m),  m) - 1;
	}

	Rate Rc(Rate Ri, int m)
	{
		return 	m * log (1 + Ri/m);
	}*/

	Value annuityPV(Periods n, Rate r, Value pmt, Value N, Rate g)
	{
		return pmt * (1 - pow ( (1 + g)/(1 + r), n) ) / ( r - g) + N / pow( (1 + r), n );
	}
	Value annuityPMT(Periods n, Rate r, Value PV, Value N, Rate g)
	{
		return   (PV - N/ pow( (1 + r), n )) / ((1 - pow ( (1 + g)/(1 + r), n) ) / ( r - g)) ;
	}

	Value annuityFV(Periods n, Rate r, Value pmt, Value N, Rate g)
	{
		return  annuityPV(n, r, pmt, N, g) * pow ( (1 + r), n);
	}

	// Secante
	Value yieldToMaturity(Periods n, Value pmt, Price PV, Price FV, double precision)
	{
		double a = 0;
		double b = 1;
		double x = 0;

		double fa = 0;
		double fb = 0;
		double fx = 0;

		do
		{
			fa = annuityPV(n, a, pmt, FV);
			fb = annuityPV(n, b, pmt, FV);

			x = a - fa *(b - a) / (fb - fa);

			if(fx * fb > 0)
				b = x;
			else
				a = x;

		}while(abs(PV - fx) > precision);

		return x;
	}


	template<typename type>
	type		modulo	(type number, type divisor)
	{
		return number - floor(number/divisor)*divisor;
	}

	Periods	remains (Periods t, int freq)
	{
		return modulo<double>( (double) 1/freq - modulo(t, (double) 1/freq), (double) 1/freq);
	}
	Periods	elapsed (Periods t, int freq)
	{
		return modulo<double>(t, (double) 1/freq);
	}

	Periods	remains (Periods t, Periods freq)
	{
		return modulo<double>( freq - modulo(t, freq), freq);
	}
	Periods	elapsed (Periods t, Periods freq)
	{
		return modulo<double>(t, freq);
	}

}
}
