#ifndef VANAGANDR_TEST_PERCEPTRON_HEADER
#define VANAGANDR_TEST_PERCEPTRON_HEADER

#include <gtest/gtest.h>

#include "../AI/Perceptron.h"
#include <iostream>

using namespace vanagandr::ai;

TEST(Perceptron, base)
{
    BrainStructure structure = {400, {25}, 10};

    Perceptron a(structure);

    a.printf(std::cout);
    a._allocate_temporary(50);
    std::cout << "\n";
    a.printf(std::cout);
    std::cout << "\n";
    std::cout << a.a(0);
    std::cout << "\n";
}



#endif
