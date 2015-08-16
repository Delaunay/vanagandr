#include "../finance/CashFlow.h"


namespace vanagandr
{
	CashFlow::CashFlow(Periods n, Rate r, Value PMT, Value PV):
		Child(n, r), Pmt_(PMT)
	{

	}

	double CashFlow::pvContinuous(Periods T, Rate R, Price pmt)				{	return pmt / exp( T * R);				}
	double CashFlow::pvEffective (Periods T, Rate R, Price pmt)				{	return pmt / pow( ( 1.0 + R), T);		}
	double CashFlow::pvSimple	 (Periods T, Rate R, Price pmt)				{	return pmt / ( 1.0 + R * T);			}
	double CashFlow::pvCompound	 (Periods T, Rate R, Price pmt, Periods m)	{	return pmt / pow( ( 1.0 + R/m), T*m);	}

	double CashFlow::fvContinuous(Periods T, Rate R, Price pmt)				{	return pmt * exp( T * R);				}
	double CashFlow::fvEffective (Periods T, Rate R, Price pmt)				{	return pmt * pow( ( 1 + R), T);			}
	double CashFlow::fvSimple	 (Periods T, Rate R, Price pmt)				{	return pmt * ( 1 + R * T);				}
	double CashFlow::fvCompound	 (Periods T, Rate R, Price pmt, Periods m)	{	return pmt * pow( ( 1 + R/m), T*m);		}

	Value CashFlow::presentValue(Periods t, Rate v) {	if (t < n_)	return pvEffective( n_ - t, r_ + v, Pmt_);	return 0.0;	}
	Value CashFlow::futureValue	(Periods t, Rate v) {	if (t > n_)	return pvEffective( n_ - t, r_ + v, Pmt_);	return 0.0;	}
	Value CashFlow::totalValue	(Periods t, Rate v) {				return pvEffective( n_ - t, r_ + v, Pmt_);				}
	Value CashFlow::scratchPV	(Periods t, Rate r)	{	if (t < n_) return pvEffective( n_ - t, r     , Pmt_);	return 0.0;	}

	double CashFlow::dr			(Periods t, Rate v)	{	return -(n_ - t) * presentValue(t, v)/(1 + r_ +v); }
	double CashFlow::ddr		(Periods t, Rate v)	{	double n = (n_ - t);	return (n *n + n) * presentValue(t, v)/pow( (1 + r_ + v), 2); }
	double CashFlow::dt			(Periods t, Rate v)	{	return - log( 1 + r_ + v) * presentValue(t, v);	}
	double CashFlow::ddt		(Periods t, Rate v) {	return pow( log( 1 + r_ + v), 2) * presentValue(t, v);	}
	double CashFlow::dpmt		(Periods t, Rate v)	{	return pow( 1 + r_ + v, n_ - t);	}
	double CashFlow::ddpmt		(Periods t, Rate v) {	return 0;	}

	double CashFlow::macaulay	(Periods t, Rate v)	{ return ( n_ - t );					}
	double CashFlow::duration	(Periods t, Rate v) { return ( n_ - t )/( 1 + r_ + v);		}
	double CashFlow::convexity	(Periods t, Rate v) { double n = n_ - t;	return ( n * n + n )/pow( (1+ r_ + v), 2);		}

	/*Value	CashFlow::cptPMT(Periods t, Rate v)	{	return fvEffective(n_ - t, r_ + v, fpv);	}
	Rate	CashFlow::cptr  (Periods t)			{	return log( Pmt_/fpv ) / (this->n_ - t);	}
	Periods CashFlow::cptn  (Rate v)			{	return log( Pmt_/fpv ) / (double) (this->r_ + v);	}*/

    double CashFlow::discountFactor(Periods t, Rate v) {	if (t < n_)	return pvEffective( n_ - t, r_ + v, Pmt_);	return 0.0;	}
    double CashFlow::compoundFactor(Periods t, Rate v) {	if (t > n_)	return pvEffective( n_ - t, r_ + v, Pmt_);	return 0.0;	}

	double CashFlow::print(Periods t, Rate v)
	{
		double buf = presentValue(t, v);

		std::cout << this->n_ << "\t" <<this->r_ << "\t" << Pmt_ << "\t" << buf;

		return buf;
	}

//	Value	CashFlow::pv()			{	return fpv;		}
	Value	CashFlow::pmt()			{	return Pmt_;	}

	//void CashFlow::setpv (Value a)	{	fpv  = a;		}
	void CashFlow::setpmt(Value a)	{	Pmt_ = a;		}

	/*****************************__ Uo __ *****************************************/

	double CashFlow::cptReinvestmentEarning(Periods t, Rate v)	{	return futureValue(t, v) -cptPaymentMade(t);	}
	double CashFlow::cptCapitalEarning(Periods t, Rate v)		{	return 0;										}
	double CashFlow::cptPaymentMade	 (Periods t, Rate v)		{	if (t > n_) return Pmt_;	return 0.0;			}

	double CashFlow::ytmGeo			  (Periods t, Rate v)		{	return (double) (v + r_) + 1;					}
	double CashFlow::ytmAri			  (Periods t, Rate v)		{	return r_ + v;									}
	double CashFlow::ytmHar			  (Periods t, Rate v)		{	return r_ + v;									}
	double CashFlow::cptExpectedReturn(Periods t, Rate v)		{	return log( totalValue(t, v)/presentValue(t, v) );	}
	//double CashFlow::cptCurrentReturn (Periods t, Rate v)		{	return log(	(futureValue(t, v) / fpv));			}
	double CashFlow::getLastPayment	  ()						{	return Pmt_;									}
	double CashFlow::getFirstPayment  ()						{	return Pmt_;									}

	Rate CashFlow::yieldtoMaturity	 (Periods t, Rate v)		{	return this->r_ + v;	}
}
