#pragma once
#include <initializer_list>
#include <array>
#include <iostream>
#include "matx.h"

namespace cm { 
    template <typename T, size_t S>
    class vec
    { 
        public:
            vec() : buff{} {};

            vec(const std::array<T, S>& a) : buff{a} {};

            vec(std::initializer_list<T>& il)
            {
                for (int i = 0; i < S; ++i)
                    buff[i] = il[i];
            };

            vec(T v) 
            {
                for (int i = 0; i < S; ++i)  
                    buff[i] = v;
            };

            vec(const vec& a) 
                : buff{a.buff} {};

            vec(vec&& a) 
                : buff{a.buff}
            {
                a.buff = nullptr;
            };

            vec& operator=(const vec& a)
            {
                buff = a.buff;
                a.buff = nullptr;
                return *this;
            };

            vec& operator=(vec&& a)
            {
                buff = a.buff;
                a.buff = nullptr;
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

            vec& cross(const vec& a) const
            {
                int res;
                for (int i = 0; i < S; ++i)
                    res += buff[i] * a[i];
                return *this;
            };

            int mod() const
            {
                int res;
                for (const T& v : buff)
                    res += v * v;
                return std::sqrt(res);
            };


            friend bool operator==(const vec& a, const vec& b) 
            { 
                bool res = true;
                int i = 0;
                while (i < S && (res = a.buff[i] == b.buff[i++]));
                return res;
            };

            friend bool operator>(const vec& a, const vec& b) 
            {
                return a.mod() > b.mod();
            };

            template<typename Q, size_t P>
            operator cm::matx<Q, P, 1>() 
            { 
                return { std::array<Q, P>{buff} };
            };

            std::array<T, S> buff;
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
                std::array<T, 2> buff;
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
                std::array<T, 3> buff;
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
                std::array<T, 4> buff;
            };
    };

    template<typename T, size_t S>
    static std::ostream& operator<<(std::ostream& os, const vec<T,S> vec) {
        for (const T& el : vec.buff)
            os << el << ", ";
        return os;
    };
}

