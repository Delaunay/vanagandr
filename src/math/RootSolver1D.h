#ifndef VANAGANDR_MATH_SOLVER1D_HEADER
#define VANAGANDR_MATH_SOLVER1D_HEADER

#include <cmath>
#include "../enum.h"

namespace vanagandr {
namespace math{

enum RootSolver1DMethod
{
    Secante,
    Bissection,
    Custom
};


/*!
 * Secante: do a linear approximation and solve for f(x) = 0
 * you need to provide a first 'guess' nevertheless does not have to include a sol
 *
 * f(x) ~ g(x) = ax + b
 *
 * a = (f(x_1) - f(x_2))/(x_1 - x_2)
 * b = x1 * a - f(x_1)
 *
 * g(x) = a * x + f(x_1) - a * x_1 = a * (x - x_1) + f(x_1)
 *
 * now solve for g(x) = 0
 *
 * a * (x - x_1) + f(x_1) = 0
 * x = x_1 - f(x_1) / a
 *
 * Which gives us the update rule:
 * x = x_1 - f(x_1) * (x_1 - x_2)/(f(x_1) - f(x_2))
 *
 * we update the oldest value (x_1, x_2)
 */
template<RootSolver1DMethod m = Secante>
struct RootSolver1D
{
public:

    template<typename function>
    static double solve(function f, double a, double b, int max_ite = 1000, double tol = 1e-10)
    {
        double c, fa, fc;
        int i;

        for(i = 0; i < max_ite; i++)
        {
            fa = f(a);
            c = a - (a - b) * fa / (fa - f(b));
            fc = f(c);

            if (i % 2 == 0)
                a = c;
            else
                b = c;

            if (sqrt(fc * fc) < tol)
                return c;
        }

        // you can return something else if sol not found
        return c;
    }
};


// f(x) = 0
template<>
struct RootSolver1D<Bissection>
{
public:

    template<typename function>
    static double solve(function f, double a, double b, int max_ite = 1000, double tol = 1e-10)
    {
        int i;
        double c, fr;

        for(i = 0; i < max_ite; i++)
        {
            c = (a + b)/2.0;

            fr = f(c);

            if (fr * f(a) < 0.0)
                b = c;
            else
                a = c;

            if (sqrt(fr * fr) < tol)
                return c;
        }

        // you can return something else if sol not found
        return c;
    }
};

/*!
 * do a quadratic approximation and solve for f(x) = 0
 *
 * f(x) ~ g(x) = ax² + bx + c
 *
 * | x_0² x_0 1 |   | a |   | f(x_0) |
 * | x_1² x_1 1 | x | b | = | f(x_1) |
 * | x_2² x_2 1 |   | c |   | f(x_2) |
 *
 * there are to possible solution !!!
 *
 * \Delta = b² - 4 ac
 *
 * s_1 = (b - \sqrt{\Delta}) / 2 a
 * s_2 = (b + \sqrt{\Delta}) / 2 a
 *
 * so what two do now ??
 *
 */

//// f(x) = 0
//template<>
//struct Solver1D<Custom>
//{
//public:
//    typedef Eigen::Matrix3d X;
//    typedef Eigen::Vector3d Y;


//    template<typename function>
//    static double solve(function f, double a, double b, int max_ite = 1000, double tol = 1e-10)
//    {
//        int i;
//        double x1, x2, d;
//        X x;
//        Y y;
//        Y v;

//        x.fill(1.0);

//        for(i = 0; i < max_ite; i++)
//        {
//            x(0, 1) = a;             x(0, 0) = a * a;               y(0) = f(a);
//            x(1, 1) = (a + b)/2.0;   x(1, 0) = a(1, 1) * a(1, 1);   y(1) = f(x(1, 1));
//            x(2, 1) = b;             x(2, 0) = b * b;               y(2) = f(b);

//            v = x.lu().solve(y);

//            d = v(1) * v(1) - 4.0 * v(0) * v(2);

//            x1 = (v(1) + sqrt(d)) / (2.0 * v(0));
//            x2 = (v(1) - sqrt(d)) / (2.0 * v(0));

//        }

//        return c;
//    }
//};


}
}
#endif
