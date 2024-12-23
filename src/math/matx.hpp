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

            matx(const std::array<std::array<T, N>, M>& il) 
            { 
                for (int i = 0; i < M; ++i) 
                    for (int j = 0; j < N; ++j) 
                        buff[i][j] = il[i][j];
            }

            matx(const std::initializer_list<std::initializer_list<T>>& il) 
            { 
                for (int i = 0; i < M; ++i) 
                    for (int j = 0; j < N; ++j) 
                        buff[i][j] = il[i][j];
            }

            matx(T v) 
            { 
                for (int i = 0; i < M; ++i) 
                    for (int j = 0; j < N; ++j) 
                        buff[i][j] = v;
            };

            matx(const matx& A) 
                : buff{A.buff} {};

            matx(matx&& A) 
                : buff{A.buff}
            {
                A.buff = nullptr;
            };

            matx& operator=(matx&& A)
            {
                buff = A.buff;
                A.buff = nullptr;
                return *this;
            };

            friend matx operator+(const matx& A, const matx& B)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res[i][j] = A[i][j] + B[i][j];
                return res;
            };

            friend matx operator-(const matx& A, const matx& B)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res[i][j] = A[i][j] - B[i][j];
                return res;
            };

            friend matx operator*(const matx& A, int k)
            {
                matx res;
                for (int i = 0; i < M; ++i)
                    for (int j = 0; j < N; ++j)
                        res[i][j] *= k;
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
                        res[i][j] = sum;
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
                os << row << ", ";
            os << '\n';
        }
        return os;
    };
}
