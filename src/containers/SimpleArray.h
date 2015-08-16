#ifndef VANAGANDR_CONTAINERS_SIMPLEARRAY_HEADER
#define VANAGANDR_CONTAINERS_SIMPLEARRAY_HEADER

#include <memory>
#include "Capacity.h"
#include "../error/Error.h"

namespace vanagandr
{
namespace containers
{

/*!
 * Description:
 * ------------
 *
 * A simple contiguous (compact) Array similar to std::vector most likely less efficient
 * This is one of the simpliest array structure and one of the most used.
 * You can enable throw/assert if you want.
 *
 * Usage:
 * ------
 *
 *  // pre allocate 32 int without initializing them (/!\ different from std::vector)
 *  SimpleArray<int> a(32);
 *
 *  // initialize 32 int to 0
 *  SimpleArray<int> b(32, 0);
 *
 * Complexity:
 * -----------
 *
 * Memory: O(n)
 *
 * Time:
 *
 *                      Best    Average     Worst
 *      * insert        O(1)                O(n²) *
 *      * remove_last   O(1)    O(1)        O(1)
 *      * get_item[]    O(1)    O(1)        O(1)
 *
 *  * Amortized worst case is O(n)
 *
 * TODO
 * -------
 *      * implement move operation
 *
 */

#ifndef VANAGANDR_SIMPLEARRAY_GROW_POLICY
#define VANAGANDR_SIMPLEARRAY_GROW_POLICY(old_cap) old_cap * 2
#endif

// Safe clause make SimpleArray correct wrong input
#if VANAGANDR_SIMPLEARRAY_SAFE
#   define SAFE_GETITEM(idx)    return _array[idx % size()]
#   define SAFE_REMOVE()        if (_last == _array) return
#   define SAFE_RESERVE(x, m)   x = std::max(x, m)
#else
#   define SAFE_GETITEM(idx)
#   define SAFE_REMOVE()
#   define SAFE_RESERVE(x, m)
#endif

template<typename Element>
class SimpleArray
{
public:
    typedef Element*       iterator;
    typedef const Element* const_iterator;
    typedef std::size_t    size_type;
    typedef Element        value_type;
    typedef Element&       reference;
    typedef const Element& const_reference;
    typedef std::ptrdiff_t ptr_diff;

    // Having a power of two as default value will make capacity look pretty =D
    // Memory is cheap. Allocate some memory by default
    SimpleArray(size_type n = 32):
        _array(nullptr), _last(nullptr), _capacity(nullptr)
    {
        _array = _allocator.allocate(n);
        _last = _array;
        _capacity = _array + n;
    }

    // Explicit prevent the compiler from using the constructor when it is not
    // explicitly called
    explicit SimpleArray(size_type n, const value_type& val):
        _array(nullptr), _last(nullptr), _capacity(nullptr)
    {
        _array = _allocator.allocate(n);
        _capacity = _last =  _array + n;
        std::uninitialized_fill(_array, _last, val);
    }

    SimpleArray(const SimpleArray& v):
        _array(nullptr), _last(nullptr), _capacity(nullptr)
    {
        reallocate_memory(v.size(), v.begin(), v.end());
    }

    SimpleArray& operator=(const SimpleArray& v)
    {
        if (&v != this)
            // copy into a new vector
            // free current vector
            reallocate_memory(v.size(), v.begin(), v.end());

        return *this;
    }

    ~SimpleArray()
    {
        free_memory();
    }

    value_type& operator[] (const size_type& idx)
    {
        SAFE_GETITEM(idx);
        VTHROW(idx > size(), std::domain_error, " Index out of bound");
        return _array[idx];
    }

    value_type&       last()        {   return *(_last - 1);   }
    const value_type& last()  const {   return *(_last - 1);   }

    const value_type& operator[] (const size_type& idx) const
    {
        SAFE_GETITEM(idx);
        VTHROW(idx > size(), std::domain_error, " Index out of bound");
        return _array[idx];
    }

    void push_back(const value_type& a)
    {
        if (_last == _capacity)
            reallocate_memory(VANAGANDR_SIMPLEARRAY_GROW_POLICY(capacity()));

        _allocator.construct(_last++, a);
    }

    // Remove last
    void remove_last()
    {
        SAFE_REMOVE();
        VTHROW(_last == _array, std::domain_error, " Cant remove last Element: Array is Empty");
        _allocator.destroy(_last--);
    }

    std::string str(unsigned int line = 5)
    {
        std::string s = "    [";

        unsigned int st = 0, en = 0;
        size_type i = 0;

        while(st < line && i < size())
        {
            s += std::to_string(_array[i]) + ", ";

            if (s.length() - en > 80)
            {
                s += "\n     ";
                en = s.length();
                st++;
            }

            i++;
        }

        if (i < size())
            s += " .... " /*+ std::to_string(_size - i) + " Skipped Elements"*/;

        s += "] \n        (size: " + std::to_string(size()) +
                ", capacity: " + std::to_string(capacity()) +
                ", memory:(Element: " + pretty_print_capacity(sizeof(value_type)) +
                           ", Used: " + pretty_print_capacity(sizeof(value_type) * size()) +
                          ", Total: " + pretty_print_capacity(sizeof(value_type) * capacity()) +
                       /*", Overhead: " + pretty_print_capacity(sizeof(SimpleArray<value_type>)) +*/ "))";

        return s;
    }

    bool      is_empty() const  {   return _array == _last;      }
    size_type size()     const  {   return _last - _array;       }
    size_type capacity() const  {   return _capacity - _array;   }

    iterator       begin()       {  return _array;   }
    const_iterator begin() const {  return _array;   }

    iterator       end()       {    return _last;    }
    const_iterator end() const {    return _last;    }

    void           reserve(size_t n)
    {
        SAFE_RESERVE(n, size());
        VTHROW(size() > n, std::domain_error, "Not enough reserved space to copy");
        reallocate_memory(n);
    }

    void shrink()   {   reallocate_memory(size());  }

protected:

    iterator _array;
    iterator _last;
    iterator _capacity;

    std::allocator<value_type> _allocator;

    void reallocate_memory(size_t n, iterator beg, iterator end)
    {
        // I am thinking about del those two
        // SAFE_RESERVE(n, end - beg);
        // VASSERT(end - beg < n && " Reallocation Error, Not enough space to copy");

        value_type* new_array = _allocator.allocate(n);

        std::uninitialized_copy(beg, end, new_array);

        free_memory();

        _array = new_array;
        _last = _array + (end - beg);
        _capacity = new_array + n;
    }
    void reallocate_memory(size_t n)    {   return reallocate_memory(n, _array, _last);   }

    void free_memory()
    {
        if (_array)
        {
            for(auto i = _last; i != _array; --i)
                _allocator.destroy(i);

            _allocator.deallocate(_array, capacity());
        }

        _array = _last = _capacity = 0;
    }
};

}
}

#endif
