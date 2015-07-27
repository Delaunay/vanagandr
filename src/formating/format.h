//#define VANAGANDR_FORMATING_FORMAT_HEADER
#ifndef VANAGANDR_FORMATING_FORMAT_HEADER
#define VANAGANDR_FORMATING_FORMAT_HEADER

#include "../memory/Ptr.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

// Original Design from 'Accelerated C++' by Andrew Koenig and Babara E. Moo
//
// Modification:
// All derived class are defined inside the source file.
// They are not anymore accessible by the user. This is why derived class
// are now fully public and does not required to be 'friend'

// must check if saving height/width val is useful

namespace vanagandr{
namespace formating{

    class PicBase;

    // public Interface
    class StrPicture
    {
        friend std::ostream& operator<< (std::ostream&, const StrPicture& s);
        friend StrPicture frame(const StrPicture& s);
        friend StrPicture vcat(const StrPicture& top, const StrPicture& bot);
        friend StrPicture hcat(const StrPicture& left, const StrPicture& right);

        public:
            typedef std::vector<std::string> vector_string;
            StrPicture(const vector_string& s = vector_string());

        protected:

            StrPicture(PicBase* p); // Constructor used by source code
            memory::Pointer<PicBase> _p;
    };

    StrPicture frame(const StrPicture& s);
    StrPicture vcat(const StrPicture& top, const StrPicture& bot);
    StrPicture hcat(const StrPicture& left, const StrPicture& right);

    std::ostream& operator<< (std::ostream&, const StrPicture& s);

    // One Dimension Scale
    template<class T>
    struct Scale
    {
        Scale():
            min(0), max(0)
        {}

        Scale(const T& mi, const T& mx):
            min(mi), max(mx)
        {
            if (min > max)
            {
                double t = min;
                min = max;
                max = t;
            }
        }

        static Scale vector_scale(const std::vector<T>& v)
        {
            auto i = std::minmax_element(v.begin(), v.end());
            return Scale((*i.first), (*i.second));
        }

        T scale(const T& x, const T& size) const
        {
            return (x - min) * size / (max - min);
        }

        T min;
        T max;
    };


    template<class T>
    StrPicture histogram(const std::vector<T>& v, int size=10)
    {
        typedef typename std::vector<T>::size_type size_t;
        size_t n = v.size();
        Scale<T> s = Scale<T>::vector_scale(v);
        std::vector<std::string> vs(n);

        for(size_t i = 0; i < n; ++i)
        {
            double sz = s.scale(v[i], size);
            bool de = 0; // 0.50 < sz - int(sz) < 1;

            vs[i] = " |"  + std::string(int(sz), '=') + (de? "-": "");

            if (size - sz - de - 1> 0)
                vs[i] += std::string(size - int(sz) - de - 1, ' ');

            vs[i] += "|";
        }

        return vs;
    }

    template<class T>
    StrPicture histogram(const std::vector<T>& v, const Scale<T>& s, int size = 10)
    {
        typedef typename std::vector<T>::size_type size_t;
        size_t n = v.size();
        std::vector<std::string> vs(n);

        for(size_t i = 0; i < n; ++i)
        {
            double sz = s.scale(v[i], size);
            int de = 0 ;//(sz - int(sz)) > 0.50;

            vs[i] = " |"  + std::string(sz, '=') + (de? "-": "");

            vs[i] += std::string(size - sz - de, ' ') + "|";
        }

        return vs;
    }



}
}


#endif
