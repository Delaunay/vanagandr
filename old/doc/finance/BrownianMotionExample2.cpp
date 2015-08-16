#include <iostream>
#include <vanagandr/finance/BrownianMotion.h>

using namespace vanagandr;

int main(arv, argc)
{
    Price price = 0;

    int n = 40000;
    int m = 1000;

    double So 	= 50;
    double K 	= 50;
    double Vol 	= 0.4;
    double t 	= 1;
    double rf 	= 0.03;
    double seed = 0;

    Price price = 0;

    // creation of the GBM Path
    GBrownianMPath<> MyGBMP(So, Vol, (double) t/ (double) m, rf, seed);
    double Sx;

    // we want to create n path with m points
    for ( int i = 0; i < n; i++)
    {
        // reset the Path
        MyGBMP.resetS();
        Sx = So;

        // generate the m prices and sum them
        for( int j = 0; j < m; j++)
            Sx = Sx + MyGBMP();

        // compute the average price of the asset (Sx / (m + 1.0) )
        // compute the gain from the option std::max( Sx /(m + 1.0) - K, 0.0)
        // sum the prime
        price = price + std::max( Sx /double(m + 1) - K, 0.0);
    }

    // compute the average prime and discount it at the risk free rate
    price = price/( double(n) * exp(t * rf ));

    // print the price
    std::cout << "Option Price : " << price <<std::endl;

    return 0;
}