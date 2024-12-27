#include "matx.hpp"
#include "vec.hpp"

template<typename T, size_t P, size_t Q>
cm::vec<T,Q> operator*(const cm::matx<T,P,Q>& A, const cm::vec<T,Q>& x) 
{
    return A*(cm::matx<T,Q,1>)x;
};

