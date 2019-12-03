#ifndef JNP1_4_FIBIN_H
#define JNP1_4_FIBIN_H

#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

struct True;
struct False;

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

template <typename A, typename B>
struct Lambda;

template <typename A, typename B>
struct Invoke;

template<typename A, typename B, typename C>
struct If;

template<bool b, typename B, typename C>
struct Choose;

template<typename A, typename B>
struct Eq;

template<typename VT, typename T, typename ...R>
struct Expr;

template<typename VT, typename A, int n, typename B, typename ...R>
struct Expr<VT, Invoke<Lambda<Var<n>, A>, B> ,R...> {
    constexpr static VT val = Expr<VT, A, Var<n>, B, R...>::val;
};

template<typename VT, typename B, typename C, typename ...R>
struct Expr<VT, Choose<true, B, C>, R...> {
    constexpr static VT val = Expr<VT, B, R...>::val;
};

template<typename VT, typename B, typename C, typename ...R>
struct Expr<VT, Choose<false, B, C>, R...> {
    constexpr static VT val = Expr<VT, C, R...>::val;
};

template<typename VT, typename A, typename B, typename C, typename ...R>
struct Expr<VT, If<A, B, C>, R...> {
    constexpr static VT val = Expr<VT, Choose<Expr<VT, A, R...>::val, B, C>, R...>::val;
};

template<typename VT, typename A, typename B, typename ...R>
struct Expr<VT, Eq<A, B>, R...>{
    constexpr static bool val = Expr<VT, A, R...>::val == Expr<VT, B, R...>::val;
};

template<typename VT, typename T, int n, typename V, typename ...R>
struct Expr<VT, Let<Var<n>,  T, V>, R...> {
    constexpr static VT val = Expr<VT, V, Var<n>, T, R...>::val;
};

template<typename VT, typename T, int n, typename ...R>
struct Expr <VT, Ref<Var<n>>, Var<n>, T, R... >{
    constexpr static VT val = Expr<VT, T>::val;
};

template <typename VT, typename ...R>
struct Expr<VT, Lit<True>, R...> {
    constexpr static bool val = true;
};

template <typename VT, typename ...R>
struct Expr<VT, Lit<False>, R...> {
    constexpr static bool val = false;
};

template<typename VT, typename ...R>
struct Expr<VT, Lit<Fib<1>>, R...> {
    constexpr static VT val = 1;
};

template<typename VT, typename ...R>
struct Expr<VT, Lit<Fib<2>>, R...> {
    constexpr static VT val = 1;
};

template<typename VT, int n, typename ...R>
struct Expr<VT, Lit<Fib<n>>, R...> {
    constexpr static VT val =
            Expr<VT, Lit<Fib<n-1>>>::val +
            Expr<VT, Lit<Fib<n-2>>>::val;
};

template<typename VT, typename ... T, typename ...R>
struct Expr<VT, Sum<T...>, R...>{
    constexpr static VT val = (Expr<VT, T, R...>::val + ...);
};

template<typename VT, typename T, typename  ...R>
struct Expr<VT, Inc1<T>, R...>{
    constexpr static VT val = Expr<VT, T, R...>::val + Expr<VT, Lit<Fib<1>> >::val;
};

template<typename VT, typename T, typename ...R>
struct Expr<VT, Inc10<T>, R...>{
    constexpr static VT val = Expr<VT, T, R...>::val + Expr<VT, Lit<Fib<10>>>::val;
};

template <class VT>
struct Fibin {
    template <typename T, typename U = VT, typename enable_if<!is_integral<U>::value, int>::type = 0>
    constexpr static void eval() {
        cout << "Fibin doesn't support: " << typeid(VT).name() << endl;
    }

    template <typename T, typename U = VT, typename enable_if<is_integral<U>::value, int>::type = 0>
    constexpr static VT eval() {
        return  Expr<VT, T>::val;
    }
};


#endif /* JNP1_4_FIBIN_H */
