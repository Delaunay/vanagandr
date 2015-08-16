#include <iostream>
#include <vanagandr/finance/CashFlows.h>

using namespace vanagandr;

int main(arv, argc)
{
    // Creation of a serie of Cash Flow (NPV, Bond, ..)
    CashFlowMaster<CashFlow> MyBond;
            
    // Creation of a YieldCurve
    YieldCurve MyTermStructure;		

    // adding rate to the yield Curve
    // add( Yield( Date, Rate) )
    MyTermStructure.add(Yield(  1, 0.02)); 
    MyTermStructure.add(Yield(  2, 0.03));
    MyTermStructure.add(Yield(  4, 0.04));
    MyTermStructure.add(Yield(  8, 0.05));
    MyTermStructure.add(Yield( 16, 0.06));
    MyTermStructure.add(Yield( 32, 0.07));

    // add the coupon payment to the bond
    for( unsigned int i = 1; i <= 19; i++)
        MyBond.add(CashFlow(i, 0, 50);

    // add the last payment plus de capital 
    MyBond.add(CashFlow(20, 0, 1000 + 50));

    // Update discounting rate
    MyBond.setToSpot(&MyTermStructure);

    // print info wanted
    std::cout << "Pv (i + 1\%) : \t" << MyBond.presentValue(0,  0.01) << std::endl;
    std::cout << "Pv (i + 0\%) : \t" << MyBond.presentValue(0,  0.00) << std::endl;
    std::cout << "Pv (i - 1\%) : \t" << MyBond.presentValue(0, -0.01) << std::endl;

    std::cout << "Duration : \t" << MyBond.duration() << std::endl;
    std::cout << "Convexity: \t" << MyBond.convexity() << std::endl;

    std::cout << "YTM : \t" << MyBond.yieldToMaturity() << std::endl;

    return 0;
}
