#ifndef VANAGANDR_TEST_VARMIN_HEADER
#define VANAGANDR_TEST_VARMIN_HEADER

#include <gtest/gtest.h>

#include "../finance/VarianceMin.h"

using namespace vanagandr::finance;

//covariance Matrix
Matrix cov(2, 2);

// ret Matrix
Matrix ret(2, 1);

void initialize_varmin()
{
    cov << 8.00891224e-05, -1.79681601e-06, -1.79681601e-06, 2.59598343e-05;

    ret << 1291463.986058, 102494.439836;
    ret = ret / 1000000000;
}


TEST(variance_min, pure)
{
    // initialization
    initialize_varmin();

    // compute
    Matrix w = variance_min(cov, true);

    // values
    EXPECT_DOUBLE_EQ(w(0, 0), 0.25315573659870083);     // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 0), 0.74684426340129917);     // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 0), 1.8933079045259392e-05);  // Lagrangian w = 1
}

TEST(variance_min, target_return)
{
    double target = 0.000102494439836;

    // compute
    Matrix w = variance_min(cov, ret, target, true);

    EXPECT_DOUBLE_EQ(w(0, 0), 0.0);                     // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 0), 1.0);                     // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 0), 2.8352580467710501e-05);  // lagrangian w = 1
    EXPECT_DOUBLE_EQ(w(3, 0), -0.023345131419217513);   // lagrangian E(r) = tr
}

TEST(variance_min, risk_free)
{
    double target = 0.000102494439836,
               rf = 0;

    // compute
    Matrix w = variance_min(cov, ret, target, rf, true);

    EXPECT_DOUBLE_EQ(w(0, 0), 0.077443282895447135);    // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 0), 0.024188912280465012);    // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 0), 0.89836780482408785);     // Risk Free Asset
    EXPECT_DOUBLE_EQ(w(3, 0), -4.979432928456253e-23);  // lagrangian w = 1
    EXPECT_DOUBLE_EQ(w(4, 0), 0.0047689301478861922);   // lagrangian E(r) = tr
}

TEST(variance_min, target_return_matrix)
{
    Matrix target(2, 1);
    target << 0.000102494439836, 0.000165071784374;

    // compute
    Matrix w = variance_min(cov, ret, target, true);

    // target 1
    EXPECT_DOUBLE_EQ(w(0, 0), 0.0);                     // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 0), 1.0);                     // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 0), 2.8352580467710501e-05);  // lagrangian w = 1
    EXPECT_DOUBLE_EQ(w(3, 0), -0.023345131419217513);   // lagrangian E(r) = tr

    // target 2
    EXPECT_DOUBLE_EQ(w(0, 1), 0.052631578947368404);    // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 1), 0.94736842105263164);     // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 1), 2.639424746913239e-05);   // lagrangian w = 1
    EXPECT_DOUBLE_EQ(w(3, 1), -0.018491632368256083);   // lagrangian E(r) = tr
}

TEST(variance_min, risk_free_tr_matrix)
{
    Matrix target(2, 1);
    target << 0.000102494439836, 0.000165071784374;

    double rf = 0;

    // compute
    Matrix w = variance_min(cov, ret, target, rf, true);

    // target 1
    EXPECT_DOUBLE_EQ(w(0, 0), 0.077443282895447135);    // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 0), 0.024188912280465012);    // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 0), 0.89836780482408785);     // Risk Free Asset
    EXPECT_DOUBLE_EQ(w(3, 0), -4.979432928456253e-23);  // lagrangian w = 1
    EXPECT_DOUBLE_EQ(w(4, 0), 0.0047689301478861922);   // lagrangian E(r) = tr

    // target 2
    EXPECT_DOUBLE_EQ(w(0, 1), 0.12472579893882024);     // Asset 1
    EXPECT_DOUBLE_EQ(w(1, 1), 0.038957302645797276);    // Asset 2
    EXPECT_DOUBLE_EQ(w(2, 1), 0.83631689841538248);     // Risk Free Asset
    EXPECT_DOUBLE_EQ(w(3, 1), 1.8341961799756578e-22);  // lagrangian w = 1
    EXPECT_DOUBLE_EQ(w(4, 1), 0.0076805708712214182);   // lagrangian E(r) = tr
}

#endif
