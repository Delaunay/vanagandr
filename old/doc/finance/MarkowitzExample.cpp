#include <iostream>
#include <vanagandr/finance/Markowitz.h>

using namespace vanagandr;

int main(arv, argc)
{
	Matrix A(4, 4);
	
	// Covariance Matrix
	A(0, 0) = 0.40;	A(0, 1) =  0.03; A(0, 2) = 0.02; A(0, 3) =  0.00;
	A(1, 0) = 0.03;	A(1, 1) =  0.20; A(1, 2) = 0.00; A(1, 3) = -0.06;
	A(2, 0) = 0.02;	A(2, 1) =  0.00; A(2, 2) = 0.30; A(2, 3) =  0.03;
	A(3, 0) = 0.00;	A(3, 1) = -0.06; A(3, 2) = 0.03; A(3, 3) =  0.10;

	// Return Matrix
	ExpectedReturn B(4);
	B(0) = 0.06;
	B(1) = 0.05;
	B(2) = 0.07;
	B(3) = 0.08;

	// Creation of the Object
	Markowitz a(A, B);

	// set Rates
	a.setTarget(0.06);
	a.setRf(0.03);
	a.setRb(0.04);

	cout << "<Weight MV"> 	<< endl;
	cout << a.minimalVariancePortfolio(Markowitz::MinimalVariance) 	<< endl << endl;
	
	cout << "<Weight NORF"> 	<< endl;
	cout << a.minimalVariancePortfolio(Markowitz::NoRiskFree) 		<< endl << endl;
	
	cout << "<Weight BRF"> 	<< endl;
	cout << a.minimalVariancePortfolio(Markowitz::BorrowRiskFree) 	<< endl << endl;
	
	cout << "<Weight BS"> 	<< endl;
	cout << a.minimalVariancePortfolio(Markowitz::BorrowSpecial) 	<< endl << endl;

	cout << "Return of Minimal Variance Port : "<< a.Return(Markowitz::MinimalVariance) << endl;
	cout << "Return of NoRiskFree Port:"		<< a.Return(Markowitz::NoRiskFree) << endl;
	cout << "Return of BorrowRiskFree Port :"	<< a.Return(Markowitz::BorrowRiskFree) << endl ;
	cout << "Return of BorrowSpecial Port :"	<< a.Return(Markowitz::BorrowSpecial) << endl;

	return 0;
}