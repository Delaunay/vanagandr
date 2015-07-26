#include "../math/Matrix.h"


namespace vanagandr
{
    Matrix bubleSortRow(Matrix data, Order b)
    {
        Matrix result = data;

        Real buf;

        if (b == Descending)
        {
            // for each columns
            for (Index h = 0; h < data.cols(); h++)
            {
                // order the rows
                for (Index k = 0; k < data.rows(); k++)
                {
                    buf = result(k, h);

                    for (Index l = k; l < data.rows(); l++)
                    {
                        if (buf < result(l, h))
                        {
                            result(k, h) = result(l, h);
                            result(l, h) = buf;

                            buf = result(k, h);
                        }
                    }
                }
            }

            return result;
        }

        // for each columns
        for (Index h = 0; h < data.cols(); h++)
        {
            // order the rows
            for (Index k = 0; k < data.rows(); k++)
            {
                buf = result(k, h);

                for (Index l = k; l < data.rows(); l++)
                {
                    if (buf > result(l, h))
                    {
                        result(k, h) = result(l, h);
                        result(l, h) = buf;

                        buf = result(k, h);
                    }
                }
            }
        }

        return result;
    }

	Matrix cutMatrix(Matrix a, int rowb, int colb, int rowe, int cole)
	{
		int n = a.rows();
		int m = a.cols();
		Matrix A = Matrix::Zero(n - rowb - rowe, m - colb - cole);

		for (int i = rowb; i < n - rowe ; i ++)
			for ( int j = colb; j < m - cole ; j ++)
				A(i - rowb, j - colb) = a(i, j);

		return A;
	}

	Matrix average(Matrix a, Alignment b)
	{
		if (b == Vertical)
		{
			Matrix e = Matrix::Constant(a.cols(), 1, 1.0/ a.cols()) ;
			return a * e;
		}
		else
		{
			Matrix e = Matrix::Constant(1, a.rows(), 1.0/ a.rows()) ;
			return e * a;
		}
	}

	Matrix yield(Matrix A, Alignment b)
	{
		int n =  A.rows();
		int m =  A.cols();

		if (b == Vertical)
		{
			Matrix B = Matrix::Zero( n , m - 1);

			for (int i = 0 ; i < n ; i++)
				for (int j = 1 ; j < m ; j++)
                    B(i, j - 1) = log ( A(i, j) / A(i, j - 1 ) ) ;

			return B;
		}
		else
		{
			Matrix B = Matrix::Zero( n - 1, m);

			for (int i = 1 ; i < n ; i++)
				for (int j = 0 ; j < m ; j++)
					B(i - 1, j) = log ( A(i, j) / A(i - 1, j ) );

			return B;
		}
	}

