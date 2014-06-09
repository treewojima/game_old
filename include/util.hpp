#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <string>

#include "defines.hpp"

extern const float PTM_RATIO;

#ifdef USE_FORMAT
std::string format(const std::string &format, ...);
#endif

std::string readFileContents(const char *filename);

inline std::string readFileContents(const std::string &filename)
{
    return readFileContents(filename.c_str());
}

inline bool isPowerOfTwo(int i)
{
    return (i & (i - 1)) == 0;
}

inline float p2m(float pixels)
{
    return pixels * PTM_RATIO;
}

inline float m2p(float meters)
{
    return meters / PTM_RATIO;
}

#endif
