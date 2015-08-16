#include "../finance/Future.h"


namespace vanagandr
{

	Future::Future(Periods n, Rate R, Value So, Value Fo, Rate q)
		:fn(n), fr(R), fFo(Fo), fSo(So), fq(q)
 	{
		//CashFlows::AddFlow(CashFlow());
 	}

	double Future::cptPV(Periods t, Rate v, Value St)
 	{
		return St / exp( fq * (fn - t) ) - CashFlowMaster::presentValue(t, v) - fFo / exp( (fr + v) * ( fn - t) );
 	}

	double Future::cptNetFo(Periods t, Rate v)
	{
		return cptNetSo(t, v) * exp ((fr + v) * fn);
	}
	double Future::cptNetSo(Periods t, Rate v)
 	{
		return fSo/ exp( fq * fn) - CashFlowMaster::presentValue(t, v);
 	}
 	
	void Future::UpdateFo()
 	{
		fFo = (cptNetFo(0));
 	}
	void Future::UpdateSo()
 	{
		fSo = (cptNetSo(0));
 	}
 	
}
