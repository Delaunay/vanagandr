#ifndef VANAGANDR_TEST_LOGISTICREG_HEADER
#define VANAGANDR_TEST_LOGISTICREG_HEADER

#include <gtest/gtest.h>

#include "../statistics/LogisticRegression.h"
#include "../file/MatrixIO.h"

using namespace vanagandr::statistics;

Matrix X;
Matrix Y;
Matrix B;
Matrix theta;
Matrix tb;
double rsqr;

TEST(LogisticRegression, Initialization)
{
    X = vanagandr::file::read("../data/x2.csv");
    Y = vanagandr::file::read("../data/y2.csv");
    tb = vanagandr::file::read("../data/theta.csv");
    theta = Matrix::Zero(3, 1);
}

TEST(LogisticRegression, CostFunction)
{
    EXPECT_DOUBLE_EQ(LogisticRegression::cost(theta, X, Y), 0.69314718055994584);
    EXPECT_DOUBLE_EQ(LogisticRegression::cost(tb   , X, Y), 0.20349770242969231);
}

TEST(LogisticRegression, Gradient)
{
    Matrix gd1 = Matrix::Zero(3, 1);
    Matrix gd2 = Matrix::Zero(3, 1);

    gd1 << -0.10,
           -12.009216589299999,
           -11.2628422055;

    gd2 << -2.8700826063236615e-06,
           -0.0003469811774408353,
           -4.0348886511015761e-05;

    Matrix grad1 = LogisticRegression::gradient(theta, X, Y);
    Matrix grad2 = LogisticRegression::gradient(tb   , X, Y);

    for (int i = 0; i < 3; i++)
        EXPECT_DOUBLE_EQ(grad1(i, 0), gd1(i, 0));

    for (int i = 0; i < 3; i++)
        EXPECT_DOUBLE_EQ(grad2(i, 0), gd2(i, 0));

    //std::cout << grad2 << std::endl;
}

TEST(LogisticRegression, GradientDescent)
{
    Matrix t = LogisticRegression::gradient_descent(theta, X, Y, 0.1, 100000);

     std::cout << t<< std::endl;
     std::cout << LogisticRegression::cost(t, X, Y) << std::endl;
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
