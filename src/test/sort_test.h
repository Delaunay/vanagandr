#ifndef VANAGANDR_TEST_SOLVER1D_HEADER
#define VANAGANDR_TEST_SOLVER1D_HEADER

#include <gtest/gtest.h>

#include "../containers/SimpleArray.h"
#include "../containers/Sort.h"

using namespace vanagandr::containers;

#include <cstdlib>
#include <iostream>

static SimpleArray<double> ary;

TEST(SimpleArraySort, Creation)
{
    for (int i = 0; i < 100000; i++)
        ary.push_back(rand());
}

TEST(SimpleArraySort, HeapSort)
{
    Sort<SimpleArray<double> >::heapsort(ary);
}

TEST(SimpleArraySort, Print)
{
    std::cout << ary.str() << std::endl;
}

TEST(SimpleArraySort, HeapSortReverse)
{
    Sort<SimpleArray<double>, true>::heapsort(ary);
}

TEST(SimpleArraySort, Printreverse)
{
    std::cout << ary.str() << std::endl;
}

#endif
