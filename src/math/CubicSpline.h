#ifndef VANAGANDR_MATH_CUBICSPLINE_HEADER
#define VANAGANDR_MATH_CUBICSPLINE_HEADER

#include "../enum.h"

namespace vanagandr {

    // add vector equivalent

    Column cubic_spline(const double* x,
                        const double* fx, unsigned int size,
                        const double* t, unsigned int n = 1)
    {
        Column B = Column::Zero(size);

        for(Index i = 1; i < n - 1; ++i)
            B(i) = ((fx[i + 1] - fx[i]) / (x[i + 1] - x[i]) - (fx[i] - fx[i - 1]) / (x[i] - x[i - 1])) * 6;

        //  Equation System
        // =====================

        Matrix A = Matrix::Zero(size, size);

        A(1, 1) = 1;
        A(size - 1, size - 1) = 1;

        for(Index i = 1; i < n - 1; ++i)
        {
            A(i, i - 1) = (x[i] - x[i - 1]);
            A(i, i + 1) = (x[i + 1] - x[i]);
            A(i, i) = (A(i, i - 1) + A(i, i + 1)) * 2;
        }

        //  Derivatives
        // =====================

        Column S = A.solve(B);               // Second
        Column P = Column::Zero(size - 1);   // First
        Column T = Column::Zero(size - 1);   // Third

        for(Index i = 0; i < size - 1; ++i)
        {
            P(i) = (fx[i + 1] - fx[i]) / (x[i + 1] - x[i])
                 -  (x[i + 1] - x[i]) * S(i) / 3
                 -  (x[i + 1] - x[i]) * S(i + 1) / 6;

            T(i) = (S(i + 1) - S(i)) / (x[i + 1] - x[i]);
        }

        //  Solution
        // =====================

        Column k = Column::Zero(n);

        for(Index j = 0; j < n; ++j)
        {
            Index l = 0;

            for(Index i = 0; i < size - 1; ++i)
            {
                if (t[j] >= x[i])
                    l = i;
                else
                    break;
            }

            k(l) = fx[l]
                 + P(l) *    (t[j] - x[l])
                 + S(l) * pow(t[j] - x[l], 2) / 2
                 + T(l) * pow(t[j] - x[l], 3) / 6;

        }

        return k;
    }


}


#endif
