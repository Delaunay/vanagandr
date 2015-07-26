#ifndef VANAGANDR_TEST_PDE_HEADER
#define VANAGANDR_TEST_PDE_HEADER


#if 0
#include <gtest/gtest.h>

#include "../finance/Options.h"
#include "../math/pde.h"

#include <iostream>

using namespace vanagandr::pde;
using namespace vanagandr::finance;

template<typename OptionClassType = Call>
class BlackScholesPDE : public FiniteDifference1D<double, Explicit>
{
public:

    BlackScholesPDE()
    {}

    // functions
    double d2g(const double& S, const double& t) const
    {
        return pow(_sigma, 2.0) * pow(S, 2.0) / 2.0;
    }
    double dg (const double& S, const double& t) const
    {
        return _r * S;
    }
    double g  (const double& S, const double& t) const
    {
        return -_r;
    }

    double initial_time(const double& S)
    {
        return OptionClassType::payoff(S, _K);
    }

    double max         (const double& t)
    {
        return OptionClassType::payoff(S, _K) * exp(-r * t);
    }

    double min         (const double& t)
    {
        return OptionClassType::payoff(S, _K) * exp(-r * t);
    }

    double time(const unsigned int& ite)
    {
        return _time - T(ite) * _dt;
    }

protected:

    double _sigma;
    double _r;
    double _K;
};

//TEST(FiniteDifference1D, Finance)
//{

//{

#if __linux__

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}

#endif
#endif

#endif
