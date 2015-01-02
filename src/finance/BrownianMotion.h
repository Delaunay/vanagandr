#ifndef VANAGANDR_FINANCE_BM_HEADER
#define VANAGANDR_FINANCE_BM_HEADER

#include <ctime>

#include <boost/random/mersenne_twister.hpp>
#include <boost/multiprecision/random.hpp>
#include <boost/math/distributions/extreme_value.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/lognormal.hpp>

#include "../enum.h"

using namespace boost::random;


// TODO     - use C++11 instead of boost
//          - use Box Muller for Normal Rand
//          - how to test it ?


namespace vanagandr
{
    /*! @include BrownianMotion.dox */
	template <class Engine = mt19937>
	class UniformRandom
	{
		public:
            UniformRandom(double min = 0.0, double max = 1.0, double seed = 0.0):
                Engine_(seed), Udistr_(min, max)
			{}

            double  operator() ()	{	return Udistr_(Engine_);	}
            double  generate()		{	return Udistr_(Engine_);	}
            void    reset()			{	Udistr_.reset();			}

		protected:
            Engine                            Engine_;
            uniform_real_distribution<double> Udistr_;
	};

	template <class Engine = mt19937>
	class NormalRandom
	{
		public:
            NormalRandom(double mean = 0, double vol = 1, double seed = 0):
                Engine_(seed), Udistr_(0, 1), Ndistr_(mean, vol)
			{}

            double  operator() ()	{	return boost::math::quantile(Ndistr_, Udistr_(Engine_));	}
            double  generate()		{	return boost::math::quantile(Ndistr_, Udistr_(Engine_));	}
            void    reset()			{	Udistr_.reset();	}

		protected:
            Engine						Engine_;
            uniform_real_distribution<> Udistr_;
            boost::math::normal			Ndistr_;
	};

    /*
    template <class Engine = mt19937>
    class GambelRandom
    {
        public:
            GambelRandom(double location = 0, double scale = 0.5, double seed = 0):
                Engine_(seed), Udistr_(0, 1), Ndistr_(location, scale)
            {
            }

            double  operator() ()	{	return boost::math::quantile(Gdistr_, Udistr_(Engine_));	}
            double  generate()		{	return boost::math::quantile(Gdistr_, Udistr_(Engine_));	}
            void    reset()			{	Udistr_.reset();	}

        protected:
            Engine                                          Engine_;
            uniform_real_distribution<>                     Udistr_;
            boost::math::extreme_value_distribution			Gdistr_;
    };*/

	template <class Engine = mt19937>
	class LogNormalRandom
	{
		public:
            LogNormalRandom(double location = 0, double scale = 1, double seed = 0):
                Engine_(seed), Udistr_(0, 1), Ndistr_(location, scale)
			{}

            double  operator() ()	{	return boost::math::quantile(Ndistr_, Udistr_(Engine_));	}
            double  generate()		{	return boost::math::quantile(Ndistr_, Udistr_(Engine_));	}
            void    reset()			{	Udistr_.reset();	}

		protected:
            Engine							Engine_;
            uniform_real_distribution<>		Udistr_;
            boost::math::lognormal			Ndistr_;
	};

    template <class PRNG = NormalRandom<> >
	class GBrownianMPath
	{
		public:
            GBrownianMPath(double So, double Vol, double dt, double R = 0.0, double seed = 0):
                Rand_(0, 1, seed), St_(So), So_(So), t_(0)
			{
                u_ = exp ( ( R - Vol * Vol / 2 ) * dt );
                v_ = Vol * pow( dt, 0.5);
			}

			double operator() ()
			{
                St_ =  St_ * u_ * exp( v_ * Rand_() );
                t_++;
                return St_;
			}

			double price(double St)
			{
                return St * u_ * exp( v_ * Rand_() );
			}

			double price()
			{
                St_ =  St_ * u_ * exp( v_ * Rand_() );
                t_++;
                return St_;
			}

            void resetS()	{	St_ = So_; t_ = 0;	}
            void reset()	{	Rand_.reset(); St_ = So_; t_ = 0;	}

            double  lastPrice()	{	return St_;	}
            int		period()	{	return t_;	}

		protected:
            PRNG    Rand_;

            double  St_;
            double  So_;
            double  u_;
            double  v_;
            Periods t_;
	};


    template <class PRNG = NormalRandom<> >
	class GBrownianMPoint
	{
		public:
            GBrownianMPoint(double So, double Vol, double dt, double R = 0.0, double seed = 0):
                Rand_(0, 1, seed)
			{
                u_ = So * exp ( ( R - Vol * Vol / 2 ) * dt );
                v_ = Vol * pow( dt, 0.5);
			}

			double operator () ()
			{
                return u_ * exp( v_ * Rand_() );
			}

			double price()
			{
                return u_ * exp( v_ * Rand_() );
			}

            void reset()	{	Rand_.reset(); 	}

		protected:
            PRNG    Rand_;
            double  u_;
            double  v_;

	};
}

#endif // FINBROWNIANMOTION_H
