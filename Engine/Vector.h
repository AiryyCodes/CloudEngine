#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

typedef glm::ivec2 Vector2i;
typedef glm::ivec3 Vector3i;
typedef glm::ivec4 Vector4i;

typedef glm::fvec2 Vector2f;
typedef glm::fvec3 Vector3f;
typedef glm::fvec4 Vector4f;

typedef glm::quat Quaternion;

namespace std
{
// Hash function for Vector2i, Vector3i, Vector4i
template <>
struct hash<Vector2i>
{
    size_t operator()(const Vector2i &v) const noexcept
    {
        return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
    }
};

template <>
struct hash<Vector3i>
{
    size_t operator()(const Vector3i &v) const noexcept
    {
        return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1) ^ (hash<int>()(v.z) << 2);
    }
};

template <>
struct hash<Vector4i>
{
    size_t operator()(const Vector4i &v) const noexcept
    {
        return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1) ^ (hash<int>()(v.z) << 2) ^ (hash<int>()(v.w) << 3);
    }
};

// Hash function for Vector2f, Vector3f, Vector4f
template <>
struct hash<Vector2f>
{
    size_t operator()(const Vector2f &v) const noexcept
    {
        return hash<float>()(v.x) ^ (hash<float>()(v.y) << 1);
    }
};

template <>
struct hash<Vector3f>
{
    size_t operator()(const Vector3f &v) const noexcept
    {
        return hash<float>()(v.x) ^ (hash<float>()(v.y) << 1) ^ (hash<float>()(v.z) << 2);
    }
};

template <>
struct hash<Vector4f>
{
    size_t operator()(const Vector4f &v) const noexcept
    {
        return hash<float>()(v.x) ^ (hash<float>()(v.y) << 1) ^ (hash<float>()(v.z) << 2) ^ (hash<float>()(v.w) << 3);
    }
};
} // namespace std
