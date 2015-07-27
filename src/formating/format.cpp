#include "format.h"
#include <ostream>

namespace vanagandr{
namespace formating{

using namespace std;
using namespace memory;

typedef StrPicture::vector_string vector_string;

// internal class
struct PicBase
{
    typedef vector_string::size_type height_type;
    typedef string::size_type      width_type;

    virtual ~PicBase()
    {}

    virtual height_type height() const = 0;
    virtual width_type  width () const  = 0;
    virtual void display(ostream& os, int row, bool add_pad = true) const= 0;

    static ostream& pad(ostream& os, int s)
    {
        for(int i = 0; i < s; ++i)
            os << " ";

        return os;
    }

};

struct StringPic: public PicBase
{
    StringPic(const vector_string& d):
        data(vector_string(d))
    {}

    height_type height() const     {   return data.size(); }
    width_type  width () const
    {
        width_type mx = 0;

        for(auto i = 0; i < data.size(); ++i)
            mx = std::max(mx, data[i].size());

        return mx;
    }

    void display(ostream& os, int row, bool add_pad = true) const
    {
        int s = 0;
        if (row < data.size())
        {
            os << data[row];
            s = data[row].size();
        }

        if (add_pad)
            pad(os, width() - s);
    }

    // copied data
    vector_string data;
};

struct FramePic: public PicBase
{
    FramePic(const Pointer<PicBase>& d):
        data(d)
    {}

    height_type height() const     {   return data->height() + 4; }
    width_type  width () const     {   return data->width() + 4; }
    void display(ostream& os, int row, bool add_pad = true) const
    {
        if (row >= height())
        {
            if (add_pad)
                pad(os, width());
        }
        else
        {
            if (row == 0 || row == height() - 1)
            {
                os << string(width(), '*');
            }
            else if (row == 0 || row == height() - 1)
            {
                os << "*";
                pad(os, width());
                os << "*";
            }
            else
            {
                os << "* ";
                data->display(os, row - 2, true);
                os << " *";
            }
        }
    }

    Pointer<PicBase> data;
};

struct VCatPic: public PicBase
{
    VCatPic(const Pointer<PicBase>& t, const Pointer<PicBase>& b):
        top(t), bottom(b)
    {}

    height_type height() const     {   return top->height() + bottom->height();    }
    width_type  width () const     {   return max(top->width(), bottom->width());   }

    void display(ostream& os, int row, bool add_pad = true) const
    {
        width_type w = 0;
        if (row < top->height())
        {
            top->display(os, row, add_pad);
            w = top->width();
        }
        else if (row < height())
        {
            bottom->display(os, row - top->height(), add_pad);
            w = bottom->width();
        }

        if (add_pad)
            pad(os, width() - w);
    }

    Pointer<PicBase> top, bottom;
};

struct HCatPic: public PicBase
{
    HCatPic(const Pointer<PicBase>& l, const Pointer<PicBase>& r):
        left(l), right(r)
    {}

    height_type height() const {   return max(left->height(), right->height()); }
    width_type  width () const {   return left->width() + right->width();   }

    void display(ostream& os, int row, bool add_pad = true) const
    {
        left->display(os, row, add_pad || row < right->height());
        right->display(os, row, add_pad);
    }

    Pointer<PicBase> left, right;
};


StrPicture frame(const StrPicture& s)
{
    return new FramePic(s._p);
}

StrPicture vcat(const StrPicture& top, const StrPicture& bot)
{
    return new VCatPic(top._p, bot._p);
}

StrPicture hcat(const StrPicture& left, const StrPicture& right)
{
    return new HCatPic(left._p, right._p);
}

StrPicture::StrPicture(const vector_string &v):
    _p(new StringPic(v))
{}

StrPicture::StrPicture(PicBase* p):
    _p(p)
{}

std::ostream& operator<< (std::ostream& os, const StrPicture& s)
{
    PicBase::height_type ht = s._p->height();

    for(PicBase::height_type i = 0; i != ht; ++i)
    {
        s._p->display(os, i, false);
        os << endl;
    }

    return os;
}

}}
