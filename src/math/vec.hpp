#pragma once
#include <initializer_list>
#include <array>
#include <iostream>

namespace cm { 
    template <typename T, size_t M, size_t N>
    class matx;

    template <typename T, size_t S>
    class vec
    { 
        public:
            constexpr vec() : buff{} {};

            constexpr vec(const std::array<T, S>& a) : buff{a} {};

            constexpr vec(const std::initializer_list<T>& il)
            {
                auto buffIt = buff.begin();
                for (auto it = il.begin(); it != il.end(); ++it)
                    (*buffIt++) = *it;
            };

            template<typename... Args>
            constexpr vec(Args... args) requires (sizeof...(Args) == S)
                : buff{args...} {};

            constexpr vec(T v) { buff.fill(v); };

            constexpr vec(const vec& a) : buff{a.buff} {};

            constexpr vec(vec&& a) : buff{std::move(a.buff)} {};

            constexpr vec& operator=(const vec& a)
            {
                buff = a.buff;
                return *this;
            };

            constexpr vec& operator=(vec&& a)
            {
                buff = std::move(a.buff);
                return *this;
            };

            constexpr friend vec operator-(const vec& a, const vec& b)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res[i] = a[i] - b[i];
                return res;
            };

            constexpr friend vec operator-(const vec& a) { return -1*a; }

            constexpr friend vec operator*(T k, const vec& a)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res.buff[i] = a.buff[i] * k;
                return res;
            };

            constexpr friend T operator*(const vec& a, const vec& b)
            {
                T res = 0;
                for (int i = 0; i < S; ++i)
                    res += a.buff[i] * b.buff[i];
                return res;
            };


            constexpr T mod() const
            {
                T res = 0;
                for (const T& v : buff)
                    res += v * v;
                return std::sqrt(res);
            };

            constexpr friend bool operator==(const vec& a, const vec& b) 
            { 
                bool res = true;
                int i = 0;
                while (i < S && (res = a.buff[i] == b.buff[i++]));
                return res;
            };

            constexpr friend bool operator>(const vec& a, const vec& b) 
            {
                return a.mod() > b.mod();
            };

            constexpr operator matx<T,S,1>() const
            { 
                matx<T,S,1> res;
                for (size_t i = 0; i < S; i++) 
                    res.buff[i][0] = buff[i];
                return res;
            };

            constexpr operator matx<T,1,S>() const 
            { return { buff }; };

            std::array<T, S> buff;
    };

    template<typename T, typename... Tail>
        vec(T, Tail...) -> vec<T, 1 + sizeof...(Tail)>;

    template<typename T, size_t S>
    constexpr vec<T,S> operator+(const vec<T,S>& a, const vec<T,S>& b)
    {
        vec<T,S> res;
        for (size_t i = 0; i < S; ++i)
            res.buff[i] = a.buff[i] + b.buff[i];
        return res;
    };

    template<typename T, size_t N> requires (N == 3)
    constexpr vec<T,N> cross(const vec<T,N>& a, const vec<T,N>& b)
    {
        vec<T,N> res;
        res.buff[0] = a.buff[1]*b.buff[2]-a.buff[2]*b.buff[1];
        res.buff[1] = a.buff[2]*b.buff[0]-a.buff[0]*b.buff[2];
        res.buff[2] = a.buff[0]*b.buff[1]-a.buff[1]*b.buff[0];

        return res;
    };

    template<typename T, size_t S>
    constexpr static std::ostream& operator<<(std::ostream& os, const vec<T,S>& vec) 
    {
        for (const T& el : vec.buff)
            os << el << ", ";
        return os;
    };
}

