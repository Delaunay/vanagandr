#include "CrossCurrency.h"

namespace vanagandr
{
    std::string ExchangeRate::name(Currency b)
    {
        std::string a;

        switch(b)
        {
        case Currency::USD:
            a = "USD";
            break;
        case Currency::EUR:
            a = "EUR";
            break;
        case Currency::JPY:
            a = "JPY";
            break;
        case Currency::GBP:
            a = "GBP";
            break;
        case Currency::CHF:
            a = "CHF";
            break;
        case Currency::CAD:
            a = "CAD";
            break;
        case Currency::AUD:
            a = "AUD";
            break;
        case Currency::NZD:
            a = "NZD";
            break;
        case Currency::ZAR:
            a = "ZAR";
            break;
        case Currency::SEK:
            a = "SEK";
            break;
        case Currency::NOK:
            a = "NOK";
            break;
        case Currency::BRL:
            a = "BRL";
            break;
        case Currency::SGD:
            a = "SGD";
            break;
        case Currency::MXN:
            a = "MXN";
            break;
        case Currency::CNY:
            a = "CNY";
            break;
        case Currency::HKD:
            a = "HKD";
            break;
        case Currency::INR:
            a = "INR";
            break;
        case Currency::KRW:
            a = "KRW";
            break;
        case Currency::RUB:
            a = "RUB";
            break;

        default:
            a = "USD";
            break;
        }

        return a;
    }
}
