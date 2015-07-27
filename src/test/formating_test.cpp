#ifndef VANAGANDR_TEST_FORMATING_HEADER
#define VANAGANDR_TEST_FORMATING_HEADER

#include <gtest/gtest.h>

#include "../formating/strtable.h"

#include <iostream>

using namespace vanagandr;

TEST(Formating, All)
{
    std::cout << std::string(20, '*') << std::endl;
    Formating<std::string>::align_left(std::cout, "test_format", 20, '_');
    Formating<std::string>::align_right(std::cout, "test_format", 20, '_');
    Formating<std::string>::align_center(std::cout, "test_format", 20, '_');

    Formating<int>::align_left(std::cout, 1200, 20, '_');
    Formating<int>::align_right(std::cout, 120, 20, '_');
    Formating<int>::align_center(std::cout, 12, 20, '_');

    Formating<double>::align_left(std::cout, 1200.12, 20, '_');
    Formating<double>::align_right(std::cout, 120.12, 20, '_');
    Formating<double>::align_center(std::cout, 12.12, 20, '_');
}

#include "../formating/format.h"

using namespace vanagandr::formating;
using namespace std;

TEST(StrPicture, All)
{
    vector<string> v = {"rftgyuhji", "yhuji", "yghujiko"};

    StrPicture s(v);

    cout << frame(hcat(vcat(frame(s), frame(s)), vcat(frame(s), frame(s))));

    vector<string> vs = {"Serie1", "Serie2", "Serie3", "Serie4", "Serie100"};
    vector<double> vd = {12.10, 15.10, 5.10, 3.10, 10.10};

    cout << "Histogram using implied min/min\n";
    cout << frame(hcat(vs, histogram(vd, 20)));

    cout << "Histogram with specified min/max\n";
    cout << frame(hcat(vs, histogram(vd, {0, 20}, 20)));
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
