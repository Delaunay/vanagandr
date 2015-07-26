#ifndef VANAGANDR_CONTAINERS_SORT_HEADER
#define VANAGANDR_CONTAINERS_SORT_HEADER

#include "../enum.h"

#include <map>


// TODO use iterator

namespace vanagandr
{
namespace containers
{

    /*!
     * Sort in ascending order.
     * The default sorting algorithm is heapsort since:
     *      - Quick Sort is kinda random
     *      - Merge sort require additional memory when merging two ordered list
     *      - Counting is quick but it is kinda specific
     *
     *
     * Memory: O(1) Inplace
     *
     * Time: Best        Average      Worst
     *       O(n log n)  O(n log n)   O(n log n)
     */
    template<typename Container, bool reverse = false>
    struct Sort
    {
        typedef typename Container::size_type size_type;
        typedef typename Container::value_type value_type;

        static void sort(Container& ds)
        {
            return heapsort(ds);
        }

        /*!
         * Memory: O(1) Inplace
         *
         * Time: Best        Average      Worst
         *       O(n log n)  O(n log n)   O(n log n)
         */
        static void heapsort(Container& ds)
        {
            size_type n = ds.size();

            // build heap
            for (size_type i = size_type(n / 2) - 1;; i --)
            {
                min_heap(ds, i, n);

                if (i == 0)
                    break;
            }

            //sort
            for (size_type i = n - 1;; i --)
            {
                value_type e = ds[0];
                ds[0] = ds[i];
                ds[i] = e;

                min_heap(ds, 0, i);

                if (i == 0)
                    break;
            }
        }

        /*!
         * Min Heap, Min is in first position
         *
         * Memory: O(1) Inplace
         *
         * Time: O(log n)
         */
        // create a min heap
        static void min_heap(Container& A, const size_type& idx, const size_type& max)
        {
            // put the value idx into the right place
            size_type left  = 2 * idx + 1,
                      right = 2 * idx + 2,
                      sel   = 0;

            if ((left < max) && (A[left] > A[idx]))
                sel = left;
            else
                sel = idx;

            if ((right < max) && (A[right] > A[sel]))
                sel = right;

            if (sel != idx)
            {
                value_type e = A[idx];
                A[idx] = A[sel];
                A[sel] = e;

                min_heap(A, sel, max);
            }
        }

        /*!
         * Max Heap, Max is in first position
         *
         * Memory: O(1) Inplace
         *
         * Time: O(log n)
         */
        static void max_heap(Container& A, const size_type& idx, const size_type& max)
        {
            // put the value idx into the right place
            size_type left  = 2 * idx + 1,
                      right = 2 * idx + 2,
                      sel   = 0;

            if ((left < max) && (A[left] < A[idx]))
                sel = left;
            else
                sel = idx;

            if ((right < max) && (A[right] < A[sel]))
                sel = right;

            if (sel != idx)
            {
                value_type e = A[idx];
                A[idx] = A[sel];
                A[sel] = e;

                max_heap(A, sel, max);
            }
        }

    };


    template<typename Container>
    struct Sort<Container, true>
    {
        typedef typename Container::size_type size_type;
        typedef typename Container::value_type value_type;

        static void sort(Container& ds)
        {
            return heapsort(ds);
        }

        static void heapsort(Container& ds)
        {
            size_type n = ds.size();

            // build heap
            for (size_type i = size_type(n / 2) - 1;; i --)
            {
                Sort<Container, false>::max_heap(ds, i, n);

                if (i == 0)
                    break;
            }

            //sort
            for (size_type i = n - 1;; i --)
            {
                value_type e = ds[0];
                ds[0] = ds[i];
                ds[i] = e;

                Sort<Container, false>::max_heap(ds, 0, i);

                if (i == 0)
                    break;
            }
        }
    };


}
}

#endif
