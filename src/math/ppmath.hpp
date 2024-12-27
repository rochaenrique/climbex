#include "matx.hpp"
#include "vec.hpp"
#include <cmath>

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

    //translate 
    template<typename T, size_t S>
    matx<T,S+1> transl(c_vec<T,S>& vec, 
            c_matx<T,S+1>& mat = I_MATX(T,S+1))
    {
        matx<T,S+1> res = mat;
        for (size_t i = 0; i < S; ++i) 
            res.buff[i][S] = vec.buff[i];
        return res;
    };

    // scale
    template<typename T, size_t S>
    constexpr matx<T,S+1> scale(c_vec<T,S>& vec, c_matx<T,S+1>& mat = I_MATX(T,S+1))
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

    //rotate
    template<typename T, size_t S> requires (S == 3)
    matx<T,S+1> rotate(c_vec<T,S>& axis, double a)
    {
        T x =  axis[0];
        T y =  axis[1];
        T z =  axis[2];
        double inv = 1.0-cos(a);

        return {
            { cos(a)+x*x*inv  , x*y*inv-z*sin(a), x*z*inv+y*sin(a), 0.0 },
            { x*y*inv+z*sin(a), cos(a)+y*y*inv  , y*z*inv-x*sin(a), 0.0 },
            { z*x*inv-y*sin(a), z*y*inv+x*sin(a), cos(a)+z*z*inv  , 0.0 },
            { 0.0             , 0.0             , 0.0             , 1.0 }
        };
    };
}
