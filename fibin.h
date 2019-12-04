#ifndef JNP1_4_FIBIN_H
#define JNP1_4_FIBIN_H

#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

const int max_id_len = 6;
const int hash_const = 37;

struct True;
struct False;

template<int N>
struct Fib;

template <typename T>
struct Lit;

template<typename ... Args>
struct Sum;

template <int N, typename Value, typename Expresion>
struct Let;

template <int N>
struct Id;

template <int N>
struct Ref;

template <typename T>
struct Inc1;

template <typename T>
struct Inc10;

template <int N, typename Body>
struct Lambda;

template <typename Function, typename Parameter>
struct Invoke;

template<typename Condition, typename Expression_1, typename Expression_2>
struct If;

template<bool truth_value, typename Expression_1, typename Expression_2>
struct Choose;

template<typename Expression_1, typename Expression_2>
struct Eq;

template<typename ValueType, typename Expression, typename ...Env>
struct Expr;

template <int N, typename ...Env>
struct FindInEnv;

template<int N, typename Value, typename ...Env>
struct FindInEnv<N, Id<N>, Value, Env...> {
    using found = Value;
};

template<int N, int M,  typename Value, typename ...Env>
struct FindInEnv<N, Id<M>, Value, Env...> {
    using found = typename FindInEnv<N, Env...>::found;
};

template<typename ValueType, int N, typename Value, typename ...Env>
struct Expr<ValueType, Invoke<Ref<N>, Value>, Env...> {
    using function = typename FindInEnv<N, Env...>::found;
    constexpr static ValueType val = Expr<ValueType, Invoke<function, Value>, Env...>::val;
};

template<typename ValueType, int N, typename Body, typename Value, typename ...Env>
struct Expr<ValueType, Invoke<Lambda<N, Body>, Value> ,Env...> {
    constexpr static ValueType val = Expr<ValueType, Body, Id<N>, Value, Env...>::val;
};

template<typename ValueType, typename Expression, typename Dismiss, typename ...Env>
struct Expr<ValueType, Choose<true, Expression, Dismiss>, Env...> {
    constexpr static ValueType val = Expr<ValueType, Expression, Env...>::val;
};

template<typename ValueType, typename Dissmis, typename Expression, typename ...Env>
struct Expr<ValueType, Choose<false, Dissmis, Expression>, Env...> {
    constexpr static ValueType val = Expr<ValueType, Expression, Env...>::val;
};

template<typename ValueType, typename Condition, typename Expression_1, typename Expression_2, typename ...Env>
struct Expr<ValueType, If<Condition, Expression_1, Expression_2>, Env...> {
    constexpr static ValueType val = Expr<ValueType, Choose<Expr<ValueType, Condition, Env...>::val, Expression_1, Expression_2>, Env...>::val;
};

template<typename ValueType, typename Expr_1, typename Expr_2, typename ...Env>
struct Expr<ValueType, Eq<Expr_1, Expr_2>, Env...>{
    constexpr static bool val = Expr<ValueType, Expr_1, Env...>::val == Expr<ValueType, Expr_2, Env...>::val;
};

template<typename ValueType, typename Value, int N, typename Expression, typename ...Env>
struct Expr<ValueType, Let<N, Value, Expression>, Env...> {
    constexpr static ValueType val = Expr<ValueType, Expression, Id<N>, Value, Env...>::val;
};

template<typename ValueType, int N, typename ...Env>
struct Expr <ValueType, Ref<N>, Env... >{

    using expr = typename FindInEnv<N, Env...>::found;
    constexpr static ValueType val = Expr<ValueType, expr, Env...>::val;
};

template <typename ValueType, typename ...Env>
struct Expr<ValueType, Lit<True>, Env...> {
    constexpr static bool val = true;
};

template <typename ValueType, typename ...Env>
struct Expr<ValueType, Lit<False>, Env...> {
    constexpr static bool val = false;
};

template<typename ValueType, typename ...Env>
struct Expr<ValueType, Lit<Fib<0>>, Env...> {
    constexpr static ValueType val = 0;
};

template<typename ValueType, typename ...Env>
struct Expr<ValueType, Lit<Fib<1>>, Env...> {
    constexpr static ValueType val = 1;
};

template<typename ValueType, int n, typename ...Env>
struct Expr<ValueType, Lit<Fib<n>>, Env...> {
    constexpr static ValueType val =
            Expr<ValueType, Lit<Fib<n-1>>>::val +
            Expr<ValueType, Lit<Fib<n-2>>>::val;
};

template<typename ValueType, typename ... T, typename ...Env>
struct Expr<ValueType, Sum<T...>, Env...>{
    constexpr static ValueType val = (Expr<ValueType, T, Env...>::val + ...);
};

template<typename ValueType, typename T, typename  ...Env>
struct Expr<ValueType, Inc1<T>, Env...>{
    constexpr static ValueType val = Expr<ValueType, T, Env...>::val + Expr<ValueType, Lit<Fib<1>> >::val;
};

template<typename ValueType, typename T, typename ...Env>
struct Expr<ValueType, Inc10<T>, Env...>{
    constexpr static ValueType val = Expr<ValueType, T, Env...>::val + Expr<ValueType, Lit<Fib<10>>>::val;
};

template <class ValueType>
struct Fibin {
    template <typename T, typename U = ValueType, typename enable_if<!is_integral<U>::value, int>::type = 0>
    constexpr static void eval() {
        cout << "Fibin doesn't support: " << typeid(ValueType).name() << endl;
    }

    template <typename T, typename U = ValueType, typename enable_if<is_integral<U>::value, int>::type = 0>
    constexpr static ValueType eval() {
        return  Expr<ValueType, T>::val;


    }
};

constexpr static int hash_char(const char c) {
    char x = c;
    if (x >= 'A' && x <= 'Z') {
        x -= 'A';
        x += 1;
    } else if (x >= 'a' && x <= 'z') {
        x -= 'a';
        x += 1;
    } else if (x >= '0' && x <= '9') {
        x -= '0';
        x += ('z' - 'a') + 1;
    } else {
        x = -1;
    }

    return x;
}

constexpr static int Var(const char *str) {
    int result = 0;
    int pow = 1;
    char c = ' ';

    for (int i = 0; str[i] != '\0'; i++) {
        c = hash_char(str[i]);
        if (c == -1 || i >= max_id_len) {
            return -1;
        }
        result += hash_char(str[i]) * pow;
        pow *= hash_const;
    }

    return result;
}


#endif /* JNP1_4_FIBIN_H */
