#ifndef JNP1_4_FIBIN_H
#define JNP1_4_FIBIN_H

#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

template<int N>
struct Fib;

template <typename T>
struct Lit;

template<typename ... Args>
struct Sum;

template <typename Var, typename Val, typename Ex>
struct Let;

template <int n>
struct Var;

template <typename T>
struct Ref;

template <int n>
struct Ref<Var<n>>;

template <typename T>
struct Inc1;

template <typename T>
struct Inc10;

template<typename VT, typename T>
struct Expr;

template<typename VT, typename A, typename B, typename C>
struct VExpr;

template<typename VT, typename T, int n, typename V>
struct Expr<VT, Let<Var<n>,  T, V>> {
    constexpr static VT val = VExpr<VT, Var<n>, T, V>::val;
};


template<typename VT, typename T, int n>
struct VExpr <VT, Var<n>, T, Ref<Var<n>> >{
    constexpr static VT val = Expr<VT, T>::val;
};

template<typename VT, typename T, int n, typename ... V>
struct VExpr <VT, Var<n>,  T, Sum <V...> >{
    constexpr static VT val = (VExpr<VT, Var<n>, T, V>::val + ...);
};

template<typename VT, typename T, typename V, int n>
struct VExpr <VT, V, T, Lit<Fib<n>> >{
    constexpr static VT val = Expr<VT, Lit<Fib<n>>>::val;
};

template<typename VT, typename T, int n, typename V>
struct VExpr <VT, Var<n>, T, Inc1<V> >{
    constexpr static VT val = VExpr<VT, Var<n>, T, V>::val + Expr<VT, Lit<Fib<1>>>::val;
};

template<typename VT, typename T, int n, typename V>
struct VExpr <VT, Var<n>, T, Inc10<V> >{
    constexpr static VT val = VExpr<VT, Var<n>, T, V>::val + Expr<VT, Lit<Fib<10>>>::val;
};

template<typename VT>
struct Expr<VT, Lit<Fib<1>>> {
    constexpr static VT val = 1;
};

template<typename VT>
struct Expr<VT, Lit<Fib<2>>> {
    constexpr static VT val = 1;
};

template<typename VT, int n>
struct Expr<VT, Lit<Fib<n>>> {
    constexpr static VT val =
            Expr<VT, Lit<Fib<n-1>>>::val +
            Expr<VT, Lit<Fib<n-2>>>::val;
};

template<typename VT, typename ... T>
struct Expr<VT, Sum<T...>>{
    constexpr static VT val = (Expr<VT, T>::val + ...);
};

template<typename VT, typename T>
struct Expr<VT, Inc1<T>>{
    constexpr static VT val = Expr<VT, T>::val + Expr<VT, Lit<Fib<1>>>::val;
};

template<typename VT, typename T>
struct Expr<VT, Inc10<T>>{
    constexpr static VT val = Expr<VT, T>::val + Expr<VT, Lit<Fib<10>>>::val;
};

template <class VT>
struct Fibo {
    template <typename T>
    constexpr static VT eval() {
        return  Expr<VT, T>::val;
    }
};


#endif /* JNP1_4_FIBIN_H */
