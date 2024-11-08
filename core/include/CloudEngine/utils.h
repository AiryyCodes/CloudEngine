#pragma once

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
