//
// Created by kaygalle on 13.08.2020.
//

#ifndef LIBSDL_VECTORS_HPP
#define LIBSDL_VECTORS_HPP

#include <ostream>
#include <sstream>
#include <fstream>
#include <cassert>

template <class T, std::size_t N>
struct vec
{
    private:
        T _data[N];
    public:
        T& operator [] (int i) { assert(i < N); return _data[i]; };
};

typedef vec <float, 2> vec2f;
typedef vec <float, 3> vec3f;
typedef vec <float, 4> vec4f;

typedef vec <int, 2> vec2i;
typedef vec <int, 3> vec3i;
typedef vec <int, 4> vec4i;

template <typename T>
struct vec <T, 2>
{
    T x, y;
    vec() : x(T()), y(T()) {};
    vec( T X, T Y) : x(X), y(Y) {};
    T& operator [] (int i)  { assert(i < 2); return (i > 0) ? y : x; };
};

template <typename T>
struct vec <T, 3>
{
    T x, y, z;
    vec() : x(T()), y(T()), z(T()) {};
    vec( T X, T Y, T Z) : x(X), y(Y), z(Z) {};
    T& operator [] (int i)  { assert(i < 3); return (i > 1) ? z : (i > 0) ? y : x; };

};

template <typename T>
struct vec <T, 4>
{
    T x, y, z, w;
    vec() : x(T()), y(T()), z(T()), w(T()) {};
    vec( T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {};
    T& operator [] (int i)  { assert(i < 4); return (i > 2) ? w : (i > 1) ? z : (i > 0) ? y : x; };
};

template <typename T, size_t size>
std::ostream& operator << (std::ostream& out, vec<T, size> v)
{
    out << '(';
    for (int i = 0; i < size; i++)
    {
        out << v[i] << ',';
    }
    out << ')';
    return out;
}

template <typename T, size_t size>
vec<T, size> operator + (vec <T, size> lhs, vec <T, size> rhs)
{
    vec <T, size> ret;
    for (size_t i = 0; i < size; i++)
    {
        ret[i] = lhs[i] + rhs[i];
    }
    return ret;
}

template <typename T, size_t size>
vec<T, size> operator - (vec <T, size> lhs, vec <T, size> rhs)
{
    vec <T, size> ret;
    for (size_t i = 0; i < size; i++)
    {
        ret[i] = lhs[i] - rhs[i];
    }
    return ret;
}

template <typename T, size_t size>
vec<T, size> operator * (vec <T, size> lhs, vec <T, size> rhs)
{
    T ret = T();
    for (size_t i = 0; i < size; i++)
    {
        ret[i] += lhs[i] * rhs[i];
    }

    return ret;
}

#endif //LIBSDL_VECTORS_HPP
