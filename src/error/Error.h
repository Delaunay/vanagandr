#ifndef VANAGANDR_ERROR_ERROR_HEADER
#define VANAGANDR_ERROR_ERROR_HEADER

#include "ErrorConfig.h"
//  Your app should not throw
// TMP might be usuable

// Throw has priority over <assert>
#if VANAGANDR_NDEBUG
#   define VASSERT(x)
#else
#   include <cassert>
#   define VASSERT(x) assert(x)
#endif
#if VANAGANDR_THROW
#   define VTHROW(predicate, error, message) if((predicate)) throw error(message)
#elif !VANAGANDR_NDEBUG
#   define VTHROW(predicate, error, message) assert(!(predicate) && message)
#else
#   define VTHROW(predicate, error, message)
#endif

#endif
