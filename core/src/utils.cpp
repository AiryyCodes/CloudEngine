#include "utils.h"

#include <cstdio>
#include <fstream>
#include <string>

std::string Utils::ReadFileFromDisk(std::string path)
{
    std::ifstream stream(path);

    std::string line;
    std::string content;

    while (std::getline(stream, line))
    {
        content += line;
        content.push_back('\n');
    }

    return content;
}
