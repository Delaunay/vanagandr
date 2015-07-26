#ifndef TIMECOVARIANCE_H
#define TIMECOVARIANCE_H

#include "../Enum.h"

namespace vanagandr
{
    enum LagLead
    {
      Lag,
      Lead
    };

    typedef Eigen::MatrixX2d Couple;

    Couple decale(Couple A, int row, LagLead a)
    {
        int n = A.rows() - abs(row);
        int m = A.cols();

        Matrix B(n, m);

        if (a == Lead)
           for(int i = 0; i < n; i++)
           {
               B(i, 0) = A(i, 0);
               B(i, 1) = A(i + row, 1);
           }
        else
            for(int i = 0; i < n; i++)
            {
                B(i, 0) = A(i + row, 0);
                B(i, 1) = A(i, 1);
            }

        return B;
    }

   /* Eigen::Array22d covariance(Couple A,  ID t, LagLead a)
    {
        A = decale(A, t, a);

        int n = A.rows();
        int m = A.cols();

        Matrix E = average(A);
        Matrix B(n, m);

        for (int i = 0; i < n ; i++)
            for (int j = 0; j < m; j++)
                B(i, j) = A(i, j) - E(i, 0);

        return ( B * B.transpose())/ m;
    }

    Eigen::Array22d correlation(Couple A,  ID t, LagLead a)
    {
       Eigen::Array22d B = covariance(A);

       B(0, 1) = B(0, 1)/ pow( B(0, 0) * B(1, 1), 0.5);

       B(0, 0) = 1;
       B(1, 1) = 1;

       B(1, 0) = B(0, 1);

       return B;
    }*/
}

#endif // TIMECOVARIANCE_H
