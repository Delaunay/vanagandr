#include <gtest/gtest.h>
#include <string>

#include "linear_reg_test.h"
//#include "file_test.h"
//#include "varmin_test.h"
//#include "integration_test.h"
//#include "option_test.h"
//#include "matrix_test.h"
//#include "logistic_test.h"
//#include "solver1D_test.h"
//#include "linkedlist_test.h"
//#include "simplearray_test.h"
//#include "eigen_date.h"
//#include "sort_test.h"
//#include "perceptron_test.h"
//#include "formating_test.h"

using namespace std;
#if __linux__

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}


#endif

