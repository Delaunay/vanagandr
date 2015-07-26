#ifndef VANAGANDR_TEST_LINKEDLIST_HEADER
#define VANAGANDR_TEST_LINKEDLIST_HEADER

#include <gtest/gtest.h>

#include "../containers/SimpleArray.h"

#include <iostream>

using namespace vanagandr::containers;
SimpleArray<double> a;

TEST(SimpleArray, Append)
{
    EXPECT_EQ(a.is_empty(), true);

    for(int i = 0; i < 100; i++)
    {
        a.push_back(i);
        EXPECT_DOUBLE_EQ(i, a[i]);
    }

    EXPECT_EQ(a.last(), 99);
    EXPECT_EQ(a.is_empty(), false);

    std::cout << a.str() << "\n\n";

    EXPECT_EQ(a.size(), 100);
    EXPECT_EQ(a.capacity(), 128);

    for(int i = 0; i < 100; i++)
        a.remove_last();

    EXPECT_EQ(a.size(), 0);

    std::cout << a.str() << std::endl;
}

TEST(SimpleArray, stlcomp)
{
    SimpleArray<int> b;
    std::vector<int> c;

    for(int i = 0; i < 100; ++i)
        c.push_back(i);

    std::copy(c.begin(), c.end(), std::back_inserter(b));

    std::cout << b.str() << std::endl;
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
