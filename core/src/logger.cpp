#include "CloudEngine/logger.h"
#include "fmt/format.h"

static Logger *instance = new Logger();

Logger::Logger()
{
    // instance = this;
}

Logger &Logger::Get()
{
    return *instance;
}
