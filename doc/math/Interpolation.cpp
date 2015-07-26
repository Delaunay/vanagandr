#include "../math/Interpolation.h"

namespace vanagandr
{
namespace interpolation
{
/***********************************************************************
 ***********************************************************************
 ***********************************************************************/
	Interpolation::Interpolation()
	{}

	void Interpolation::addPoint( Point<Real> x )
	{
		Point_.push_back(x);	std::sort(Point_.begin(), Point_.end());
	}
	void Interpolation::addPoint( Real x, Real y)
	{
		Point_.push_back(Point<Real>(x, y));
		std::sort(Point_.begin(), Point_.end());
	}
	ID Interpolation::seekIndex(Real x)
	{
		ID index = 0;
		for(int i = 0, n = Point_.size(); i < n; i++)
		{
			if(Point_[i].x() > x)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	Real Interpolation::y(ID i)
	{
		if(i < Point_.size())
			return Point_[i].y();

		return 0;
	}
	Real Interpolation::x(ID i)
	{
		if(i < Point_.size())
			return Point_[i].x();

		return 0;
	}
	Real Interpolation::h(ID i)
	{
        if (i < Point_.size())
			return Point_[i + 1].x() - Point_[i].x();

		return 0;
	}
	Point<Real> Interpolation::point(ID i)
	{
		if(i < Point_.size())
			return Point_[i];

		return Point<Real>(0, 0);
	}
/***********************************************************************
 ***********************************************************************
 ***********************************************************************/
	Linear::Linear()
	{}

	Real	Linear::operator()	(Real x)
	{
		ID i = seekIndex(x);
		return linear(x, Point_[i - 1], Point_[i]);
	}

	Matrix	Linear::coefficient()
	{
		int n = Point_.size() - 1;
		Matrix Solution(n, 2);

		for(int i = 0; i < n; i++)
		{
			Real slope = (Point_[i].y() - Point_[i + 1].y())/(Point_[i].x() - Point_[i + 1].x());
			Solution(i, 0) = slope;
			Solution(i, 1) = Point_[i].y() - Point_[i].x()*slope;
		}

		return Solution;
	}

	Real Linear::linear(Real x, Point<Real> p1, Point<Real> p2)
	{
		return (p1.y() - p2.y())/(p1.x() - p2.x()) * (x - p1.x()) + p1.y();
	}
	Real Linear::logLinear(Real x, Point<Real> p1, Point<Real> p2)
	{
		return exp(log(p1.y()/p2.y())/(p1.x() - p2.x()) * (x - p1.x()) + log(p1.y()));
	}
	Real Linear::expLinear(Real x, Point<Real> p1, Point<Real> p2)
	{
		return log((exp(p1.y()) - exp(p2.y()))/(p1.x() - p2.x()) * (x - p1.x()) + exp(p1.y()));
	}

/***********************************************************************
 ***********************************************************************
 ***********************************************************************/
	Polynomial::Polynomial()
	{}

	Real	Polynomial::operator()	(Real x)
	{
		Column S = coefficient();
		Real fx = 0;

		for(int i = 0, n = Point_.size(); i < n ; i++)
			fx = fx + S(i) * pow(x, i);

		return fx;
	}

	Column	Polynomial::coefficient()
	{
		ID n = Point_.size();
		Matrix A(n, n);
		Column B(n);

		for(ID i = 0; i < n; i++)
		{
			Point<Real> p = point(i);

			for(ID j = 1; j < n; j++)
			{
				A(i, j) = pow( p.x(), double(j) );
			}

			A(i, 0) = 1;
			B(i)	= p.y();
		}

		return A.inverse() * B;
	}

/***********************************************************************
 ***********************************************************************
 ***********************************************************************/
	CubicSpline::CubicSpline(){}

	Real	CubicSpline::operator()	(Real x)
	{
		int n = Point_.size();
		int s = n - 1;

		for ( int i = 0; i < n; i++)
		{
			if (Point_[i].x() > x)
			{
				s = i;
				break;
			}
		}

		Column S = solution();

		Real x1 = Point_[s - 1].x();
		Real x2 = Point_[s].x();

		Real fx1 = Point_[s - 1].y();
		Real fx2 = Point_[s].y();

		Real fp = (fx2 - fx1) / (x2 - x1) - (1.0/3.0)*h(s - 1) * S(s - 1) - (1.0/6.0) * h(s - 1) * S(s) ;

		Real fpp = S( s - 1);
		Real fppp = (S(s) - S(s-1))/h(s -1);

		return fx1 + fp * (x - x1) + fpp * pow( (x - x1), 2) / 2.0 + fppp * pow( (x - x1), 3) /6.0;
	}

	Matrix	CubicSpline::coefficient()
	{
		Column S = solution();

		int n = Point_.size();
		Matrix R(n - 1, 4);

		for(int i = 1; i < n ; i++)
		{
			Real x1 = Point_[i - 1].x();
			Real x2 = Point_[i].x();

			Real fx1 = Point_[i - 1].y();
			Real fx2 = Point_[i].y();

			Real fp = (fx2 - fx1) / (x2 - x1) - (1.0/3.0)*h(i - 1) * S(i - 1) - (1.0/6.0) * h(i - 1) * S(i) ;

			Real fpp = S( i - 1);
			Real fppp = (S(i) - S(i-1))/h(i -1);

			R(i - 1, 0) = fx1;
			R(i - 1, 1) = fp;
			R(i - 1, 2) = fpp/2.0;
			R(i - 1, 3) = fppp/6.0;
		}

		return R;
	}

	Matrix	CubicSpline::solution()
	{
		int n = Point_.size();

		Matrix A = Matrix::Zero(n , n);

		Column B(n);

		int N = n - 1;

		B(0)	= 0;
		B(N)	= 0;

		A(0, 0) = 1;
		A(N, N) = 1;

		Real x1 = 0;
		Real x2 = 0;
		Real x3 = 0;

		Real fx1 = 0;
		Real fx2 = 0;
		Real fx3 = 0;

		for ( int i = 1; i < N; i++)
		{
			x1 = x(i - 1);
			x2 = x(i   );
			x3 = x(i + 1);

			fx1 = y(i - 1);
			fx2 = y(i	 );
			fx3 = y(i + 1);

			B(i) = 6 * ( (fx3 - fx2) / ( x3 - x2) - (fx2 - fx1) / (x2 - x1) ) ;

			A(i, i - 1 ) = ( x2 - x1 );
			A(i, i	   ) = 2 * ( x3 - x1);
			A(i, i + 1 ) = ( x3 - x2 );
		}

		return A.inverse() * B;
	}


}}
