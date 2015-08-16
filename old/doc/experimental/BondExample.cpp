#include "../finance/Bond.h"

namespace vanagandr
{


/*bool Bond::setBond(int Npmt, Rate Coupon, Value NV, Rate ytm)
{
	if (!fset)
	{
		double pmt = Coupon * NV;

		for (int i = 0 ; i < Npmt - 1 ; i ++)
			this->add(CashFlow( ( 1 + i) / ffreq, ytm, pmt));

		this->add(CashFlow( Npmt / ffreq, ytm, pmt + NV));

		fset = true;
		return true;
	}

	return false;
}

template <typename T>
bool Bond::setBond(int Npmt, Rate Coupon, Value NV, YieldMaster<T> *a)
{
	if (!fset)
	{
		double pmt = Coupon * NV / ffreq;

		for (int i = 0 ; i < Npmt - 1 ; i ++)
		{
			n = ( 1 + i) / ffreq;
			this->add(FINFlow( n , a->r(n) + this->fspread, pmt));
		}

		n = Npmt / ffreq;
		this->add(FINFlow( n, a->r(n) + this->fspread, pmt + NV));

		fset = true;
		return true;
	}

	return false;
}

template <typename T>
void Bond::updateRate(YieldMaster<T> *a)
{
	for (int i = 0, n = this->size(); i < n ; i++)
	{
		this->operator [](i).setr(a, this->spread);
	}
}

double Bond::cleanPrice(double t, double v)
{
	// Add the missing period to find the price at the date of the next coupon
	double t2 = t + timeBeforePayment(t);

	return presentValue(t2, v);
}

double Bond::dirtyPrice(double t, double v)
{
	double coupon = this->operator [](1).pmt();

	// compute the elapsed period between past coupon and future coupon
	double part = timeElapsed(t);

	if (part == 0)
		return cleanPrice(t, v);

	return cleanPrice(t, v) + coupon * ( part / ffreq);
}

	/*
	void FINBond::setBond(int Nbpmt, double CRate, int freq, double FV, FINYieldMaster<> *a)
	{
		eraseAll();

		double rate = 0;
		double pmt = CRate * FV / freq;

		if ( a == 0)
		{
			for (int i = 1; i < Nbpmt; i++)
			{
				add(FINFlow(i / freq, rate, pmt));
			}

			add(FINFlow(Nbpmt / freq, rate, pmt + FV));
		}
		else
		{
			double n = 0;

			for (int i = 1; i < Nbpmt; i++)
			{
				n = i / freq;

				rate = (double) fspread + a->r(n);

				add(FINFlow(n, rate, pmt));
			}

			n = Nbpmt / freq;

			rate = a->r(n);

			add(FINFlow(n, rate, pmt + FV));
		}
	}

	void FINBond::setBond(int Nbpmt, double CRate, int freq, double FV, double ytm)
	{
		double pmt = CRate * FV / freq;

		eraseAll();

		for (int i = 1; i < Nbpmt; i++)
		{
			add(FINFlow(i / freq, ytm, pmt));
		}

		add(FINFlow(Nbpmt / freq, ytm, pmt + FV));

	}

	


/*	FINBondV::FINBondV(int Npmt, int freq, double FV, double spread):f_spread(spread)
	{
		ffreq = freq;
		double n = 0;

		// create missing Flow
		for ( int i = 0; i < Npmt; i++ )
		{
			n =  (double) ( i + 1) /freq;
			add(	FINFlow(n, 0, 0)	);
		}

		add(	FINFlow(n, 0, FV)	);

	}

	FINBondV::FINBondV(int Npmt, int freq, double FV, double spread, FINYieldMaster<> *a):f_spread(spread)
	{
		ffreq = freq;
		double PMT = 0;
		double n = 0;
		double Rc = 0;
		// create missing Flow
		for ( int i = 0; i < Npmt; i++ )
		{
			n = (double) ( i + 1)/freq;

			Rc = a->getForward( (double) i / freq, (double) (i + 1) / freq) + f_spread;

			PMT = ( exp (Rc/freq) - 1)	* FV;

			add(	FINFlow(n, (a->getYield(n) + f_spread), PMT)	);
		}

		add(	FINFlow(n, a->getYield(n), FV)	);

	}*/
}
