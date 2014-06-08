#include "logger.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <sstream>

#include "defines.hpp"

using namespace std;

Logger::Logger()
{
    memset(_buffer, 0, LOG_BUFFER_SIZE);

    const char *filename = "log.txt";
    _fp = fopen(filename, "w");
    if (!_fp)
    {
        printf("ERROR: couldn't start logger");
        exit(1);
    }

    ostringstream ss;
    ss << "Logger started at " << timestamp() << " (logging to " << filename << ")";
    const char *str = ss.str().c_str();

    printf("%s\n", str);
    fprintf(_fp, "%s\n", str);
    fflush(stdout);
    fflush(_fp);
}

Logger::~Logger()
{
    ostringstream ss;
    ss << "Logger stopped at " << timestamp();
    const char *str = ss.str().c_str();

    printf("%s\n", str);
    assert(_fp);
    fprintf(_fp, "%s\n", str);

    fflush(stdout);
    fflush(_fp);

    fclose(_fp);
}

// The standard lazy static singleton instance
Logger &Logger::getInst()
{
    static Logger logger;
    return logger;
}

unsigned Logger::flush()
{
    printf("%s\n", _buffer);
    assert(_fp);
    fprintf(_fp, "%s\n", _buffer);

    fflush(stdout);
    fflush(_fp);

    unsigned len = strlen(_buffer);
    memset(_buffer, 0, LOG_BUFFER_SIZE);

    return len;
}

const char *Logger::timestamp()
{
    static char date[20];
    time_t t = time(0);
    strftime(date, sizeof(date), "%m/%d/%Y %X", localtime(&t));
    return date;
}

Logger &Logger::operator<<(bool b)
{
    const char *valueStrings[] = { "false", "true" };

    sprintf(_buffer + strlen(_buffer), "%s", valueStrings[b]);

    return *this;
}

Logger &Logger::operator<<(char c)
{
    sprintf(_buffer + strlen(_buffer), "%c", c);

    return *this;
}

Logger &Logger::operator<<(double d)
{
    sprintf(_buffer + strlen(_buffer), "%f", d);

    return *this;
}

Logger &Logger::operator<<(float f)
{
    operator<<(static_cast<double>(f));
    return *this;
}

Logger &Logger::operator<<(int i)
{
    operator<<(static_cast<long>(i));
    return *this;
}

Logger &Logger::operator<<(long l)
{
    sprintf(_buffer + strlen(_buffer), "%ld", l);

    return *this;
}

Logger &Logger::operator<<(unsigned u)
{
    operator<<(static_cast<unsigned long>(u));
    return *this;
}

Logger &Logger::operator<<(unsigned long lu)
{
    sprintf(_buffer + strlen(_buffer), "%lu", lu);

    return *this;
}

Logger &Logger::operator<<(const char *s)
{
    assert(s);
    sprintf(_buffer + strlen(_buffer), "%s", s);

    return *this;
}

Logger &Logger::operator<<(const string &s)
{
    operator<<(s.c_str());
    return *this;
}

Logger &Logger::operator<<(Logger &(*pf)(Logger &))
{
    return pf(*this);
}

Logger &endl(Logger &logger)
{
    logger.flush();
    return logger;
}
