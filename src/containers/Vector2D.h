#ifndef VANAGANDR_CONTAINERS_VECTOR2D_HEADER
#define VANAGANDR_CONTAINERS_VECTOR2D_HEADER

#include <vector>
#include <ostream>

#include "../error/Error.h"

namespace vanagandr{
namespace containers{

    // row major
    // I dont think this container is useful Eigen::Matrix
    // must be better
    // rows and cols can be sorted independently
    template<class T>
    class Vector2D
    {
    public:
        typedef typename std::vector<T>::size_type size_type;
        typedef typename std::vector<T>::value_type value_type;
        typedef typename std::vector<T>::iterator iterator;
        typedef typename std::vector<T>::const_iterator const_iterator;

        Vector2D(const size_type&  rows, const size_type&  cols):
            _data(rows * cols), _rows(rows), _cols(cols)
        {}

        const value_type& operator() (const size_type& x, const size_type& y) const
        {
            VTHROW(x >= _rows && y >= _cols, std::domain_error, " Index out of bound");
            return _data[x * _cols + y];
        }

        value_type& operator() (const size_type& x, const size_type& y)
        {
            VTHROW(x >= _rows && y >= _cols, std::domain_error, " Index out of bound");
            return _data[x * _cols + y];
        }

        inline value_type rows()   {   return _rows;   }
        inline value_type cols()   {   return _cols;   }

        void resize_rows(const size_type&  rows)
        {
            if (rows > _rows)
                add_rows(rows - _rows);
            else
                del_rows(_rows - rows);
        }

        void resize_cols(const size_type&  cols)
        {
            if (cols > _cols)
                add_cols(cols - _cols);
            else
                del_cols(_cols - cols);
        }

        // I dont know which way would be faster
        void resize(const size_type&  rows, const size_type&  cols)
        {
            if (cols != _cols)
                resize_cols(cols);

            if (rows != _rows)
                resize_rows(rows);
        }

        void add_rows(const size_type& rows = 1)
        {
            _data.resize(_rows * _cols + rows * _cols);
            _rows += rows;
        }

        void del_rows(const size_type& rows = 1)
        {
            _data.resize(_rows * _cols - rows * _cols);
            _rows -= rows;
        }

        void add_cols(size_type cols = 1)
        {
            cols = _cols + cols;
            std::vector<T> temp(_rows * cols);

            for(size_type i = 0; i < _rows; ++i)
                for(size_type j = 0; j < _cols; ++j)
                    temp[i * cols + j] = (*this)(i, j);

            _cols = cols;
            _data = temp;
        }

        void del_cols(size_type cols = 1)
        {
            cols = _cols - cols;
            std::vector<T> temp(_rows * cols);

            for(size_type i = 0; i < _rows; ++i)
                for(size_type j = 0; j < cols; ++j)
                    temp[i * cols + j] = (*this)(i, j);

            _cols = cols;
            _data = temp;
        }

        void print(std::ostream& os)
        {
            for(size_type i = 0; i < _rows; ++i)
            {
                for(size_type j = 0; j < _cols; ++j)
                    os << (*this)(i, j) << " ";
                os << "\n";
            }
        }

        // Matrix to_matrix() Eigen::Map<>
        // Array to_array() Eigen::Map<>

        iterator begin() {  return _data.begin();   }
        const_iterator begin() const {  return _data.begin();   }

        iterator end() {  return _data.end();   }
        const_iterator end() const {  return _data.end();   }

    protected:
        std::vector<T> _data;
        size_type _rows;
        size_type _cols;
    };

    template<class T>
    struct V2DRow
    {
        typedef typename Vector2D<T>::size_type size_type;
        typedef typename Vector2D<T>::value_type value_type;
        typedef typename Vector2D<T>::iterator iterator;
        typedef typename Vector2D<T>::const_iterator const_iterator;

        // bool operator ==

        V2DRow(const size_type& r, Vector2D<T>& v):
            _v(v), _row(r)
        {
            VTHROW(r >= _v.rows(), std::domain_error, " Index out of bound");
        }

        value_type& operator[] (const size_type& t)
        {
            VTHROW(t >= _v.cols(), std::domain_error, " Index out of bound");
            return _v(_row, t);
        }

        iterator begin() {  return _v.begin() + _row * _v.cols();          }
        iterator end()   {  return std::min(_v.begin() + (_row  + 1) * _v.cols(),
                                            _v.end());   }

        size_type size() const    {   return _v.rows();   }

    protected:
        Vector2D<T>& _v;
        const size_type _row;
    };

    // row major
    // no Col iterator
    template<class T>
    struct V2DCol
    {
        typedef typename Vector2D<T>::size_type size_type;
        typedef typename Vector2D<T>::value_type value_type;

        V2DCol(const size_type& c, Vector2D<T>& v):
            _v(v), _col(c)
        {
            VTHROW(c >= _v.cols(), std::domain_error, " Index out of bound");
        }

        value_type& operator[] (const size_type& t)
        {
            VTHROW(t >= _v.rows(), std::domain_error, " Index out of bound");
            return _v(t, _col);
        }

        size_type size() const    {   return _v.cols();   }

    protected:
        Vector2D<T>& _v;
        const size_type _col;
    };

}
}

#endif
