#ifndef VANAGANDR_CONTAINERS_TYPE_HEADER
#define VANAGANDR_CONTAINERS_TYPE_HEADER

#include <iosfwd>
//#include <iostream>
#include <string>


namespace vanagandr{

/*!
 * Define new types that can be used inside Eigen::Array/Eigen::Matrix
 */
namespace type {

enum Day
{
    Mon = 1,
    Tue = 2,
    Wed = 3,
    Thu = 4,
    Fri = 5,
    Sar = 6,
    Sun = 7
};

enum Month
{
    Jan =  1,
    Feb =  2,
    Mar =  3,
    Apr =  4,
    May =  5,
    Jun =  6,
    Jul =  7,
    Aug =  8,
    Sep =  9,
    Oct = 10,
    Nov = 11,
    Dec = 12
};

enum Format
{
    DDMMYYYY,
    YYYYMMDD
};

// some operation might seem ... unusual
// they are implemented so we can insert Date into Eigen Matrix/Array
template<typename DateType>
struct Date
{
    Date(DateType m = 0):
        day(0), month(0), year(0)
    {}

    Date(DateType day, DateType month, DateType year):
        day(day), month(month), year(year)
    {}

    // 31-12-1992
    Date(std::string date, Format fmt = DDMMYYYY)
    {}

    // need to determine working days

    bool operator< (const Date& b)
    {
        if (this->year < b.year)
            return true;

        if (this->year > b.year)
            return false;

        if (this->month < b.month)
            return true;

        if (this->month > b.month)
            return false;

        if (this->day < b.day)
            return true;

        if (this->day > b.day)
            return false;
    }

    bool operator> (const Date& b)    {   return ! *this <  b; }
    bool operator>=(const Date& b)
    {
        return (*this > b) || (*this == b);
    }

    bool operator<=(const Date& b)    {   return ! *this >= b; }
    bool operator==(const Date& b)
    {
        return (this->day   == b.day  ) &&
               (this->month == b.month) &&
               (this->year  == b.year );
    }

    Date<DateType>& operator+=(const Date& b)
    {
        *this = *this + b;
        return *this;
    }

    Date<DateType>& operator-=(const Date& b)
    {
        *this = *this - b;
        return *this;
    }

    Date<DateType>& operator/=(const Date& b)
    {
        *this = *this / b;
        return *this;
    }

    Date<DateType>& operator*=(const Date& b)
    {
        *this = *this * b;
        return *this;
    }

    DateType day;
    DateType month;
    DateType year;
};

template<typename DateType> inline Date<DateType> operator+ (const Date<DateType>& a, const Date<DateType>& b)
{
    return Date<DateType>(a.day + b.day, a.month + b.month, a.year + b.year);
}

template<typename DateType> inline Date<DateType> operator- (const Date<DateType>& a, const Date<DateType>& b)
{
    return Date<DateType>(a.day - b.day, a.month - b.month, a.year - b.year);
}

template<typename DateType> inline Date<DateType> operator* (const Date<DateType>& a, const Date<DateType>& b)
{
    return Date<DateType>(a * b);
}

template<typename DateType> inline Date<DateType> operator/ (const Date<DateType>& a, const Date<DateType>& b)
{
    return Date<DateType>(a / b);
}



template<typename TimeType>
class Time
{
public:

    Time(TimeType tt):
        hours(tt / 3600), minutes((tt % 3600) / 60), seconds(((tt % 3600) % 60))
    {}

    Time(TimeType h, TimeType m, TimeType s):
        hours(h), minutes(m), seconds(s)
    {}

    // 23:59:59
    Time(std::string t)
    {}

    TimeType hours;
    TimeType minutes;
    TimeType seconds;
};

template<typename DateType>
int month_length(const Month& m)
{
    switch(m)
    {
    case Jan:
        return 31;
    case Feb:
        return 28; // 29
    case Mar:
        return 31;
    case Apr:
        return 30;
    case May:
        return 31;
    case Jun:
        return 30;
    case Jul:
        return 31;
    case Aug:
        return 31;
    case Sep:
        return 30;
    case Oct:
        return 31;
    case Nov:
        return 30;
    case Dec:
        return 31;
    }
}


template <typename DateType>
inline std::ostream &operator<<(std::ostream &s, const Date<DateType>& d)
{
    return s << d.day << "-" << d.month << "-" << d.year;
}

template <typename TimeType>
inline std::ostream &operator<<(std::ostream &s, const Time<TimeType>& d)
{
    return s << d.hours << ":" << d.minutes << ":" << d.seconds;
}

}

}

#include "eigen3/Eigen/Core"

namespace Eigen {

// Creating a specialization of NumTraits enables placing Dates objects inside
template <typename DateType>
struct NumTraits<vanagandr::type::Date<DateType> >
{
    typedef vanagandr::type::Date<DateType> Real;
    typedef vanagandr::type::Date<DateType> NonInteger;
    typedef vanagandr::type::Date<DateType> Nested;

    static typename vanagandr::type::Date<DateType> dummy_precision()
    {
        return Real(1e-12);
    }

    static inline Real epsilon()
    {
        return Real(std::numeric_limits<DateType>::epsilon());
    }

    enum
    {
        IsComplex = 0,
        IsInteger = 1,
        IsSigned,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 3,
        HasFloatingPoint = 0,
        RequireInitialization = 1
    };

};

}

#endif
