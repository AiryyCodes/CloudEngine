#pragma once

#include <string>
#include <vector>

template <typename T>
class Optional
{
public:
    Optional()
        : dummy(0), isEmpty(true) {}
    Optional(const T &value)
        : value(value), isEmpty(false) {}
    ~Optional() {}

    T &Get() { return value; }
    bool IsEmpty() { return isEmpty; }

    static Optional<T> Create(const T &value)
    {
        return Optional(value);
    }

    static Optional<T> CreateEmpty()
    {
        return Optional();
    }

private:
    union
    {
        char dummy;
        T value;
    };

    bool isEmpty;
};

inline std::vector<std::string> Split(const std::string &s, const std::string &delimiter)
{
    std::string strCopy = s;

    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = strCopy.find(delimiter)) != std::string::npos)
    {
        token = strCopy.substr(0, pos);
        tokens.push_back(token);
        strCopy.erase(0, pos + delimiter.length());
    }
    tokens.push_back(strCopy);

    return tokens;
}
