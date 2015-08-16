#include "Child.h"


namespace vanagandr
{
	Child::Child(Periods n, Rate r):n_(n), r_(r)
	{

	}

	bool	Child::operator<(const Child &a) const
	{
		return n_ < a.n_;
	}

	Child	Child::operator[](int a)
	{
		return Child(this->n_, this->r_);
	}

	int		Child::size()
	{
		return 1;
	}
	void	Child::setn(Periods x)
	{
		n_ = x;
	}

	void	Child::print()
	{
		std::cout << n_ << "\t" << r_ ;
	}

	Eigen::Vector2d Child::exportColVector()
	{
		Eigen::Vector2d a;

		a(0, 0) = n_;
		a(1, 0) = r_;

		return a;
	}

	Eigen::RowVector2d Child::exportRowVector()
	{
		Eigen::RowVector2d a;

		a(0, 0) = n_;
		a(0, 1) = r_;

		return a;
	}

	double Child::discountFactor(double t, double v)
	{
		return pow(1.0 + (r_ - v),  - (n_ - t)  );
	}

	double Child::compoundFactor(double t, double v)
	{
		return pow(1.0 + (r_ - v),  (n_ - t)  );
	}

	Periods Child::n()
	{
		return n_;
	}
	Rate	Child::r()
	{
		return r_;
	}
	bool Child::isChild()
	{
		return true;
	}
	bool Child::isParent()
	{
		return false;
	}
	bool Child::isVector()
	{
		return false;
	}
	void Child::setr(Rate x)
	{
		r_ = x;
	}
	void Child::setr(Rate x, double r_e)
	{	r_ = r_e * log  ( 1 + x / r_e);
	}

	Rate	Child::r(VRate::Type a, double r_e)
	{
		switch (a)
		{
			case VRate::Compound:
				return ( exp(r_ / r_e) - 1 ) * r_e;
				break;
			case VRate::Continuous:
				return r_;
				break;
			case VRate::Effective:
				return ( exp(r_ ) - 1 );
				break;
			default:
				return r_;
				break;
		}
	}

	Periods Child::getLastDate()	{	return this->n_;	}
	Periods Child::getFirstDate()	{	return this->n_;	}

	Rate	Child::getLastRate()	{	return this->r_;	}
	Rate	Child::getFirstRate()	{	return this->r_;	}



/************************************************************
 *					Yield
 * **********************************************************/

	Yield::Yield(Periods n, Rate r):Child(n, r)
	{
	}

	Yield Yield::operator()(int a, int b)
	{
		return Yield(n_, r_);
	}

	Rate Yield::r(Periods a, Periods b)	{	return r_;	}


}
