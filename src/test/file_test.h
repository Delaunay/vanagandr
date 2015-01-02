#ifndef VANAGANDR_TEST_FILE_HEADER
#define VANAGANDR_TEST_FILE_HEADER

#include <gtest/gtest.h>

#include "../file/MatrixIO.h"


using namespace vanagandr::file;

TEST(write_open, Matrix)
{
    Matrix rand_mat = Matrix::Random(10, 2);

    write("test.csv", rand_mat);

    Matrix rd = read("test.csv");

    // the precision saved is 12 decimals, the difference should be below
    for(int j = 0; j < 2; j++)
        for(int i = 0; i < 10; i++)
            EXPECT_LT(rd(i, j) - rand_mat(i, j), 1e-12);
}


#endif
