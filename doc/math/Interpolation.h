#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

#include <Eigen/Dense>


typedef Eigen::MatrixXd Matrix;

namespace vanagandr
{
namespace interpolation
{
    class Interpolation
	{
		public:
			Interpolation():
			    {}

            void set_points(Matrix* a)  {   Points_ = &(*a)(0, 0);   }
            
		protected:

			const double* Points_;
	};

	

	class Linear : public Interpolation
	{
		public:
			Linear();

			Real	operator()	(Real x);

			Matrix	coefficient();

			static Real linear(Real x, Point<Real> p1, Point<Real> p2);
			static Real logLinear(Real x, Point<Real> p1, Point<Real> p2);

            template <class A, class B>
            static Real customLinear(Real x, Point<Real> p1, Point<Real> p2)
            {
                A one; B two;
                return two(((one(p1.y()) - one(p2.y()))/(p1.x() - p2.x()) * (x - p1.x()) + one(p1.y())));
            }

            template <class A, class B>
            static Real customLinear(Real x, Point<Real> p1, Point<Real> p2, A one, B two)
            {
                return two(((one(p1.y()) - one(p2.y()))/(p1.x() - p2.x()) * (x - p1.x()) + one(p1.y())));
            }
	};



	class Polynomial: public Interpolation
	{
		public:
			Polynomial();

			Real	operator()	(Real x);

			Column	coefficient();

            /*
			template<unsigned int d>
			PolynomialFunction<d, Real> exportFunction()
			{
				Column S = coefficient();
                ID const n = S.rows();
				PolynomialFunction<n , Real> r;

				for(ID i = 0; i < n; i++)
					r.setCoefficient(i, S(i));

				return r;
            }*/
	};

	class CubicSpline : public Interpolation
	{
		public:
			CubicSpline();

			Real	operator()	(Real x);

			Matrix	coefficient();

			Matrix	solution();
	};

	class Linear3D : public Interpolation
	{
		public:
			Linear3D();

			Real operator()	(Real x)
			{

			}
	};
}
}


#endif // LINEARINTERPOLATION_H
