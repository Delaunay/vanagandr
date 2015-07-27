#ifndef VANAGANDR_CONTAINERS_STACK_HEADER
#define VANAGANDR_CONTAINERS_STACK_HEADER

#include "../enum.h"
#include "LinkedList.h"
#include "SimpleArray.h"

namespace vanagandr
{
namespace containers
{
template<typename Element>
class StackNoCompact
{
public:

    StackNoCompact():
        _linkedlist()
    {}

    typedef Element        value_type;
    typedef std::size_t    size_type;
    typedef Element&       reference;
    typedef const Element& const_reference;

    void push(const_reference a)  {   return _linkedlist.push_first(a);      }
    void pop()                    {   return _linkedlist.remove_first();     }
    std::string str() const       {   return _linkedlist.str();       }
    const size_type& size() const {   return _linkedlist.size();      }

    bool            is_empty() const {   return _linkedlist.is_empty(); }
    const_reference top() const      {   return _linkedlist.first();    }
    reference       top()            {   return _linkedlist.first();    }

protected:

    LinkedList<Element, Index> _linkedlist;
};

// this implementation must be better that the non compact
// use less memory and is faster than the Linkedlist stack
template<typename Element>
class StackCompact
{
public:

    StackCompact(std::size_t n = 32):
        _list(n)
    {}

    typedef Element        value_type;
    typedef std::size_t    size_type;
    typedef Element&       reference;
    typedef const Element& const_reference;

    void        push(const value_type& a)  {   return _list.push_back(a);      }
    void        pop ()                     {   return _list.remove_last();     }

    const size_type&    size    () const {   return _list.size();      }
    bool                is_empty() const {   return _list.is_empty();  }

    value_type&       top()         {   return _list.last();    }
    const value_type& top() const   {   return _list.last();    }
    std::string       str()         {   return _list.str();     }

    void shrink()   {   _list.shrink(); }

protected:

    SimpleArray<Element> _list;
};

}
}

#endif