	Matrix covariance(Matrix A,  Alignment b)
	{
        //for(Index k = 0; k <_periodicReturn.cols();k++)
        //    for(Index h = 0; h < _periodicReturn.rows(); h++)
        //        cov(h, k) = _periodicReturn(h, k) - _Statistics[k].mean;

		int n = A.rows();
		int m = A.cols();


		Matrix B(n, m);
        Matrix E = average(A, b);

		if (b ==  Vertical)
		{
			for (int i = 0; i < n ; i++)
				for (int j = 0; j < m; j++)
					B(i, j) = A(i, j) - E(i, 0);

			return ( B * B.transpose())/ m;
		}
		else
        {
            for (int i = 0; i < n ; i++)
              for (int j = 0; j < m; j++)
                  B(i, j) = A(i, j) - E(0, j);

            return ( B.transpose()  * B )/ n;
		}
	}


Matrix linearRegression(Matrix IndiVar, Matrix DiVar,  Alignment b)
{
	if (IndiVar.rows() == DiVar.rows())
		throw std::invalid_argument("Matrix Multiplication Impossible");


	if (b ==  Vertical)
	{
		// Add the intercept as aRow
		int n = IndiVar.rows();
		IndiVar.conservativeResize( n + 1, Eigen::NoChange);

		for (int i = 0; i < IndiVar.cols(); i++)
			IndiVar(n, i) = 1;

		return (DiVar * IndiVar.transpose()) * ( IndiVar * IndiVar.transpose() ).inverse();
	}
	else
	{
		// Add the intercept as a Column
		int n = IndiVar.cols();
		IndiVar.conservativeResize(Eigen::NoChange, n + 1);

		for (int i = 0; i < IndiVar.rows(); i++)
			IndiVar(i, n) = 1;

		return  ( IndiVar.transpose() * IndiVar ).inverse() * (IndiVar.transpose() * DiVar);
	}
}

/*Matrix customLinearRegr(Matrix IndiVar, Matrix DiVar, Function f,  Alignment b)
{
	if (IndiVar.rows() == DiVar.rows())
		throw std::invalid_argument("Matrix Multiplication Impossible");

	if (b ==  Vertical)
	{
		// Add the intercept as aRow
		int n = IndiVar.rows();
		IndiVar.conservativeResize( n + 1, Eigen::NoChange);

		for (int i = 0; i < IndiVar.cols(); i++)
			IndiVar(n, i) = 1;

		for ( int i = 0; i < DiVar.cols() ; i++)
			DiVar(0, i) = f(DiVar(0, i));

		return (DiVar * IndiVar.transpose()) * ( IndiVar * IndiVar.transpose() ).inverse();
	}
	else
	{
		// Add the intercept as a Column
		int n = IndiVar.cols();
		IndiVar.conservativeResize(Eigen::NoChange, n + 1);

		for (int i = 0; i < IndiVar.rows(); i++)
			IndiVar(i, n) = 1;

		for ( int i = 0; i < DiVar.rows() ; i++)
			DiVar(i, 0) = f(DiVar(i, 0));

		return  ( IndiVar.transpose() * IndiVar ).inverse() * (IndiVar.transpose() * DiVar);
	}
}

Matrix logLinearRegr	  (Matrix IndiVar, Matrix DiVar,  Alignment b)
{
	Function f = log;

	return customLinearRegr(IndiVar, DiVar, f, b);
}*/



/*
double 			    FIN_Lin::CptDetermination	(FIN_Matrix<double> Independant, FIN_Matrix<double> Dependant, FIN_Matrix<double> Coefficient)
{
	// add the intercept
	FIN_Matrix<double> A(Independant.size1(), Independant.size2() + 1);

	for (unsigned i = 0, n = A.size1(); i < n; i ++)
	{
		for (unsigned j = 0, m = A.size2(); j < m; j++)
		{
			if (j == 0)
				A(i, j) = 1;

			else
				A(i, j) = Independant(i, j - 1);
		}
	}

	double average = 0;
	double sum = 0;

	unsigned n = Dependant.size1();

	for ( unsigned i = 0; i < n; i++)
	{
		average = average + Dependant(i, 0);
	}

	average = average / n;

	FIN_Matrix<double> buf = prod(A, Coefficient);

	for (unsigned i = 0; i < n; i++)
	{
		sum = sum + ( buf(i, 0) - average ) * ( buf(i, 0) - average );

	}
	return 1 - CptQuadraticError(Independant, Dependant, Coefficient)/sum;
}
double 			    FIN_Lin::CptQuadraticError	(FIN_Matrix<double> Independant, FIN_Matrix<double> Dependant, FIN_Matrix<double> Coefficient)
{
	if (Independant.size2() != Coefficient.size1() - 1)
		return 0;

	// add the intercept
	FIN_Matrix<double> A(Independant.size1(), Independant.size2() + 1);

	for (unsigned i = 0, n = A.size1(); i < n; i ++)
	{
		for (unsigned j = 0, m = A.size2(); j < m; j++)
		{
			if (j == 0)
				A(i, j) = 1;

			else
				A(i, j) = Independant(i, j - 1);
		}
	}

	FIN_Matrix<double> buf(prod(A, Coefficient) - Dependant );

	return ( prod(trans( buf ), buf ) )(0, 0);
}
*/
}
