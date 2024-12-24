#pragma once
#include <array>
#include <initializer_list>
#include <iostream>

namespace cm { 
    template <typename T, size_t M, size_t N>
    class matx 
    { 
        public: 
            matx() : buff{} {};

            matx(const std::array<std::array<T, N>, M>& mat) 
            { 
                auto arrIt = buff.begin();
                for (auto it = mat.begin(); it != mat.end(); ++it)
                    std::copy(it->begin(), it->end(), (arrIt++)->begin());
            }

            matx(std::initializer_list<std::initializer_list<T>> il) 
            { 
                auto arrIt = buff.begin();
                for (auto it = il.begin(); it != il.end(); ++it)
                    std::copy(it->begin(), it->end(), (arrIt++)->begin());
            }

            matx(T v) 
            { 
                for (const auto& row : buff) 
                    for (const auto& cell : row)
                        cell = v;
            };

            matx(const matx& A) 
                : buff{A.buff} {};

            matx(matx&& A) 
                : buff{std::move(A.buff)}
            {};

            matx operator=(matx&& A)
            {
                buff = std::move(A.buff);
                return *this;
            };

            friend matx operator+(const matx& A, const matx& B)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res.buff[i][j] = A.buff[i][j] + B.buff[i][j];
                return res;
            };

            friend matx operator-(const matx& A, const matx& B)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res.buff[i][j] = A.buff[i][j] - B.buff[i][j];
                return res;
            };

            friend matx operator*(int k, const matx& A)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res.buff[i][j] = A.buff[i][j] * k;
                return res;
            };

            template<size_t P, size_t Q, size_t R>
            friend matx<T, P, R> operator*(const matx<T, P, Q>& A, const matx<T, Q, R>& B) 
            { 
                matx<T, P, R> res;
                for (int i = 0; i < P; ++i)
                    for (int j = 0; j < R; ++j)
                    {
                        int sum = 0;
                        for (int z = 0; z < Q; ++z)  
                            sum += A.buff[i][z] + B.buff[z][i];
                        res.buff[i][j] = sum;
                    }
                return res;
            }

            /*
            template<typename P, size_t Q, size_t R> 
            friend matx<P, Q, 1> operator*(const matx<P, Q, R>& A, const cm::vec<P, R>& b) 
            {
                return A*(matx<P, Q, 1>)b;
            }
            */

            //TODO: DEFINE
            int det() const 
            {
            };

            matx<T, N, M> t() const 
            {
                matx<T, N, M> res;
                for (int i = 0; i < M; ++i) 
                    for (int j = 0; j < N; ++j) 
                        res.buff[i][j] = buff[j][i];
                return res;
            };

            friend bool operator==(const matx& A, const matx& B) 
            { 
                bool res = true;
                int i = 0;
                int j = 0; 
                while (i < M && res)  
                    while (j < N && 
                            (res = A.buff[i][j] == B.buff[i++][j++]));
                return res;
            };

            /*
            template<typename P, size_t Q>
            operator cm::vec<P, Q>() const 
            { 
                return { buff[0] };
            };
            */

            std::array<std::array<T, N>, M> buff;

    };

    template<typename T, size_t S> 
        static cm::matx<T,S,S> make_iden() 
        { 
            cm::matx<T,S,S> I;
            for (int i = 0; i < S; ++i) 
                for (int j = 0; j < S; ++j) 
                    I.buff[i][j] = i == j ? 1 : 0;
            return I;
        }

    template<typename T, size_t M, size_t N>
    static std::ostream& operator<<(std::ostream& os, const matx<T,M,N> matx) {
        for (const std::array<T, N>& row : matx.buff)
        {
            for (const T& v : row) 
                os << v << ", ";
            os << '\n';
        }
        return os;
    };
}
