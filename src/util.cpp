#include "util.hpp"

#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "defines.hpp"

using namespace std;

const float PTM_RATIO = 1.f / 50.f;

string format(const string &format, ...)
{
    va_list args;
    char buffer[256];
    
    va_start(args, format);
    vsprintf(buffer, format.c_str(), args);
    va_end(args);
    
    return string(buffer);
}

string readFileContents(const char *filename)
{
    string contents;
    ifstream file(filename, ios::binary);
    file.seekg(0, ios::end);
    contents.resize(file.tellg());
    file.seekg(0, ios::beg);
    file.read(&contents[0], contents.size());
    file.close();

    return contents;
}
