/*******************************************************************************
 *
 *  @autor Pierre Delaunay
 *
 *
 *
 ******************************************************************************/
#ifndef VANAGANDR_FINANCE_OPTIONS_HEADER
#define VANAGANDR_FINANCE_OPTIONS_HEADER

//#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/math/distributions/normal.hpp>
#include <eigen3/Eigen/Dense>

#include "../math/Matrix.h"

// Eigen::Column || std::vector have similar perf

namespace vanagandr
{
namespace finance
{
    struct Call
    {
        static double payoff (const double& St, const double& K) { return std::max(St - K, 0.0); }
    };

    struct Put
    {
        static double payoff (const double& St, const double& K) { return std::max(K - St, 0.0); }
    };

    enum OptionType
    {
        European,
        American
    };

    enum EvaluationEngine
    {
        BlackScholesEngine,
        BinomialTree,
        TrinomialTree,
        MDFE,
    };

    enum Adjustement
    {
        NotAdjusted,
        BlackScholesAdjust,
        Adjusted = BlackScholesAdjust,

    };

    boost::math::normal_distribution<> normal_standard;

    template<typename OptionClassType = Call>
    class BlackMertonScholes
    {
        public:
            static double price(double So, double K, double vol, double T, double r, double y = 0)
            {
                double d1 = (log(So / K) + (r - y + vol * vol / 2.0) * T)/(vol * sqrt(T));
                double d2 = d1 - vol * sqrt(T);

                double Nd1 = boost::math::cdf(normal_standard, d1);
                double Nd2 = boost::math::cdf(normal_standard, d2);

                return So * exp(- y * T) * Nd1 - K * Nd2 * exp(- r * T);
            }
    };

    template<>
    class BlackMertonScholes<Put>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, double y = 0)
            {
                double d1 = (log(So / K) + (r - y + vol * vol / 2.0) * T)/(vol * sqrt(T));
                double d2 = d1 - vol * sqrt(T);

                double Nd1 = boost::math::cdf(normal_standard, -d1);
                double Nd2 = boost::math::cdf(normal_standard, -d2);

