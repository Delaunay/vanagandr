#include <iostream>
#include <vanagandr/finance/CashFlows.h>

using namespace vanagandr;

int main(arv, argc)
{
    Rate	  MyWACC = 0.10;
    // Creation of a serie of Cash Flow (NPV, Bond, ..)
    CashFlowMaster<CashFlow> MyCashFlows; 

    MyCashFlows.add(CashFlow(0, MyWACC, -100000));

    MyCashFlows.add(CashFlow(1, MyWACC, +5000));
    MyCashFlows.add(CashFlow(2, MyWACC, +25000));
    MyCashFlows.add(CashFlow(3, MyWACC, +25000));
    MyCashFlows.add(CashFlow(4, MyWACC, +50000));

    std::cout << "NPV (i + 1\%) : \t" << MyCashFlows.presentValue(0,  0.01) << std::endl;
    std::cout << "NPV (i + 0\%) : \t" << MyCashFlows.presentValue(0,  0.00) << std::endl;
    std::cout << "NPV (i - 1\%) : \t" << MyCashFlows.presentValue(0, -0.01) << std::endl;

    std::cout << "IRR : \t" << MyCashFlows.yieldToMaturity() << std::endl;

    return 0;
}