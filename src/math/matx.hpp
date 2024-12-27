#pragma once
#include <array>
#include <initializer_list>
#include <iostream>

namespace cm { 
    template<typename P, size_t Q>
    class vec;

    template <typename T, size_t M, size_t N = M>
    class matx 
    { 
        public: 
            constexpr matx() : buff{} {};

            constexpr matx(const std::array<std::array<T, N>, M>& mat) 
            { 
                auto arrIt = buff.begin();
                for (auto it = mat.begin(); it != mat.end(); ++it)
                    std::copy(it->begin(), it->end(), (arrIt++)->begin());
            }

            constexpr matx(const std::array<std::array<T, N>, M>&& mat) 
            { 
                auto arrIt = buff.begin();
                for (auto it = mat.begin(); it != mat.end(); ++it)
                    std::move(it->begin(), it->end(), (arrIt++)->begin());
            }

            constexpr matx(const std::initializer_list<std::initializer_list<T>>& il) 
            { 
                auto arrIt = buff.begin();
                for (auto it = il.begin(); it != il.end(); ++it)
                    std::copy(it->begin(), it->end(), (arrIt++)->begin());
            }

            constexpr matx(T v) 
            { 
                for (const auto& row : buff) 
                    row.fill(v);
            };

            constexpr matx(const matx& A) 
                : buff{A.buff} {};

            constexpr matx(matx&& A) 
                : buff{std::move(A.buff)}
            {};

            constexpr matx operator=(matx&& A)
            {
                buff = std::move(A.buff);
                return *this;
            };

            constexpr matx operator=(const matx& A)
            {
                buff = A.buff;
                return *this;
            };

            constexpr friend matx operator+(const matx& A, const matx& B)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res.buff[i][j] = A.buff[i][j] + B.buff[i][j];
                return res;
            };

            constexpr friend matx operator-(const matx& A, const matx& B)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res.buff[i][j] = A.buff[i][j] - B.buff[i][j];
                return res;
            };

            constexpr friend matx operator*(T k, const matx& A)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res.buff[i][j] = A.buff[i][j] * k;
                return res;
            };


            //TODO: DEFINE
            constexpr T det() const 
            {
            };

            constexpr matx<T,N,M> t() const 
            {
                matx<T,N,M> res;
                for (int i = 0; i < M; ++i) 
                    for (int j = 0; j < N; ++j) 
                        res.buff[i][j] = buff[j][i];
                return res;
            };

            constexpr friend bool operator==(const matx& A, const matx& B) 
            { 
                bool res = true;
                int i = 0;
                int j = 0; 
                while (i < M && res)  
                    while (j < N && 
                            (res = A.buff[i][j] == B.buff[i++][j++]));
                return res;
            };

            constexpr operator vec<T, M>() const requires (N == 1)
            { 
                vec<T, M> res;
                for (size_t i = 0; i < M; ++i) 
                    res.buff[i] = buff[i][0];
                return res;
            };

            std::array<std::array<T, N>, M> buff;

    };

    template<typename T, size_t P, size_t Q, size_t R>
    constexpr matx<T,P,R> operator*(const matx<T,P,Q>& A, const matx<T,Q,R>& B) 
    { 
        matx<T,P,R> res;
        for (int p = 0; p < P; ++p)  
            for (int r = 0; r < R; ++r) 
                for (int q = 0; q < Q; ++q) 
                    res.buff[p][r] += A.buff[p][q] * B.buff[q][r];

        return res;
    }

    template<typename T, size_t S> 
    constexpr static cm::matx<T,S,S> make_iden() 
    { 
        cm::matx<T,S,S> I;
        for (int i = 0; i < S; ++i) 
            for (int j = 0; j < S; ++j) 
                I.buff[i][j] = i == j ? 1 : 0;
        return I;
    }

    template<typename T, size_t M, size_t N>
    constexpr static std::ostream& operator<<(std::ostream& os, const matx<T,M,N>& matx) {
        for (const std::array<T, N>& row : matx.buff)
        {
            for (const T& v : row) 
                os << v << ", ";
            os << '\n';
        }
        return os;
    };

}
