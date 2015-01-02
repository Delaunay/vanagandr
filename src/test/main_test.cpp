#include <gtest/gtest.h>

#include "file_test.h"
#include "varmin_test.h"
#include "integration_test.h"
#include "option_test.h"

#if __linux__

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

#endif
