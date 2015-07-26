#ifndef VANAGANDR_MATH_INTEGRATION_HEADER
#define VANAGANDR_MATH_INTEGRATION_HEADER

#include <cmath>
#define PI 3.14159265358979

// TODO simplify composed rules
// less f call can be achieved

namespace vanagandr
{
namespace math
{
    namespace internal
    {
        // GaussChebyshev weight and node
        double t1(int i, int n) {   return cos((2.0 * i - 1.0) * PI / (2.0 * n)); }
        double w1(int n)        {   return PI / double(n);  }

        double t2(int i, int n) { return cos(i * PI / (n + 1.0)); }
        double w2(int i, int n) { return sin(i * PI / pow((n + 1.0), 2.0)) * PI / (n + 1.0); }
    }
    
    enum IntegrationMethod
    {
        Rectangle,
        Trapezoidal,
        Simpson,
        GaussLegendre,
        GaussChebyshev1,
        GaussChebyshev2,
    };

    /*!
     *  Integrate, provide the static function 'integrate' different specialized version can be
     *  called (from slower to faster)
     *
     * - Integrate<Simpson>    ::integrate : integrate the function using a polynomial of degree 2
     * - Integrate<Trapezoidal>::integrate : integrate the function using a polynomial of degree 1
     * - Integrate<Rectangle>  ::integrate : integrate the function using a polynomial of degree 0
     *
     * - Integrate<GaussLegendre>::integrate : integrate the function using GaussLegendre (3 points)
     *              [Really good for polynomial the approximation can be exact]
     *
     * - Integrate<GaussChebyshev1>::integrate  | I don't think the function will be of any use.
     *              [ weights are computed in real time]
     */
    template<IntegrationMethod method = Simpson>
    struct Integrate
    {
    public:
        
        template<typename function>
        static double integrate(function f, double a, double b, int n)
        {
            double step = (b - a)/double(n);
            double inte = 0.0;

            for(int i = 0; i < n; i++)
                inte = inte + simpson(f, a + double(i) * step, a + (i + 1.0) * step);

            return inte;
        }

        // simple simpson rule
        template<typename function>
        static double simpson(function f, double a, double b)
        {
            return (b - a) * (f(a) + 4.0 * f((a + b)/2.0)+ f(b))/6.0;
        }

        // simple rectangle rule
        template<typename function>
        static double rectangle(function f, double a, double b)
        {
            return (b - a) * f((a + b)/2);
        }

        // simple trapezoidal rule
        template<typename function>
        static double trapezoidal(function f, double a, double b)
        {
            return (b - a) * (f(a) + 4.0 * f((a + b)/2.0)+ f(b))/6.0;
        }

    };

    // GaussLegendre with 3 Nodes
    // perfect approximation for polynomials
    
    template<>
    struct Integrate<GaussLegendre>
    {
    public:

        template<typename function>
        static double integrate(function f, double a, double b, int n)
        {
            return (f(- (b - a) * sqrt(3.0/5.0)/2.0 + (b + a)/2.0) * 5.0 +
                    f(                                (b + a)/2.0) * 8.0 +
                    f(+ (b - a) * sqrt(3.0/5.0)/2.0 + (b + a)/2.0) * 5.0) * (b - a) / 18.0;
        }
    };

    template<>
    struct Integrate<Trapezoidal>
    {
    public:

        template<typename function>
        static double integrate(function f, double a, double b, int n)
        {
            double step = (b - a)/double(n);
            double inte = 0.0;

            for(int i = 0; i < n; i++)
                inte = inte + Integrate<>::trapezoidal(f, a + double(i) * step, a + (i + 1.0) * step);

            return inte;
        }
    };

    template<>
    struct Integrate<Rectangle>
    {
    public:

        template<typename function>
        static double integrate(function f, double a, double b, int n)
        {
            double step = (b - a)/double(n);
            double inte = 0.0;

            for(int i = 0; i < n; i++)
                inte = inte + Integrate<>::rectangle(f, a + double(i) * step, a + (i + 1.0) * step);

            return inte;
        }
    };

    template<>
    struct Integrate<GaussChebyshev1>
    {
    public:

        template<typename function>
        static double integrate(function f, double a, double b, int n)
        {
            double ret = 0;

            for(int i = 1; i < n + 1; i++)

                ret = ret + f((b - a) * internal::t1(i, n)/2.0 + (b + a)/2.0)
                * sqrt(1.0 - pow(internal::t1(i, n), 2.0));

            // PI / double(n)
            return (b - a) * ret * PI / (2.0 * double(n));
        }
    };

//    template<>
//    struct Integrate<GaussChebyshev2>
//    {
//    public:

//        template<typename function>
//        static double integrate(function f, double a, double b, int n)
//        {
//            double ret = 0;

//            for(int i = 1; i < n + 1; i++)

//                ret = ret + f((b - a) * internal::t2(i, n)/2.0 + (b + a)/2.0) * internal::w2(i, n) / sqrt(1.0 - pow(internal::t2(i, n), 2.0));

//            return (b - a) * ret / 2.0;
//        }
//    };
}
}
#endif
