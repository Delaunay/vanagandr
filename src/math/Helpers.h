#ifndef VANAGANDR_MATH_HELPERS_HEADER
#define VANAGANDR_MATH_HELPERS_HEADER

#include "../enum.h"

namespace vanagandr
{
namespace math
{

// function are defined such as :
// compute_correlation(compute_covariance(compute_returns(data)))

// compute correlation does not compute the covariance
// compute covariance does not compute the returns
// that way users will not ask to compute twice the samething useless they want to

// assume data are from older to newer
Matrix compute_returns      (const Matrix& data_price);
Matrix compute_covariance   (const Matrix& data_percentage);
Matrix compute_correlation  (const Matrix& data_covariance);

}
}

#endif
