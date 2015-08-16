#include "../finance/OptionEngine.h"


namespace vanagandr
{
	namespace Option
	{
		double putCallparity(Price So, Price K, Periods T, Price Call, Price Put, Rate rf)
		{
			return Call - Put - ( So - K / exp(rf * T));
		}

		namespace MonteCarlo
		{
			namespace European
			{
				Price optionCall(double So, double K,double t, double rf, double Vol, int n, double seed)
				{
					Price price = 0;
					GBrownianMPoint<> a(So, Vol, t, rf, seed);

					for( int i = 0; i < n; i++)
						price = price + std::max( a() - K, 0.0);

					return price / ( (double) n * exp( t * rf ));
				}

				Price optionPut(double So, double K,double t, double rf, double Vol, int n, double seed)
				{
					Price price = 0;
					GBrownianMPoint<> a(So, Vol, t,rf, seed);

					for( int i = 0; i < n; i++)
						price = price + std::max( K - a(), 0.0);

					return price / ( (double) n * exp( t * rf ));
				}

				namespace Barrier
				{
					//Price optionCall(double So, double K,double t, double rf, double Vol, double n = 10000, double seed = 0);
					//Price optionPut(double So, double K,double t, double rf, double Vol, double n = 10000, double seed = 0);
				}

				namespace Asian
				{
					// n => number of path generated
					// m => number of point each path has
					Price optionCall(double So, double K,double t, double rf, double Vol, int n, int m, double seed)
					{
						Price price = 0;
						GBrownianMPath<> a(So, Vol, (double) t/ (double) m, rf, seed);
						double Sx;

						for ( int i = 0; i < n; i++)
						{
							a.resetS();
							Sx = So;

							for( int j = 0; j < m; j++)
								Sx = Sx + a();

							price = price + std::max( Sx /(m + 1) - K, 0.0);
						}

						return price/( (double) n * exp(t * rf ));
					}

					Price optionPut(double So, double K, double t, double rf, double Vol, int n, int m, double seed)
					{
						Price price = 0;

						GBrownianMPath<> a(So, Vol, (double) t/ (double) m, rf, seed);

						double Sx;

						for ( int i = 0; i < n; i++)
						{
							a.resetS();
							Sx = So;

							for( int j = 0; j < m; j++)
								Sx = Sx + a();

							price = price + std::max( K - Sx /(m + 1), 0.0);
						}

						return price/( (double) n * exp(t * rf ));
					}
				}

				namespace LookBack
				{
					namespace Fixed
					{
						Price optionCall(double So, double K, double t, double rf, double Vol, int n, int m, double seed)
						{
							Price price = 0;
							GBrownianMPath<> a(So, Vol, (double) t/ (double) m, rf, seed);
							double Sx;

							for ( int i = 0; i < n; i++)
							{
								a.resetS();
								Sx = So;

								for( int j = 0; j < m; j++)
									Sx = std::max( Sx, a() );

								price = price + std::max( Sx - K, 0.0);
							}

							return price/( (double) n * exp(t * rf ));
						}

						Price optionPut(double So, double K, double t, double rf, double Vol, int n, int m, double seed)
						{
							Price price = 0;
							GBrownianMPath<> a(So, Vol, (double) t/ (double) m, rf, seed);
							double Sx;

							for ( int i = 0; i < n; i++)
							{
								a.resetS();
								Sx = So;

								for( int j = 0; j < m; j++)
									Sx = std::min( Sx, a() );

								price = price + std::max( K - Sx, 0.0);
							}

							return price/( (double) n * exp(t * rf ));
						}
					}
				}

			}


		}

		namespace BinomialTree
		{

		}

		namespace BlackScholes
		{
			namespace European
			{
				Price optionCall(double So, double K, double t, double rf, double Vol)
				{
					double d1 = log(So/K) + (rf + Vol * Vol / 2.0) * t		   / ( Vol * sqrt(t));
					double d2 = d1 - Vol * sqrt(t);

					boost::math::normal a(0, 1);

					d1 = boost::math::cdf(a, d1);
					d2 = boost::math::cdf(a, d2);

					return So * d1 - K * d2 / exp(rf * t);
				}
				Price optionPut(double So, double K, double t, double rf, double Vol)
				{
					double d1 = log(So/K) + (rf + Vol * Vol / 2.0) * t		   / ( Vol * sqrt(t));
					double d2 = d1 - Vol * sqrt(t);

					boost::math::normal a(0, 1);

					d1 = boost::math::cdf(a, -d1);
					d2 = boost::math::cdf(a, -d2);

					return  K * d2 / exp(rf * t) - So * d1;
				}
			}

		}
	}
}

