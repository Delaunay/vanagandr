#include "CurveMovement.h"



namespace vanagandr
{
	//CurveMovement(Yield Low = Yield(), Yield Mid = Yield(), Yield Top = Yield(), Rate Par = 0);
	CurveMovement::CurveMovement(Yield Low, Yield Mid, Yield Top, Rate Par):
		LowMvt(Low), MidMvt(Mid), TopMvt(Top), ParallelMvt(Par), Data_(0), Adress_(0)
	{}

	Column CurveMovement::nameMvt()
	{
		Column a(3);	a(0) = 0;
		a(1) = 0;	a(2) = 0;

		if (ParallelMvt > 0)
			a(Parallel) =  1;	//PositiveParallel;

		else if (ParallelMvt < 0)
			a(Parallel) = -1;	//NegativeParallel;

		// this is a percentage change not a (discount) rate
		double slope = (LowMvt.r() - TopMvt.r())/(LowMvt.n() - TopMvt.n()) ;

		if ( slope > 0)
			a(Twist) =  1;		//PositiveTwist

		else if ( slope < 0)
			a(Twist) = -1;		//Negative Twist

		// this is a percentage change not a (discount) rate
		double r = slope * (MidMvt.n() - LowMvt.n()) + LowMvt.r();

		if (MidMvt.r() < r)
			a(Butterfly) =  1 ;	// PositiveButterfly;

		else if (MidMvt.r() > r)
			a(Butterfly) = -1 ;	// NegativeButterfly;

		return a;
	}

	Yield CurveMovement::operator() (Yield rate, InterpolationMethod a)
	{
		Rate r = 0;

		switch (a)
		{
			case Linear:
			{
				interpolation::Linear Lin;
				Lin.addPoint(LowMvt.n(), LowMvt.r());
				Lin.addPoint(MidMvt.n(), MidMvt.r());
				Lin.addPoint(TopMvt.n(), TopMvt.r());

				r = Lin(rate.n());
				break;
			}
			case Polynomial:
			{
				interpolation::Polynomial Pol;
				Pol.addPoint(LowMvt.n(), LowMvt.r());
				Pol.addPoint(MidMvt.n(), MidMvt.r());
				Pol.addPoint(TopMvt.n(), TopMvt.r());

				r = Pol(rate.n());
				break;
			}
		}

		rate.setr(rate.r() * ( 1.0 + r) + ParallelMvt);

		return rate;
	}

	void CurveMovement::identifyMvt(YieldCurve *one, YieldCurve *two)
	{/*
		interpolation::Polynomial ione;
		interpolation::Polynomial itwo;

		int on = one->size(), tn = two->size();

		for(int i = 0; i < on ; i++)
			ione.addPoint(one->operator [](i).n(), one->operator [](i).r());

		for(int i = 0; i < tn ; i++)
			itwo.addPoint(two->operator [](i).n(), two->operator [](i).r());

		PolynomialFunction<on, Real> pone = ione.exportFunction();
		PolynomialFunction<tn, Real> ptwo = itwo.exportFunction();

		unsigned int s = std::max(on, tn);

		PolynomialFunction<s, Real> pdif;

		if (on < tn)
		{
			pdif = ptwo;
			pdif -= pone;
		}
		else
		{
			pdif = pone;
			pdif -= ptwo;
		}
		// found the commun point
		Real x = secante(pdif);

		ParallelMvt = pdif(x);

		LowMvt.setn(two->FirstElement().n);
		MidMvt.setn(x);
		TopMvt.setn(two->LastElement().n());

		LowMvt.setr(	(two->FirstElement().r() - ParallelMvt)	/pone(LowMvt.n())	);
		MidMvt.setr(	(ptwo(x)				 - ParallelMvt)	/pone(MidMvt.n())	);
		TopMvt.setr(	(two-> LastElement().r() - ParallelMvt)	/pone(TopMvt.n())	);*/
	}

	void CurveMovement::print(Column a)
	{
		std::string twist = "Twist :\t";
		std::string butter = "Butterfly :\t";
		std::string Paral = "Parallel :\t";

		if (a(0) > 0)
			twist = twist + "Steeping";
		else
			twist = twist + "Flatening";

		if (a(1) > 0)
			butter = butter + "Positive";
		else
			butter = butter + "Negative";

		if (a(2) > 0)
			Paral = Paral + "Positive";
		else
			Paral = Paral + "Negative";

		std::cout << twist  << std::endl;
		std::cout << butter << std::endl;
		std::cout << Paral  << std::endl;
	}
}
