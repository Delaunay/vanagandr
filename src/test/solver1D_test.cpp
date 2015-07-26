#ifndef VANAGANDR_TEST_SOLVER1D_HEADER
#define VANAGANDR_TEST_SOLVER1D_HEADER

#include <gtest/gtest.h>

#include "../math/RootSolver1D.h"

using namespace vanagandr::math;


double f1(double x)
{
    return x * x;
}

double f2(double x)
{
    return x * x - 1.0;
}


TEST(RootSolver1D, Bissection)
{
    double tol = 1e-10;

    double s1 = RootSolver1D<Bissection>::solve(f1, -1, 1 , 1000, tol);
    double s2 = RootSolver1D<Bissection>::solve(f2,  0, 10, 1000, tol);

    EXPECT_LT(sqrt(pow(f1(s1), 2.0)), tol);
    EXPECT_LT(sqrt(pow(f2(s2), 2.0)), tol);
}


TEST(RootSolver1D, Secante)
{
    double tol = 1e-10;

    // guess near sol
    double s1 = RootSolver1D<Secante>::solve(f1, -2, 1 , 1000, tol);
    double s2 = RootSolver1D<Secante>::solve(f2,  0, 10, 1000, tol);

    // guess far away from sol
    double s3 = RootSolver1D<Secante>::solve(f2,  10, 20, 1000, tol);

    EXPECT_LT(sqrt(pow(f1(s1), 2.0)), tol);
    EXPECT_LT(sqrt(pow(f2(s2), 2.0)), tol);
    EXPECT_LT(sqrt(pow(f2(s3), 2.0)), tol);
}


#if __linux__

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}


#endif

#endif
