#include "../finance/Mark.h"

namespace vanagandr
{
	
	double Margin::margin( double st, double d, Position a)
	{
		if (a == Long)
			return ( st * f_contractsize * f_numberowned - f_debt * exp( f_rate * d / 365) ) /  ( st  * f_contractsize * f_numberowned) ;
		else
            return ( - st  * f_contractsize * f_numberowned + f_debt * exp( f_rate * d / 365) ) /  ( f_debt * exp( f_rate * d / 365) ) ;
	}
	
	double Margin::margincall_price(double d, Position a )
	{
		if (a == Long)
			return ( f_debt * exp( f_rate * d / 365) )  / ( ( 1 - f_maintenancemargin) * f_contractsize * f_numberowned);
		else
			return ( f_debt * exp( f_rate * d / 365) )  / ( ( 1 + f_maintenancemargin) * f_contractsize * f_numberowned)  ;
	}
	

	double Mark::addDay ( double st, double rf, double d)
	{
		// add the interest due or earned for the period
        f_margin = f_margin * exp(rf * d / 365) + (st - f_so) * f_contractsize * f_numberowned;
        f_so = st;

		// if the margin is not enough add the missing part
		if (f_margin < f_maintenancemargin)
		{
            double buf = f_initialmargin - f_margin;
			f_added = f_added + buf;
			f_margin = f_margin + buf;
		}
		
	return f_margin;
	}

	double Mark::withdraw ( double amount)
    {
		// if the margin is higher than the maximal requirement do the transaction
		if ((f_margin > f_initialmargin) && (amount > 0))
		{
            f_withdraw = f_withdraw + amount;
            f_margin = f_margin - amount;
		}
		
	return f_margin;
	}

	double Mark::profit()
	{
		// Profit = current margin minus initial margin minus added margin plus deleted margin (withdraw)
        return f_margin - f_initialmargin - f_added + f_withdraw;
	}

	double Mark::marginCallPrice()
	{
        return ( f_maintenancemargin - f_margin ) / ( f_contractsize * f_numberowned ) + f_K;
	}
}
