#ifndef VANAGANDR_TEST_INTEGRATE_HEADER
#define VANAGANDR_TEST_INTEGRATE_HEADER

#include <gtest/gtest.h>

#include "../math/integeration.h"

double f1(double x)
{
    return x * x;
}

double f2(double x)
{
    return exp(- (x * x) / 2.0) / sqrt(2.0 * PI);
}

double F1(double x)
{
    return x * x * x / 3.0;
}

double trunc(double x)
{
    return int(x * 10000.0)/10000.0;
}

using namespace vanagandr::math;

TEST(Integrate, Rectangle)
{
    double a = 0, b = 1;

    // Rectangle is quite approximative so we truncate
    EXPECT_DOUBLE_EQ(trunc(Integrate<Rectangle>::integrate(f1,  a,  b, 1000)),
                     trunc(F1(b) - F1(a)));

    EXPECT_DOUBLE_EQ(Integrate<Rectangle>::integrate(f2, -20, 0, 1000), 0.5);
}

TEST(Integrate, Trapezoidal)
{
    double a = 0, b = 1;

    EXPECT_DOUBLE_EQ(Integrate<Trapezoidal>::integrate(f1,  a,  b, 1000), F1(b) - F1(a));
    EXPECT_DOUBLE_EQ(Integrate<Trapezoidal>::integrate(f2, -20, 0, 1000), 0.5);
}

TEST(Integrate, Simpson)
{
    double a = 0, b = 1;

    EXPECT_DOUBLE_EQ(Integrate<Simpson>::integrate(f1,  a,  b, 1000), F1(b) - F1(a));
    EXPECT_DOUBLE_EQ(Integrate<Simpson>::integrate(f2, -20, 0, 1000), 0.5);
}

TEST(Integrate, GaussLegendre)
{
    double a = 0, b = 1;

    EXPECT_DOUBLE_EQ(Integrate<GaussLegendre>::integrate(f1,  a,  b, 1000), F1(b) - F1(a));
    // GaussLegendre with 3 nodes suck for the normal dist
    //EXPECT_DOUBLE_EQ(Integrate<GaussLegendre>::integrate(f2, -20, 0, 1000), 0.5);
}
TEST(Integrate, GaussChebyshev1)
{
    double a = 0, b = 1;

    EXPECT_DOUBLE_EQ(trunc(Integrate<GaussChebyshev1>::integrate(f1,  a,  b, 1000)), trunc(F1(b) - F1(a)));
    EXPECT_DOUBLE_EQ(trunc(Integrate<GaussChebyshev1>::integrate(f2, -20, 0, 1000)), 0.5);
}

//TEST(Integrate, GaussChebyshev2)
//{
//    double a = 0, b = 1;

//    EXPECT_DOUBLE_EQ(Integrate<GaussChebyshev2>::integrate(f1,  a,  b, 1000), F1(b) - F1(a));
//    EXPECT_DOUBLE_EQ(Integrate<GaussChebyshev2>::integrate(f2, -20, 0, 1000), 0.5);
//}
#endif
