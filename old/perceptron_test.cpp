#ifndef VANAGANDR_TEST_PERCEPTRON_HEADER
#define VANAGANDR_TEST_PERCEPTRON_HEADER

#include <gtest/gtest.h>

#include "../AI/Perceptron.h"
#include "../file/MatrixIO.h"
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
}



TEST(Perceptron, Cost)
{
    Matrix x = vanagandr::file::read("../data/xdebug.csv", false);
    Matrix y = vanagandr::file::read("../data/yvec.csv", false);
    Matrix t1 = vanagandr::file::read("../data/t1debug.csv", false);
    Matrix t2 = vanagandr::file::read("../data/t2debug.csv", false);

    std::cout << "X Matrix:\n" << x << "\n";
    std::cout << "Y Matrix:\n" << y << "\n\n";

    std::cout << "T1 Matrix:\n" << t1 << "\n";
    std::cout << "T2 Matrix:\n" << t2 << "\n\n";

                              //    3      5        3
    BrainStructure structure = {x.cols(), {5}, y.cols()};

    Perceptron a(structure);
    a.theta(0) = t1.transpose();
    a.theta(1) = t2.transpose();

    a._allocate_temporary(x.rows());
    std::cout << "Cost: " << a.cost(x, y) <<  " = 2.10092 \n";

    // Compute Gradient using finite difference
    std::vector<double> ngrad = a.numerical_gradient(x, y, 1e-6);


    //a.gradient(y);


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
