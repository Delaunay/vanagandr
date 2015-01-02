#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum Style
{
    Boxerrorbars,
    Boxes,
    Boxplot,
    BoxXYerrorbars,
    Candlesticks,
    Circles,
    Ellipses,
    Dots,
    FilledCurves,
    Financebars,
    Fsteps,
    Fillsteps,
    Histeps,
    Histograms
};

enum LegendPosition
{
    TopRight,
    TopLeft,
    BottomRight,
    BottomLeft
};

class Drawing
{
public:


protected:

};

/*!
 * \brief map C++ data to a gnuplot script : made to generate gnuplot script without touching gnuplot (compile reverse =_=)
 * this map a Single plot
 * multiplot will be implemented in a layout class
 */

class Plot
{
public:
    struct Point
    {
        double x;
        double y;
    };

    struct Size
    {
        int w;
        int h;
    };

    struct Label
    {
        double x;
        double y;
        string label;
    };



    Plot()
    {}

    // attributes
    void addLines();
    void addLabel();

    void addLabel(Label);
    void addLabel(string label, Point coord);
    void addLabel(string label, double x, double y);

    void    setSize(int w, int h);

    Size&   size()   {  return _Size;   }
    string& ylabel() {  return _yLabel; }
    string& xlabel() {  return _xLabel; }
    string& title () {  return _Title;  }

    // generate gnuplot script and return it back as a string
    string generate_string()
    {
        stringstream s;

        s << "set style data" << "lines"  << " \n"
             "set ylabel \""  << ylabel() << "\" \n"
             "set xlabel \""  << xlabel() << "\" \n"
             "set title \""   << title()  << "\" \n"
             ;

        for (int i = 0, n = _Label.size(); i < n; i++)
            s << "set label \"" << _Label[i].label <<
                       "\" at " << _Label[i].x     <<
                            "," << _Label[i].y << " \n";

        return s.str();
    }

protected:

    Size            _Size;
    DataStyle       _DataStyle;
    string          _yLabel;
    string          _xLabel;
    string          _Title;
    vector<Label>   _Label;

};
