#ifndef VANAGANDR_FORMATING_STRTABLE_HEADER
#define VANAGANDR_FORMATING_STRTABLE_HEADER

#include <ostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

namespace vanagandr{

template<typename T>
struct Formating
{
    // Compute the number of char needed
    // to print out a numeric type of base 10
    static unsigned int char_size(const T& val, const unsigned int dec)
    {
        return int(log10(val)) + 1;
    }

    static T trunc(const T& val, const unsigned int& size=2)
    {
        const double m = pow(10.0, double(size));
        return int(val * m) / m;
    }

    // cut a value into a smaller string representation
    static ostream& cut(ostream& is, const T& val, const unsigned int& size, const unsigned int dec=2)
    {
        is << trunc(val, dec);
        return is;
    }

    // is       : output
    // val      : value
    // col_size : column size
    // c        : filling char
    // dec      : number of decimal
    static ostream& align_left(ostream& is, const T& val, unsigned int col_size, char c = ' ', const unsigned int dec=2)
    {
        unsigned int t = col_size - char_size(val, dec);
        if (t > 0)
            is << trunc(val, dec) << string(t, c) << "\n";
        else
            is << cut(is, val, col_size, dec) << "\n";

        return is;
    }

    static ostream& align_right(ostream& is, const T& val, unsigned int col_size, char c = ' ', const unsigned int dec=2)
    {
        unsigned int t = col_size - char_size(val, dec);
        if (t > 0)
            is << string(t, c) << trunc(val, dec) << "\n";
        else
            is << cut(is, val, col_size, dec) << "\n";

        return is;
    }

    static ostream& align_center(ostream& is, const T& val, unsigned int col_size, char c = ' ', const unsigned int dec=2)
    {
        unsigned int t = col_size - char_size(val, dec);
        if (t > 0)
            is << string(t / 2, c)
               << trunc(val, dec)
               << string(t % 2 == 0 ? t / 2 : t / 2 + 1, c) << "\n";
        else
            is << cut(is, val, col_size, dec) << "\n";

        return is;
    }


};

template<>
ostream& Formating<string>::cut(ostream& is, const string& val, const unsigned int& size, const unsigned int dec)
{
    for (unsigned int i = 0; i < size; i++)
        is << val[i];

    return is;
}

template<>
unsigned int Formating<string>::char_size(const string& val, const unsigned int dec)
{
    return val.size();
}

template<>
unsigned int Formating<double>::char_size(const double& val, const unsigned int dec)
{
    double v = val - int(val);

    // not an integer
    if (v != 0)
    {
        return int(log10(val)) + 2 + dec;
    }

    // integer
    return int(log10(val)) + 1;
}

template<>
string Formating<string>::trunc(const string& val, const unsigned int& size)
{
    return val;
}

}


#endif
