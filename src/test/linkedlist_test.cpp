#ifndef VANAGANDR_TEST_LINKEDLIST_HEADER
#define VANAGANDR_TEST_LINKEDLIST_HEADER

#include <gtest/gtest.h>

#include "../containers/LinkedList.h"

#include <iostream>

using namespace vanagandr::containers;
LinkedList<int> a;

TEST(LinkedList, Append)
{
    EXPECT_EQ(a.is_empty(), true);

    for(int i = 0; i < 50; i++)
        a.push_first(i);

    for(int i = 0; i < 50; i++)
        a.push_last(i);

    std::cout << a.str() << std::endl;
    EXPECT_EQ(a.is_empty(), false);

    EXPECT_EQ(a.first(), 49);
    EXPECT_EQ(a.last() , 49);
}

TEST(LinkedList, Remove)
{
    a.remove_first();
    a.remove_last();

    EXPECT_EQ(a.first(), 48);
    EXPECT_EQ(a.last() , 48);

    std::cout << a.str() << std::endl;
}

TEST(LinkedList, stlcomp)
{
    LinkedList<int> b;
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
