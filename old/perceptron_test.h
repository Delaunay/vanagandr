#ifndef VANAGANDR_TEST_PERCEPTRON_HEADER
#define VANAGANDR_TEST_PERCEPTRON_HEADER

#include <gtest/gtest.h>

#include "../AI/Perceptron.h"
#include <iostream>

using namespace vanagandr::ai;

TEST(Perceptron, base)
{
    BrainStructure structure(3);
        structure.input = 400;
        structure.hidden[0] = 200;
        structure.hidden[1] = 100;
        structure.hidden[2] = 25;
        structure.output = 10;

    Perceptron<double> a(structure);


    a.printf(std::cout);
}



#endif
