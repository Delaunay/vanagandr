#include "Security.h"

namespace vanagandr
{
	Security::Security():n_(0), Spread_(0), Rate_(0), Cost_(0),
		Holding_(1), ContractSize_(1), Maturity_(0),
        IssueDate_(0), Name_("Name"), BaseCurrency_(Currency::USD)
	{

	}
	Price Security::cost()
	{
		return Cost_;
	}
	void Security::setCost(Price a)
	{
		Cost_ = a;
	}
	Periods Security::initialMaturity()
	{
		return	Date::n(Date( Maturity_ ), IssueDate_ );
	}
	Periods	Security::currentMaturity(Date today)
	{
		return	Date::n(Date( Maturity_ ), today);
	}
	void Security::setn(Date today)
	{
		n_ = initialMaturity() - currentMaturity(today);
	}
	Rate Security::spread()
	{
		return Spread_;
	}
	Size Security::holding()
	{
		return Holding_;
	}
	Size Security::contractSize()
	{
		return ContractSize_;
	}
	Rate Security::rate()
	{
		return Rate_;
	}
	Posix Security::maturity()
	{
		return Maturity_;
	}
	Posix Security::issueDate()
	{
		return IssueDate_;
	}
	Name Security::name()
	{
		return Name_;
	}
	Periods Security::n()
	{
		return n_;
	}
	void Security::setn(Periods a)
	{
		n_ = a;
	}
	void Security::setSpread(Rate a)
	{
		Spread_ = a;
	}
	void Security::setHolding(Size a)
	{
		Holding_ = a;
	}
	void Security::setContractSize(Size a)
	{
		ContractSize_ = a;
	}
	void Security::setRate(Rate  a)
	{
		Rate_ = a;
	}
	void Security::setMaturity(Posix a)
	{
		Maturity_ = a;
	}
	void Security::setIssueDate(Posix a)
	{
		IssueDate_ = a;
	}
	void Security::setName(Name a)
	{
		Name_ = a;
	}

    void Security::setCurrency(Currency a)
    {
        BaseCurrency_ = a;
    }

    Currency Security::currency()
    {
        return BaseCurrency_;
    }
}

