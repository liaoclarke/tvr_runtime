#ifndef UTIL_Verbosity_H
#define UTIL_Verbosity_H
#include <iostream>
#define TVR_DEV_VERBOSE(tag, message) std::cerr << "[" << tag << "] " << message << std::endl;

#endif
