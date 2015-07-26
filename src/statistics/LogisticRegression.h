#ifndef VANAGANDR_STATISTIC_LOGISTICREG_HEADER
#define VANAGANDR_STATISTIC_LOGISTICREG_HEADER

#include "../enum.h"
#include "../math/Matrix.h"

namespace vanagandr
{
namespace statistics
{


class LogisticRegression
{

public:

    static double sigmoid(double x)
    {
        return 1.0/ (1.0 + exp(-x));
    }

    // Theta (n x 1)
    // X     (m x n)
    // Y     (m x 1)
    static double cost(const Matrix& theta, const Matrix& X, const Matrix& Y)
    {
        Matrix x = X * theta;
        return ((
                (1.0 - Y.transpose().array()).matrix() * x)(0, 0) +
                (1.0 + (- x).array().exp()).log().sum()
               ) / X.rows();
    }

    static Matrix gradient(const Matrix& theta, const Matrix& X, const Matrix& Y)
    {
        //      (mxn) => (nxm)   (mxn) * (n x 1) - (m * 1)
        // .unaryExpr(std::ptr_fun(sigmoid))
        // (1.0 / (1.0 + (- X * theta).array().exp())).matrix()
        return X.transpose() * ((X * theta).unaryExpr(std::ptr_fun(sigmoid)) - Y)
                / X.rows();
    }


    static double linesearch(const Matrix& theta, const Matrix& X, const Matrix& Y, const Matrix& grad)
    {
        Matrix x1 = (- X * theta).array().exp().matrix();
        Matrix x2 = X * grad;
        return - ((1.0 - Y.transpose().array()).matrix() * x2)(0, 0) + ((x2.transpose() * x1)(0, 0) / ( 1 + x1.array())).sum();
    }

    static Matrix gradient_descent(const Matrix& theta, const Matrix& X, const Matrix& Y,
                            double al, int ite)
    {
//        Eigen::Matrix3d val; val.fill(1.0);
//        val(0, 1) = 0.0001;     val(0, 0) = val(0, 1) * val(0, 1);
//        val(1, 1) = 0.0001550;  val(1, 0) = val(1, 1) * val(1, 1);
//        val(2, 1) = 0.003;      val(2, 0) = val(2, 1) * val(2, 1);
//        Eigen::Vector3d f;
//        Eigen::Vector3d c;
//            for(int j = 0; j < 3; j++)
//                f(j) = cost(t - val(j) * gradient(t, X, Y), X, Y);
//            c = val.inverse() * f;
//                    //std::cout << cost(t, X, Y) << "\t" << val[j] << "\t" << cost(t - val[j] * gradient(t, X, Y), X, Y) << std::endl;
//        double val[] = {0.0001, 0.0003, 0.0009,
//                         0.001,  0.003,  0.009,
//                          0.01,   0.03,   0.09,
//                           0.1,    0.3,    0.9};

        Matrix t1 = theta, t2 = theta;
        double a = cost(t1, X, Y),
               b;

        // find the al that minimize the most the cost
        for (int i = 0; i < ite; i++)
        {
            // makes sure the cost go down at each iteration
            while(true)
            {
                t1 = t2 - al * gradient(t2, X, Y);
                b = cost(t1, X, Y);

                if (b > a)
                    al = al/3.0;
                else
                    break;
            }

            a = b;
            t2 = t1;
        }

        return t1;
    }
};

}
}

#endif
