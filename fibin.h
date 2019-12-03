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

template <char*>
struct Var;

template <typename T>
struct Ref;

template <char* C>
struct Ref<Var<C>>;

template<typename VT, typename T>
struct Expr;

template<typename VT, typename A, typename B, typename C>
struct VExpr;

template<typename VT, typename T, char* C, typename V>
struct Expr<VT, Let<Var<C>, Expr<VT, T>, V>> {
    constexpr static VT val = Expr<VT, T>::val;
};

template<typename VT, typename T, char* C>
struct VExpr <VT, Var<C>, Expr<VT, T>, Ref<Var<C>> >{
    constexpr static VT val = Expr<VT, T>::val;
};

template<typename VT, typename T, char* C, typename ... V>
struct VExpr <VT, Var<C>, Expr<VT, T>, Sum <V...> >{
    constexpr static VT val = (VExpr<VT, Var<C>, Expr<VT, T>,V>::val + ...);
};

template<typename VT, typename T, char* C, int n>
struct VExpr <VT, Var<C>, Expr<VT, T>, Lit<Fib<n>> >{
    constexpr static VT val = Expr<VT, Lit<Fib<n>>>::val;
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

//template<typename VT, char* C, typename V, typename ... T>
//struct Expr<VT, Var<C>, Expr<VT, V>, Sum<T...>>{
//    constexpr static VT val = (Expr<VT, T>::val + ...);
//};


template <class VT>
struct Fibo {
    template <typename T>
    constexpr static VT eval() {
        return  Expr<VT, T>::val;
    }
};


#endif /* JNP1_4_FIBIN_H */