                return K * Nd2 * exp(- r * T) - So * exp(- y * T) * Nd1;
            }
    };

    // Primary Template
    template<typename OptionClassType, OptionType Type, EvaluationEngine Engine, Adjustement adj = NotAdjusted>
    class Option
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                return 0;
            }
    };

    // Black Scholes for consistency
    template<typename OptionClassType>
    class Option<OptionClassType, European, BlackScholesEngine, NotAdjusted>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n = 0, double y = 0)
            {
                return BlackMertonScholes<OptionClassType>::price(So, K, vol, T, r, y);
            }
    };

    // American Binomial Tree
    template<typename OptionClassType>
    class Option<OptionClassType, American, BinomialTree, NotAdjusted>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- (r) * dt),
                       u  = exp(vol * sqrt(dt)),
                       d  = 1.0/u,
                       p  = (exp((r - y) * dt) - d) / (u - d);

                // allocate memory
                Column prices(n + 1);

                // generate the prices
                for(int i = 0; i < n + 1; ++i)
                    prices(i) = OptionClassType::payoff(So * pow(u, double(n - i * 2)), K);

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= i; ++j)
                        prices(j) = std::max((prices(j) * p + prices(j + 1) * (1 - p)) * f,
                        OptionClassType::payoff(So * pow(u, double(i - 2 * j)), K));

                return prices[0];
            }
    };

    // European Binomial Tree
    template<typename OptionClassType>
    class Option<OptionClassType, European, BinomialTree, NotAdjusted>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- (r) * dt),
                       u  = exp(vol * sqrt(dt)),
                       d  = 1.0/u,
                       p  = (exp((r - y) * dt) - d) / (u - d);

                // allocate memory
                std::vector<double> prices(n + 1);

                // generate the prices
                for(int i = 0; i < n + 1; ++i)
                    prices[i] = OptionClassType::payoff(So * pow(u, double(n - i * 2)), K);

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= i; ++j)
                        prices[j] = (prices[j] * p + prices[j + 1] * (1 - p)) * f;

                return prices[0];
            }

    };

    // European Binomial Tree Ajusted
    template<typename OptionClassType>
    class Option<OptionClassType, European, BinomialTree, BlackScholesAdjust>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- (r) * dt),
                       u  = exp(vol * sqrt(dt)),
                       d  = 1.0/u,
                       p  = (exp((r - y) * dt) - d) / (u - d);

                // allocate memory
                Column prices(n);

                n = n - 1;
                // generate the prices
                for(int i = 0; i < n + 1; ++i)
                    prices(i) = BlackMertonScholes<OptionClassType>::price(So * pow(u, double(n - i * 2)), K, vol, dt, r, y);

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= i; ++j)
                        prices(j) = (prices(j) * p + prices(j + 1) * (1 - p)) * f;

                return prices(0);
            }
    };

    // American Binomial Tree Ajusted
    template<typename OptionClassType>
    class Option<OptionClassType, American, BinomialTree, BlackScholesAdjust>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- (r)* dt),
                       u  = exp(vol * sqrt(dt)),
                       d  = 1.0/u,
                       p  = (exp((r - y) * dt) - d) / (u - d);

                // allocate memory
                Column prices(n);

                n = n - 1;

                // generate the prices
                for(int i = 0; i < n + 1; ++i)
                    prices(i) = std::max(BlackMertonScholes<OptionClassType>::price(So * pow(u, double(n - i * 2)), K, vol, dt, r, y),
                                         OptionClassType::payoff(So * pow(u, double(n - i * 2)), K));

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= i; ++j)
                        prices(j) = std::max((prices(j) * p + prices(j + 1) * (1 - p)) * f,
                        OptionClassType::payoff(So * pow(u, double(i - 2 * j)), K));

                return prices(0);
            }
    };

    // European Trinomial Tree
    template<typename OptionClassType>
    class Option<OptionClassType, European, TrinomialTree, BlackScholesAdjust>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- r * dt),
                       M  = exp((r - y) * dt),
                       V  = exp((2.0 * (r - y) + vol *vol) * dt),
                       m  = V * V / (M * M * M),
                       H  = m * V * (V + 1.0)/ (2.0 * M * M),
                       u  = H + sqrt(H * H - m * m),
                       d  = H - sqrt(H * H - m * m),
                       q1 = (m * d - M * (m + d) + V)/((u - d) * (u - m)),
                       q2 = (M * (u + d) - u * d - V)/((u - m) * (m - d)),
                       q3 = (u * m - M * (u + m) + V)/((u - d) * (m - d));

                // allocate memory
                n = n - 1;
                int g = 2 * n + 1;
                Column prices(2 * n + 1);

                // generate the prices
                for(int i = 0; i < g; ++i)
                    prices(i) = std::max(BlackMertonScholes<OptionClassType>::price(So * pow(u, double(n - i)) * pow(m, i), K, vol, dt, r, y),
                                         OptionClassType::payoff(So * pow(u, double(n - i)) * pow(m, i), K));

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= 2 * i; ++j)
                        prices(j) = (prices(j) * q1 + prices(j + 1) * q2 + prices(j + 2) * q3) * f;

                return prices(0);
            }
    };

    // European Trinomial Tree
    template<typename OptionClassType>
    class Option<OptionClassType, European, TrinomialTree, NotAdjusted>
    {
        public:
        static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
        {
            double dt = T/double(n),
                   f  = exp(- r * dt),
                   M  = exp((r - y) * dt),
                   V  = exp((2.0 * (r - y) + vol *vol) * dt),
                   m  = V * V / (M * M * M),
                   H  = m * V * (V + 1.0)/ (2.0 * M * M),
                   u  = H + sqrt(H * H - m * m),
                   d  = H - sqrt(H * H - m * m),
                   q1 = (m * d - M * (m + d) + V)/((u - d) * (u - m)),
                   q2 = (M * (u + d) - u * d - V)/((u - m) * (m - d)),
                   q3 = (u * m - M * (u + m) + V)/((u - d) * (m - d));

            // allocate memory
            int g = 2 * n + 1;
            Column prices(2 * n + 1);

            // generate the prices
            for(int i = 0; i < g; ++i)
                prices(i) = OptionClassType::payoff(So * pow(u, double(n - i)) * pow(m, i), K);

            // Columns
            for(int i = n - 1; i >= 0; --i)
                // Rows
                for(int j = 0; j <= 2 * i; ++j)
                    prices(j) = (prices(j) * q1 + prices(j + 1) * q2 + prices(j + 2) * q3) * f;

            return prices(0);
        }
    };

    // American Trinomial Tree
    template<typename OptionClassType>
    class Option<OptionClassType, American, TrinomialTree, BlackScholesAdjust>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- r * dt),
                       M  = exp((r - y) * dt),
                       V  = exp((2.0 * (r - y) + vol *vol) * dt),
                       m  = V * V / (M * M * M),
                       H  = m * V * (V + 1.0)/ (2.0 * M * M),
                       u  = H + sqrt(H * H - m * m),
                       d  = H - sqrt(H * H - m * m),
                       q1 = (m * d - M * (m + d) + V)/((u - d) * (u - m)),
                       q2 = (M * (u + d) - u * d - V)/((u - m) * (m - d)),
                       q3 = (u * m - M * (u + m) + V)/((u - d) * (m - d));

                // allocate memory
                n = n - 1;
                int g = 2 * n + 1;
                Column prices(2 * n + 1);

                // generate the prices
                for(int i = 0; i < g; ++i)
                    prices[i] = std::max(BlackMertonScholes<OptionClassType>::price(So * pow(u, double(n - i)) * pow(m, i), K, vol, dt, r, y),
                                         OptionClassType::payoff(So * pow(u, double(n - i)) * pow(m, i), K));

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= 2 * i; ++j)
                        prices(j) = std::max((prices(j) * q1 + prices(j + 1) * q2 + prices(j + 2) * q3) * f,
                        OptionClassType::payoff(So * pow(u, double(i - j)) * pow(m, j) , K));

                return prices(0);
            }
    };

    // European Trinomial Tree
    template<typename OptionClassType>
    class Option<OptionClassType, American, TrinomialTree, NotAdjusted>
    {
        public:
            static double price(double So, double K, double vol, double T, double r, int n, double y = 0)
            {
                double dt = T/double(n),
                       f  = exp(- r * dt),
                       M  = exp((r - y) * dt),
                       V  = exp((2.0 * (r - y) + vol *vol) * dt),
                       m  = V * V / (M * M * M),
                       H  = m * V * (V + 1.0)/ (2.0 * M * M),
                       u  = H + sqrt(H * H - m * m),
                       d  = H - sqrt(H * H - m * m),
                       q1 = (m * d - M * (m + d) + V)/((u - d) * (u - m)),
                       q2 = (M * (u + d) - u * d - V)/((u - m) * (m - d)),
                       q3 = (u * m - M * (u + m) + V)/((u - d) * (m - d));

                // allocate memory
                int g = 2 * n + 1;
                Column prices(2 * n + 1);

                // generate the prices
                for(int i = 0; i < g; ++i)
                    prices(i) = OptionClassType::payoff(So * pow(u, double(n - i)) * pow(m, i), K);

                // Columns
                for(int i = n - 1; i >= 0; --i)
                    // Rows
                    for(int j = 0; j <= 2 * i; ++j)
                        prices(j) = std::max((prices(j) * q1 + prices(j + 1) * q2 + prices(j + 2) * q3) * f,
                        OptionClassType::payoff(So * pow(u, double(i - j)) * pow(m, j) , K));

                return prices(0);
            }
    };
}
}

#endif
