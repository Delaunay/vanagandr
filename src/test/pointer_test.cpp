#include <gtest/gtest.h>

#include "../memory/Ptr.h"
#include <iostream>

using namespace vanagandr::memory;
using namespace std;

struct test
{
    int a;
    int b;
};


TEST(Pointer, base)
{
    int *a = new int(10),
        *b = new int(20);

    Pointer<int> pa(a), pb(b);

    EXPECT_EQ(*a, *pa);
    EXPECT_EQ(*b, *pb);

    test* s = new test();
    s->a = 10;
    s->b = 20;

    Pointer<test> ptr = s;

    EXPECT_EQ(ptr->a, 10);
    EXPECT_EQ(ptr->b, 20);

    EXPECT_EQ((*ptr).a, 10);
    EXPECT_EQ((*ptr).b, 20);
}

TEST(Pointer, ref_management)
{
    test* s = new test();
    s->a = 10;
    s->b = 20;

    Pointer<test> ptr = s;
    Pointer<test> ptr2(ptr);

    ptr2->a = 50;
    ptr2->b = 50;

    EXPECT_EQ(ptr->a, 50);
    EXPECT_EQ(ptr->b, 50);

    EXPECT_EQ(ptr2->a, 50);
    EXPECT_EQ(ptr2->b, 50);

    ptr2.make_unique();
    ptr2->a = 0;
    ptr2->b = 0;

    EXPECT_EQ(ptr->a, 50);
    EXPECT_EQ(ptr->b, 50);

    EXPECT_EQ(ptr2->a, 0);
    EXPECT_EQ(ptr2->b, 0);
}


#if __linux__

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}


#endif
