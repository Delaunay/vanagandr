#ifndef VANAGANDR_TEST_VECTOR2D_HEADER
#define VANAGANDR_TEST_VECTOR2D_HEADER

#include <gtest/gtest.h>

#include "../containers/Vector2D.h"
#include "../containers/Sort.h"

using namespace vanagandr::containers;

Vector2D<double> v(10, 10);

TEST(Vector2D, init)
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            v(i, j) = j + i * 10;
}

TEST(Vector2D, print)
{
    v.print(std::cout);
}

TEST(Vector2D, iterator)
{
    V2DRow<double> r(0, v);

    for(auto i = r.begin(); i != r.end(); ++i)
        std::cout << *i << " ";

//    Vector2D<double>::ColIterator c(0, v);
//    while(c != v.end_col(0))
//    {
//        std::cout << *c << std::endl;
//        ++c;
//    }

//    Vector2D<double>::RowIterator r(9, v);

//    while(r != v.end_row(9))
//    {
//        std::cout << *r << " ";
//        ++r;
//    }

//    std::cout << "\n";
}

TEST(Vector2D, sorting)
{
//    v.print(std::cout);

    V2DRow<double> r(0, v);
    V2DCol<double> c(0, v);

    vanagandr::containers::Sort<V2DRow<double>, true>::heapsort(r);
    vanagandr::containers::Sort<V2DCol<double>, true>::heapsort(c);

    v.print(std::cout);
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
