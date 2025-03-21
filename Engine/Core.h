#pragma once

#include <memory>

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
Scope<T> CreateScope(Args &&...args)
{
    return std::make_unique<T>(args...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
Ref<T> CreateRef(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
