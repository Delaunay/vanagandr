#ifndef VANAGANDR_MATH_SOLVER1D_HEADER
#define VANAGANDR_MATH_SOLVER1D_HEADER

#include <cmath>
#include "../enum.h"

//namespace vanagandr {
//namespace math{

//enum MinSolver1DMethod
//{
//    NewtonRaphson,
//};


///*!
// *
// */
//template<MinSolver1DMethod m = NewtonRaphson>
//struct MinSolver1D
//{
//public:

//    template<typename function>
//    static double solve(function f, double a, double b, int max_ite = 1000, double tol = 1e-10)
//    {
//        double c, fa, fc;
//        int i;

//        for(i = 0; i < max_ite; i++)
//        {
//            fa = f(a);
//            c = a - (a - b) * fa / (fa - f(b));
//            fc = f(c);

//            if (i % 2 == 0)
//                a = c;
//            else
//                b = c;

//            if (sqrt(fc * fc) < tol)
//                return c;
//        }

//        // you can return something else if sol not found
//        return c;
//    }
//};




///*!
// * do a quadratic approximation and solve for min f(x)
// * try to return a global maximum but nothing is sure
// *
// * f(x) ~ g(x) = ax² + bx + c
// *
// * | x_0² x_0 1 |   | a |   | f(x_0) |
// * | x_1² x_1 1 | x | b | = | f(x_1) |
// * | x_2² x_2 1 |   | c |   | f(x_2) |
// *
// * we can derivate g(x) => g'(x) = 2ax + b
// *
// * sol = -b  / (2a)
// * if the problem is concave two new branches are created
// *
// * like the secant we update the oldest value
// *
// * NOT TESTED NOT EVEN COMPILED NOT EVEN ONCE
// */
//struct MinSolver1D
//{
//public:
//    typedef Eigen::Matrix3d X;
//    typedef Eigen::Vector3d Y;


//    template<typename function>
//    static double solve(function f, double a, double b, int max_ite = 1000, double tol = 1e-10)
//    {
//        int i;
//        double o1, o2;

//        X x;    x.fill(1.0);
//        Y y;
//        Y v;

//        for(i = 0; i < max_ite; i++)
//        {
//            x(0, 1) = a;             x(0, 0) = a * a;               y(0) = f(a);
//            x(1, 1) = (a + b)/2.0;   x(1, 0) = a(1, 1) * a(1, 1);   y(1) = f(x(1, 1));
//            x(2, 1) = b;             x(2, 0) = b * b;               y(2) = f(b);

//            v = x.lu().solve(y);

//            if (v(0) < 0)
//                // then the approximation is concave No minimum on that location
//                // 2 possibles Minimum
//                // branch here -> recu
//            {
//                // start two new branch
//                double s1 = MinSolver1D::solve(f, a - 1.0, a, max_ite, tol), // left
//                       s2 = MinSolver1D::solve(f, b, b + 1.0, max_ite, tol); // right

//                // break this loop
//                if (f(s1) > f(s2))
//                    return s2;
//                else
//                    return s1;
//            }

//            if (i % 2 == 0)
//            {
//                o1 = f(a);
//                a = - v(1) /(2.0 * v(0));
//                o2 = f(a);

//                if (sqrt(pow(o2 - o1, 2.0)) < tol)
//                    return a;
//            }
//            else
//            {
//                o1 = f(b);
//                b = - v(1) /(2.0 * v(0));
//                o2 = f(b);

//                if (sqrt(pow(o2 - o1, 2.0)) < tol)
//                    return b;
//            }
//        }

//        return c;
//    }
//};


//}
//}
#endif
