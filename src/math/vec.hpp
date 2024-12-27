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
            vec() : buff{} {};

            vec(const std::array<T, S>& a) : buff{a} {};

            vec(const std::initializer_list<T>& il)
            {
                auto buffIt = buff.begin();
                for (auto it = il.begin(); it != il.end(); ++it)
                    (*buffIt++) = *it;
            };

            vec(T v) { buff.fill(v); };

            vec(const vec& a) : buff{a.buff} {};

            vec(vec&& a) : buff{std::move(a.buff)} {};

            vec& operator=(const vec& a)
            {
                buff = a.buff;
                return *this;
            };

            vec& operator=(vec&& a)
            {
                buff = std::move(a.buff);
                return *this;
            };

            friend vec operator-(const vec& a, const vec& b)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res[i] = a[i] - b[i];
                return res;
            };

            friend vec operator-(const vec& a) { return -1*a; }

            friend vec operator*(T k, const vec& a)
            {
                vec res;
                for (int i = 0; i < S; ++i)
                    res.buff[i] = a.buff[i] * k;
                return res;
            };

            friend T operator*(const vec& a, const vec& b)
            {
                T res = 0;
                for (int i = 0; i < S; ++i)
                    res += a.buff[i] * b.buff[i];
                return res;
            };


            T mod() const
            {
                T res = 0;
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

            operator matx<T,S,1>() const
            { 
                matx<T,S,1> res;
                for (size_t i = 0; i < S; i++) 
                    res.buff[i][0] = buff[i];
                return res;
            };

            operator matx<T,1,S>() const 
            { return { buff }; };

            std::array<T, S> buff;
    };

    template<typename T, typename... Tail>
        vec(T, Tail...) -> vec<T, 1 + sizeof...(Tail)>;

    template<typename T, size_t S>
    vec<T,S> operator+(const vec<T,S>& a, const vec<T,S>& b)
    {
        vec<T,S> res;
        for (size_t i = 0; i < S; ++i)
            res.buff[i] = a.buff[i] + b.buff[i];
        return res;
    };

    template<typename T, size_t N> requires (N == 3)
    vec<T,N> cross(const vec<T,N>& a, const vec<T,N>& b)
    {
        vec<T,N> res;
        res.buff[0] = a.buff[1]*b.buff[2]-a.buff[2]*b.buff[1];
        res.buff[1] = a.buff[2]*b.buff[0]-a.buff[0]*b.buff[2];
        res.buff[2] = a.buff[0]*b.buff[1]-a.buff[1]*b.buff[0];

        return res;
    };

    template<typename T, size_t S>
    static std::ostream& operator<<(std::ostream& os, const vec<T,S>& vec) 
    {
        for (const T& el : vec.buff)
            os << el << ", ";
        return os;
    };
    
}

