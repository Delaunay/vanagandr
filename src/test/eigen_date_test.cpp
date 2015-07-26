#ifndef VANAGANDR_TEST_EIGENDATE_HEADER
#define VANAGANDR_TEST_EIGENDATE_HEADER

#include <gtest/gtest.h>
#include <iostream>

#include "../containers/Type.h"

using namespace vanagandr::type;

typedef Eigen::Matrix<Date<int>, Eigen::Dynamic, Eigen::Dynamic> MatDate;

TEST(Date, Datetype)
{
    Date<int> d1(31, 12, 2014);
    Date<int> d2(31, 12, 2015);

    std::cout << d1 << std::endl;

    MatDate m = MatDate::Zero(10, 1);

    for (int i = 0; i < 10; i++)
        m(i, 0) = Date<int>(i + 1, 05, 2014);

    std::cout << m << std::endl;

    EXPECT_EQ(d1 < d2, true);

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
