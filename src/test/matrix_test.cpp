#ifndef VANAGANDR_TEST_MATRIX_HEADER
#define VANAGANDR_TEST_MATRIX_HEADER

#include <gtest/gtest.h>

#include "../math/Matrix.h"


Matrix mf = Matrix::Zero(2, 2);


TEST(MatrixFunction, init)
{
    mf << 4, 25, exp(1), 1;
}

TEST(MatrixFunction, log)
{
    Matrix xl = vanagandr::math::mlog(mf);

    for(int i = 0; i < xl.cols(); i++)
        for(int j = 0; j < xl.rows(); j++)
            EXPECT_DOUBLE_EQ(xl(j, i), log(mf(j, i)));
}

TEST(MatrixFunction, sqr)
{
    Matrix xl = vanagandr::math::msqr(mf);

    for(int i = 0; i < xl.cols(); i++)
        for(int j = 0; j < xl.rows(); j++)
            EXPECT_DOUBLE_EQ(xl(j, i), pow(mf(j, i), 2.0));
}

TEST(MatrixFunction, sqrt)
{
    Matrix xl = vanagandr::math::msqrt(mf);

    for(int i = 0; i < xl.cols(); i++)
        for(int j = 0; j < xl.rows(); j++)
            EXPECT_DOUBLE_EQ(xl(j, i), sqrt(mf(j, i)));
}


TEST(MatrixFunction, mpow)
{
    Matrix ex = Matrix::Zero(2, 2);
    ex << 2, 0.5, 2, 2;

    Matrix xl = vanagandr::math::mpow(mf, ex);

    for(int i = 0; i < xl.cols(); i++)
        for(int j = 0; j < xl.rows(); j++)
            EXPECT_DOUBLE_EQ(xl(j, i), pow(mf(j, i), ex(j, i)));
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
