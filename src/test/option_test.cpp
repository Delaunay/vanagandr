#ifndef VANAGANDR_TEST_OPTION_HEADER
#define VANAGANDR_TEST_OPTION_HEADER

#include <gtest/gtest.h>

#include "../finance/Options.h"

using namespace vanagandr::finance;

double So = 50.00,
        K = 50.00,
      vol = 00.25,
        T = 00.25,
        r = 00.05,
        y = 00.02,
        N = 100;

TEST(Options, BlackMertonScholes)
{
    EXPECT_DOUBLE_EQ(BlackMertonScholes<Call>::price(So, K, vol, T, r, y),
                     2.6603823816568002);
    EXPECT_DOUBLE_EQ(BlackMertonScholes<Put>::price(So, K, vol, T, r, y),
                     2.2886484467167563);
}


TEST(Options, BinomialTreeNA_euro_std)
{
    Option<Put , European, BinomialTree>::price(So, K, vol, T, r, 1000, y);
}

TEST(Options, BinomialTreeNA)
{
    Option<Put , American, BinomialTree>::price(So, K, vol, T, r, 1000, y);
}

TEST(Options, TrinomialTreeNA)
{
    Option<Put , American, TrinomialTree>::price(So, K, vol, T, r, 1000, y);
}

TEST(Options, BinomialTreeA)
{
    Option<Put , American, BinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
}

TEST(Options, TrinomialTreeA)
{
    Option<Put , American, TrinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
}

TEST(Options, Trees)
{
    // test if every possibility works
    double eu_call_bi    = Option<Call, European, BinomialTree>::price(So, K, vol, T, r, 1000, y);
    double eu_put_bi     = Option<Put , European, BinomialTree>::price(So, K, vol, T, r, 1000, y);
    double eu_call_bi_ad = Option<Call, European, BinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
    double eu_put_bi_ad  = Option<Put , European, BinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
    double am_call_bi    = Option<Call, American, BinomialTree>::price(So, K, vol, T, r, 1000, y);
    double am_put_bi     = Option<Put , American, BinomialTree>::price(So, K, vol, T, r, 1000, y);
    double am_call_bi_ad = Option<Call, American, BinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
    double am_put_bi_ad  = Option<Put , American, BinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);

    double eu_call_ti    = Option<Call, European, TrinomialTree>::price(So, K, vol, T, r, 1000, y);
    double eu_put_ti     = Option<Put , European, TrinomialTree>::price(So, K, vol, T, r, 1000, y);
    double eu_call_ti_ad = Option<Call, European, TrinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
    double eu_put_ti_ad  = Option<Put , European, TrinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
    double am_call_ti    = Option<Call, American, TrinomialTree>::price(So, K, vol, T, r, 1000, y);
    double am_put_ti     = Option<Put , American, TrinomialTree>::price(So, K, vol, T, r, 1000, y);
    double am_call_ti_ad = Option<Call, American, TrinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);
    double am_put_ti_ad  = Option<Put , American, TrinomialTree, Adjusted>::price(So, K, vol, T, r, 1000, y);

    std::cout << "[          ] BLS: " << BlackMertonScholes<Call>::price(So, K, vol, T, r, y)<< std::endl;
    std::cout << "[          ] \t" << "EU Call B: " << eu_call_bi << "\t" << eu_call_bi_ad << std::endl;
    std::cout << "[          ] \t" << "EU Call T: " << eu_call_ti << "\t" << eu_call_ti_ad << std::endl;
    std::cout << "[          ] \t" << "AM Call B: " << am_call_bi << "\t" << am_call_bi_ad << std::endl;
    std::cout << "[          ] \t" << "AM Call T: " << am_call_ti << "\t" << am_call_ti_ad << std::endl;
    std::cout << "[          ] \t" << " "<< std::endl;
    std::cout << "[          ] BLS: " << BlackMertonScholes<Put>::price(So, K, vol, T, r, y) << std::endl;
    std::cout << "[          ] \t" << "EU Put  B: " << eu_put_bi  << "\t" << eu_put_bi_ad  << std::endl;
    std::cout << "[          ] \t" << "EU Put  T: " << eu_put_ti  << "\t" << eu_put_ti_ad  << std::endl;
    std::cout << "[          ] \t" << "AM Put  B: " << am_put_bi  << "\t" << am_put_bi_ad  << std::endl;
    std::cout << "[          ] \t" << "AM Put  T: " << am_put_ti  << "\t" << am_put_ti_ad  << std::endl;
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
