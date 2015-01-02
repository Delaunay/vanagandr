#ifndef VANAGANDR_FINANCE_VARIANCEMIN_HEADER
#define VANAGANDR_FINANCE_VARIANCEMIN_HEADER

#include "../enum.h"

namespace vanagandr
{
namespace finance
{
/*!
 * \brief Compute the weight w which minimize the expected variance
 *
 * \param cov  : Expecetd covariance : Square Matrix : nxn
 * \param full : if true also return lagrangian mutiplicators
 *
 * \return Column Vector (n + 1)x1  | full == true
 * \return Column Vector nx1        | full == false
 */
Matrix variance_min(const Matrix& cov, bool full = false);

/*!
 * \brief Compute the weight w which minimize the expected variance
 * and with a expected return of rt
 *
 * \param cov  : Expecetd covariance : Square Matrix : nxn
 * \param ret  : Expected return     : Column Vector : nx1
 * \param rt   : target return       : Scalar        : 1x1
 * \param full : if true also return lagrangian mutiplicators
 *
 * \return Column Vector (n + 2)x1  | full == true
 * \return Column Vector nx1        | full == false
 */
Matrix variance_min(const Matrix& cov, const Matrix& ret, const double rt, bool full = false);


/*!
 * \brief Compute the weight w which minimize the expected variance
 * and with a expected return of rt. (include a risk free asset)
 *
 * \param cov  : Expecetd covariance : Square Matrix : nxn
 * \param ret  : Expected return     : Column Vector : nx1
 * \param rt   : target return       : Scalar        : 1x1
 * \param rf   : risk free rate      : Scalar        : 1x1
 * \param full : if true also return lagrangian mutiplicators
 *
 * \return Column Vector (n + 2)x1  | full == true
 * \return Column Vector nx1        | full == false
 */
Matrix variance_min(const Matrix& cov, const Matrix& ret, const double rt,
                    const double rf, bool full = false);

/*!
 * \brief Compute the weights w which minimize the expected variance
 * and with a expected returns of rt
 *
 * \param cov  : Expecetd covariance : Square Matrix : nxn
 * \param ret  : Expected return     : Column Vector : nx1
 * \param rt   : target return       : Column Vector : mx1
 * \param full : if true also return lagrangian mutiplicators
 *
 * \return Matrix (n + 2)xm,  | full == true
 * \return Matrix  nxm        | full == false
 */
Matrix variance_min(const Matrix& cov, const Matrix& ret, const Matrix& rt, bool full = false);

/*!
 * \brief Compute the weight w which minimize the expected variance
 * and with a expected return of rt. (include a risk free asset)
 *
 * \param cov  : Expecetd covariance : Square Matrix : nxn
 * \param ret  : Expected return     : Column Vector : nx1
 * \param rt   : target return       : Column Vector : mx1
 * \param rf   : risk free rate      : Scalar        : 1x1
 * \param full : if true also return lagrangian mutiplicators
 *
 * \return Matrix (n + 2)xm  | full == true
 * \return Matrix nxm        | full == false
 */
Matrix variance_min(const Matrix& cov, const Matrix& ret, const Matrix& rt,
                    const double rf, bool full = false);


/*!
 * \brief extract the correlation from the correlation matrix
 * \param covariance matrix
 * \return corelation matrix
 */
Matrix correl(const Matrix &cov, bool lower = true);

} // finance namespace
} // vanagandr namespace

#endif
