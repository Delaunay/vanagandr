#ifndef VANAGANDR_CRYPTOGRAPHY_UTILS_HEADER
#define VANAGANDR_CRYPTOGRAPHY_UTILS_HEADER

#include "../enum.h"

namespace vanagandr
{
namespace cryptography
{

/*!
 * Complexity
 * ----------
 *  - O(b)
 *
 * Possible Upgrade
 * ----------------
 *  - O(log(b))
 *
 */
template<typename T>
T modular_pow(a, b, mod)
{
    T c = 1;

    for(T i = 1; i <= b; i++)
        c = c * a % mod;

    return c;
}

}
}

#endif
