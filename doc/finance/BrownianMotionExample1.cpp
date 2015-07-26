#include <iostream>
#include <vanagandr/finance/BrownianMotion.h>

using namespace vanagandr;

int main(arv, argc)
{
    Price price = 0;

    int n = 40000;

    double So 	= 50;
    double K 	= 50;
    double Vol 	= 0.4;
    double t 	= 1;
    double rf 	= 0.03;
    double seed = 0;

    // creation of the GBM Point
    GBrownianMPoint<> MyGBMP(So, Vol, t, rf, seed);

    // simulate n different prices and compute the option Value
    for( int i = 0; i < n; i++)
        price = price + std::max( MyGBMP() - K, 0.0);

    // compute the average price and discount it at the risk free rate
    price = price / ( double(n) * exp( t * rf ))

    // print the price
    std::cout << "Option Price : " << price <<std::endl;

    return 0;
}