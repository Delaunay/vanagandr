#ifndef VANAGANDR_ERROR_CONFIG_HEADER
#define VANAGANDR_ERROR_CONFIG_HEADER

// default config
// include your config before #include "Error.h" to override

// do you want it to Throw ?
#ifndef VANAGANDR_THROW
#   define VANAGANDR_THROW 0
#endif

// do you want to enable debug assert
#ifndef VANAGANDR_NDEBUG
#   define VANAGANDR_NDEBUG 0
#endif

#endif
