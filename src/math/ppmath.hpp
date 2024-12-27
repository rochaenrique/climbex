#include "matx.hpp"
#include "vec.hpp"

namespace cm { 
    template<typename T, size_t M, size_t N = M>
        using c_matx = const matx<T,M,N>;

    template<typename T, size_t S>
        using c_vec = const vec<T,S>;

#define I_MATX(T,S) cm::make_iden<T,S>()

    template<typename T, size_t P, size_t Q>
    inline vec<T,Q> operator*(c_matx<T,P,Q>& A, c_vec<T,Q>& x) 
    {
        return A*(matx<T,Q,1>)x;
    };

    template<typename T, size_t S>
    matx<T,S+1> transl(c_vec<T,S>& vec, 
            c_matx<T,S+1>& mat = I_MATX(T,S+1))
    {
        matx<T,S+1> res = mat;
        for (size_t i = 0; i < S; ++i) 
            res.buff[i][S] = vec.buff[i];
        return res;
    };

    template<typename T, size_t S>
    matx<T,S+1> scale(c_vec<T,S>& vec, c_matx<T,S+1>& mat = I_MATX(T,S+1))
    {
        matx<T,S+1> res = mat;
        for (size_t i = 0; i < S; ++i) 
            res.buff[i][i] *= vec.buff[i];
        return res;
    };

    template<typename T, size_t S>
    matx<T,S> scale(T k, c_matx<T,S>& mat = I_MATX(T,S))
    {
        matx<T,S> res = mat;
        for (size_t i = 0; i < S-1; ++i) 
            res.buff[i][i] *= k;
        return res;
    };
}
