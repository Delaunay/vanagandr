#ifndef VANAGANDR_TEST_LINEARREG_HEADER
#define VANAGANDR_TEST_LINEARREG_HEADER

#include <gtest/gtest.h>

#include "../statistics/LinearRegression.h"

using namespace vanagandr::statistics;


Matrix X = Matrix::Zero(5, 4);
Matrix Y = Matrix::Zero(5, 1);
Matrix B = Matrix::Zero(4, 1);
Matrix Yb = Matrix::Zero(5, 1);
double rsqr;

TEST(LinearRegression, Initialization)
{
    X << 1,	0.635648444,	0.338662754,	0.31579336,
         1,	0.408316224,	0.08835369,	    0.745996554,
         1,	0.182192391,	0.966436277,	0.214539099,
         1,	0.341566296,	0.551990467,	0.767195742,
         1,	0.292347551,	0.222970648,	0.439478797;

    Y << 1.136414285,
         0.750522886,
         1.414950923,
         1.176693506,
         0.841587103;

    Yb << 1.133976471,
          0.776983989,
          1.427630092,
          1.159726817,
          0.821851335;

    B << 0.429752544,
         0.610184905,
         0.912300258,
         0.023429001;

    rsqr = 0.994653672;
}


TEST(LinearRegression, NormalEquation)
{
    Matrix Bt = LinearRegression<NormalEquation>::linear_regression(X, Y);
    Matrix Yt = X * Bt;
    double rt = rsquare(Yt, Y);

    // we got 9 numbers

    for (int i = 0; i < 4; i++)
        EXPECT_LT(Bt(i, 0) - B(i, 0), 1e-9);

    for (int i = 0; i < 5; i++)
        EXPECT_LT(Yt(i, 0) - Yb(i, 0), 1e-9);

    EXPECT_LT(rsqr- rt, 1e-9);

//    Matrix u = Y - Yt;
//    std::cout << estimator_variance(X, u) << std::endl;
//    Matrix u = Y - Yt;
//    Matrix s =  u.transpose() * u / u.rows();
//    std::cout << s << std::endl;
//    std::cout << u * u.transpose() / s(0, 0) << std::endl;
}

TEST(LinearRegression, JacobiSVD)
{
    Matrix Bt = LinearRegression<JacobiSVD>::linear_regression(X, Y);
    Matrix Yt = X * Bt;
    double rt = rsquare(Yt, Y);

    // we got 9 numbers

    for (int i = 0; i < 4; i++)
        EXPECT_LT(Bt(i, 0) - B(i, 0), 1e-9);

    for (int i = 0; i < 5; i++)
        EXPECT_LT(Yt(i, 0) - Yb(i, 0), 1e-9);

    EXPECT_LT(rsqr- rt, 1e-9);
}

#if CERES_SOLVER
TEST(LinearRegression, Iterative)
{
    Matrix Bt = LinearRegression<Iterative>::linear_regression(X, Y);
    Matrix Yt = X * Bt;
    double rt = rsquare(Yt, Y);

    // we got 9 numbers

    for (int i = 0; i < 4; i++)
        EXPECT_LT(Bt(i, 0) - B(i, 0), 1e-9);

    for (int i = 0; i < 5; i++)
        EXPECT_LT(Yt(i, 0) - Yb(i, 0), 1e-9);

    EXPECT_LT(rsqr- rt, 1e-9);
}
#endif

// Quick and dirty performance check
// always interesting

Matrix X2 = Matrix::Random(1000, 50);
Matrix Y2 = Matrix::Random(1000, 1);

TEST(LinearRegression, init_perf)
{
    X2.col(0) = Matrix::Ones(1000, 1);
}

// faster
TEST(LinearRegression, NormalEquation_perf)
{
    Matrix Bt = LinearRegression<NormalEquation>::linear_regression(X2, Y2);
}

// slower
TEST(LinearRegression, JacobiSVD_perf)
{
    Matrix Bt = LinearRegression<JacobiSVD>::linear_regression(X2, Y2);
}

Matrix ArY = Matrix::Zero(15, 1);
Matrix ArU = Matrix::Random(15, 2);

TEST(AR, init_ar)
{
    ArY << 1.02442739,
           0.704533995,
           0.602597564,
           0.4695702,
           0.428023161,
           0.375716492,
           0.298413347,
           0.278349434,
           0.275355042,
           0.27626409,
           0.306151471,
           0.340888208,
           0.284204849,
           0.334586509,
           0.334628776;
}

TEST(AR, NormalEquation)
{
    std::cout << ar_matrix(ArY, 3, ArU) << "\n\n";

    std::cout << LinearRegression<NormalEquation>::auto_regress(ArY, 3) << "\n\n";
    std::cout << LinearRegression<NormalEquation>::auto_regress(ArY, 3, ArU) << std::endl;
}

TEST(AR, JacobiSVD)
{
    std::cout << LinearRegression<JacobiSVD>::auto_regress(ArY, 3) << "\n\n";
    std::cout << LinearRegression<NormalEquation>::auto_regress(ArY, 3, ArU) << std::endl;
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
