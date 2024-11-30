#pragma once
#include <initializer_list>
#include <array>
#include <iostream>

namespace cm { 
    template <typename T, size_t S>
    class vec
    { 
        public:
            vec() : arr{} {};

            vec(const std::array<T, S>& a) : arr{a} {};

            vec(std::initializer_list<T> il)
            {
                for (int i = 0; i < S; ++i)
                    arr[i] = il[i];
            };

            vec(const vec& a) 
                : arr{a.arr} {};

            vec(vec&& a) 
                : arr{a.arr}
            {
                a.arr = nullptr;
            };

            vec& operator=(const vec& a)
            {
                arr = a.arr;
                a.arr = nullptr;
                return *this;
            };

            vec& operator=(vec&& a)
            {
                arr = a.arr;
                a.arr = nullptr;
                return *this;
            };

            friend vec operator+(const vec& a, const vec& b)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res[i] = a[i] + b[i];
                return res;
            };

            friend vec operator-(const vec& a, const vec& b)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res[i] = a[i] - b[i];
                return res;
            };

            friend vec operator*(const vec& a, int k)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res[i] *= k;
                return res;
            };

            friend int operator*(const vec& a, const vec& b)
            {
                int res;
                for (int i = 0; i < S; ++i)
                    res += a[i] * b[i];
                return res;
            };

            vec& cross(const vec& a)
            {
                int res;
                for (int i = 0; i < S; ++i)
                    res += arr[i] * a[i];
                return *this;
            };

            int mod()
            {
                int res;
                for (const T& v : arr)
                    res += v * v;
                return std::sqrt(res);
            };

            std::array<T, S> arr;

        private: 
            T& operator[](size_t i)
            {
                static_assert(i >= S, "index out of bounds");
                return arr[i];
            };

            const T& operator[](size_t i) const
            {
                static_assert(i >= S, "index out of bounds");
                return arr[i];
            };
    };

    template<typename T, typename... Tail>
        vec(T, Tail...) -> vec<T, 1 + sizeof...(Tail)>;

    template<typename T>
    class vec<T, 2>
    {
        public: 
            vec(T x, T y) : x(x), y(y) {};

            union { 
                struct { T x, y; };
                std::array<T, 2> arr;
            };
    };

    template<typename T>
    class vec<T, 3>
    {
        public: 
            vec(T x, T y, T z) : x(x), y(y), z(z) {};

            union { 
                struct { T x, y, z; };
                struct { T r, g, b; };
                std::array<T, 3> arr;
            };
    };

    template<typename T>
    class vec<T, 4>
    {
        public: 
            vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

            union { 
                struct { T x, y, z, w; };
                struct { T r, g, b, a; };
                std::array<T, 4> arr;
            };
    };
}

template<typename T, size_t S>
static std::ostream& operator<<(std::ostream& os, const cm::vec<T,S> vec) 
{
    for (const T& el : vec.arr)
        os << el << ", ";
    return os;
};
