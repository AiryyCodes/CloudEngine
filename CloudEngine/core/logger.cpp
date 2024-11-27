#include "CloudEngine/core/logger.h"

#include <sstream>
#include <streambuf>

static Logger *instance = new Logger();
static std::stringstream buffer;
static std::streambuf *oldBuffer;

Logger::Logger()
{
    // instance = this;
    // oldBuffer = std::cout.rdbuf(buffer.rdbuf());
}

Logger::~Logger()
{
}

Logger &Logger::Get()
{
    return *instance;
}

const std::stringstream &Logger::GetBuffer()
{
    return buffer;
}
