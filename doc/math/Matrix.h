#ifndef FINMATRX_H
#define FINMATRX_H

#include <stdexcept>
#include <iostream>

#include "../Enum.h"

namespace vanagandr
{
	Matrix average				(Matrix a, Alignment b = Vertical);
	Matrix yield				(Matrix a, Alignment b = Vertical);
	Matrix covariance			(Matrix a, Alignment b = Vertical);
	Matrix cutMatrix			(Matrix a, int rowb, int colb, int rowe, int cole);


	Matrix linearRegression		(Matrix IndiVar, Matrix DiVar, Alignment b = Vertical);
	//Matrix customLinearRegr		(Matrix IndiVar, Matrix DiVar, Function f, Alignment b = Vertical);
	Matrix logLinearRegr		(Matrix IndiVar, Matrix DiVar, Alignment b = Vertical);

	Matrix modelProjection		(Matrix IndiVar, Matrix DiVar, Alignment b = Vertical);
	Matrix quadraticError		(Matrix IndiVar, Matrix DiVar, Alignment b = Vertical);
	Matrix determinationCoefficient(Matrix IndiVar, Matrix DiVar, Alignment b = Vertical);

    Matrix bubleSortRow(Matrix data, Order b = Ascending);


    /*
    void returnRepartition()
    {
        Index bin = round(pow( _periodicReturn.rows()));

        double min[_periodicReturn.cols()];
        double max[_periodicReturn.cols()];
        double binsize[_periodicReturn.cols()];

        for(Index k = 0; k < _periodicReturn.cols; k++)
        {
            min[k] = _periodicReturnOrdered(0, k);
            max[k] = _periodicReturnOrdered(_periodicReturn.rows() - 1, k);

            binsize[k] = ( max[k] - min[k] )/ bin;
        }

        for (Index h = 0; h < _periodicReturn.cols(); h++)
        {
            std::vector<struct Bin> b;

            struct Bin buf= buf;
                buf.Low = min[h];
                buf.Frequency = 0;

            for (Index k = 0; k < _periodicReturn.rows(); k++)
            {
                if (_periodicReturnOrdered(k, h) <= buf.Low)
                {
                    buf.Frequency = buf.Frequency + 1;
                }
                else
                {
                    b.push_back(buf);

                    buf.Low = buf.Low + binsize[h];
                    buf.Frequency = 1;
                }
            }

            _BinArray.push_back(b);
        }
    }*/

}



#endif // FINMATRX_H
