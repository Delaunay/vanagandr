#ifndef VANAGANDR_CONTAINERS_LINKEDLIST_HEADER
#define VANAGANDR_CONTAINERS_LINKEDLIST_HEADER

#include "../enum.h"
#include "Capacity.h"

#include<tuple>

namespace vanagandr
{
namespace containers
{
/*!
 * Description:
 * ------------
 *
 * Linked list are non contiguous containers (as opposed to vector<> and C style
 * array). Linked list are polyvalent.
 *
 * Usage:
 * ------
 *
 * Linked list are particulary useful when we delete inside the list.
 * (if we need to delete last elements it is better to use compact containers)
 *
 * Complexity:
 * -----------
 *
 * Memory: O(n)   (sizeof(Element) + 2 * sizeof(ptr)) * n
 * Hold 2 pointer and an Element per entry
 *
 * Time:
 *
 *                      Best    Average     Worst
 *      * remove first  O(1)    O(1)        O(1)
 *      * remove last   O(1)    O(1)        O(1)
 *      * push_first    O(1)    O(1)        O(1)
 *      * push_last     O(1)    O(1)        O(1)
 *
 * Moreover, Iterators have non standard methods that allow users to:
 *      * delete the pointed element (O(1))
 *      * insert before/after the pointed element (O(1))
 *
 */
template<typename Element>
class LinkedList
{
protected:
    struct Node
    {
        Node(Element el, Node* n = NULL, Node* p = NULL):
            element(el), next(n), prev(p)
        {}

        Element element;
        Node*   next;
        Node*   prev;
    };

public:

    template<class V>
    struct Iterator
    {
        Iterator(Node * n):
            _position(n)
        {}

        bool     operator== (const Iterator& rhs) const {   return this->_position == rhs._position; }
        void     operator-- () const {  _position = _position->prev;  }
        void     operator++ () const {  _position = _position->next;  }
        V&       operator*  ()       {  return _position->element;    }

        void insert_after(const V& el)
        {
            Node* next = _position.next;
            _position->next = new Node(el, next, _position);
        }

        void insert_before(const V& el)
        {
            Node* prev = _position->prev;
            _position->prev = new Node(el, _position, prev);
        }

        void     remove_element()
        {
            Node* prev = _position->prev;
            prev->next = _position->next;
            delete _position;
            _position = prev->next;
        }

    protected:
        Node* _position;
    };

    typedef Element                     value_type;
    typedef Iterator<value_type>        iterator;
    typedef Iterator<const value_type>  const_iterator;
    typedef std::size_t    size_type;
    typedef Element&       reference;
    typedef const Element& const_reference;

    LinkedList():
        _size(0), _first(nullptr), _last(nullptr)
    {}

    ~LinkedList()
    {
        Node* pos = _first;
        Node* tp;

        while(pos != NULL)
        {
            tp = pos;
            pos = pos->next;

            delete tp;
        }
    }

    void init(const value_type& v)
    {
        _first = _last = new Node(v, nullptr, nullptr);
        _size = 1;
    }

    void push_last(const value_type& v)
    {
        if (_first == nullptr)
            return init(v);

        _last->next = new Node(v, nullptr, _last);
        _last = _last->next;
        ++_size;
    }

    void push_first(const value_type& v)
    {
        if (_first == nullptr)
            return init(v);

        _first->prev = new Node(v, _first, nullptr);
        _first = _first->prev;
        ++_size;
    }

    void remove_first()
    {
        _first = _first->next;
        delete _first->prev;
        _first->prev = nullptr;
    }

    void remove_last()
    {
        _last = _last->prev;
        delete _last->next;
        _last->next = nullptr;
    }

    bool is_empty() const         {   return !_size;  }

    value_type& first()       {   return _first->element; }
    value_type& last ()       {   return _last ->element; }
    const value_type& first() const {   return _first->element; }
    const value_type& last () const {   return _last ->element; }
    const size_type & size () const {   return _size;           }

    iterator begin()    {   return Iterator<value_type>(_first);    }
    iterator end()      {   return Iterator<value_type>(_last);     }

    const_iterator begin() const   {   return Iterator<const value_type>(_first);    }
    const_iterator end()   const   {   return Iterator<const value_type>(_last);     }

    void push_back(const value_type& v) {   return push_last(v);}

    std::string str(unsigned int line = 5) const
    {
        Node* pos = _first;
        std::string s = "    [";
        unsigned int st = 0, en = 0;
        size_type i = 0;

        while(st < line && pos!= NULL)
        {
            s += std::to_string(pos->element) + ", ";

            if (s.length() - en > 80)
            {
                s += "\n     ";
                en = s.length();
                st++;
            }

            i++;

            pos = pos->next;
        }

        if (i < size())
            s += " .... " /*+ std::to_string(_size - i) + " Skipped Elements"*/;

        s += "] \n        (size: " + std::to_string(_size) +
              ", memory: (Node: "  + pretty_print_capacity(sizeof(Node)) + ", Total: "
                                   + pretty_print_capacity(sizeof(Node) * _size) + "))";

        return s;
    }

protected:

    size_type _size;
    Node* _first;
    Node* _last;

};

}
}

#endif
