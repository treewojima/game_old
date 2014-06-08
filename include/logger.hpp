#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>

#include "defines.hpp"

// Convenience macros
#define LOG_INFO    (Logger::getInst() << "[" << Logger::timestamp() << "] ")
#define LOG_WARNING (LOG_INFO << "warning: ")
#define LOG_ERROR   (LOG_INFO << "ERROR: ")

#define LOG_BUFFER_SIZE 256

// Singleton logger class
class Logger
{
    friend Logger &endl(Logger &logger);

public:
    Logger();
    ~Logger();

    static Logger &getInst();

    unsigned flush();

    // Timestamp helper
    static const char *timestamp();

    // Basic types
    Logger &operator<<(bool b);
    Logger &operator<<(char c);
    Logger &operator<<(double d);
    Logger &operator<<(float f);
    Logger &operator<<(int i);
    Logger &operator<<(long l);
    Logger &operator<<(unsigned u);
    Logger &operator<<(unsigned long lu);

    // String types
    Logger &operator<<(const char *s);
    Logger &operator<<(const std::string &s);

    // Stream manipulator functionality
    Logger &operator<<(Logger &(*pf)(Logger &));

private:
    FILE *_fp;
    char _buffer[LOG_BUFFER_SIZE];
};

Logger &endl(Logger &logger);

#endif
