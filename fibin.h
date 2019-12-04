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

template<typename T>
struct Lit;

template<typename ... Args>
struct Sum;

template<long long N, typename Value, typename Expression>
struct Let;

template<long long N>
struct Ref;

template<typename T>
struct Inc1;

template<typename T>
struct Inc10;

template<long long N, typename Body>
struct Lambda;

template<typename Function, typename Parameter>
struct Invoke;

template<typename Condition, typename Expression_1, typename Expression_2>
struct If;

template<typename Expression_1, typename Expression_2>
struct Eq;

constexpr static long long Var(const char *str) {
    int i = 0, x = 0;
    long long result = 0, pow = 1;

    if ((str == NULL) || (str[i] == '\0')) {
        return -1;
    }

    while ((i < max_id_len) && (str[i] != '\0')) {
        x = (int) str[i];

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
            return -1;
        }

        result += x * pow;
        pow *= hash_const;
        i++;
    }

    if (str[i] != '\0') {
        return -1;
    }
    return result;
}

template<typename ValueType>
struct Fibin {
private:
    template<long long N>
    struct Id;

    template<bool Truth_value, typename Expression_1, typename Expression_2>
    struct Choose;

    template<typename T, typename Expression, typename ... Env>
    struct Expr;

    template<long long N, typename ... Env>
    struct FindInEnv;

    template<long long N, typename Value, typename ... Env>
    struct FindInEnv<N, Id<N>, Value, Env ...> {
        using found = Value;
    };

    template<long long N, long long M, typename Value, typename ... Env>
    struct FindInEnv<N, Id<M>, Value, Env ...> {
        using found = typename FindInEnv<N, Env ...>::found;
    };

    template<typename T, long long N, typename Value, typename ... Env>
    struct Expr<T, Invoke<Ref<N>, Value>, Env ...> {
        using function = typename FindInEnv<N, Env ...>::found;
        constexpr static ValueType val = Expr<T, Invoke<function, Value>, Env ...>::val;
    };

    template<typename T, long long N, typename Body, typename Value, typename ... Env>
    struct Expr<T, Invoke<Lambda<N, Body>, Value>, Env ...> {
        constexpr static ValueType val = Expr<T, Body, Id<N>, Value, Env ...>::val;
    };

    template<typename T, typename Expression, typename Dismiss, typename ... Env>
    struct Expr<T, Choose<true, Expression, Dismiss>, Env ...> {
        constexpr static ValueType val = Expr<T, Expression, Env ...>::val;
    };

    template<typename T, typename Dismiss, typename Expression, typename ... Env>
    struct Expr<T, Choose<false, Dismiss, Expression>, Env ...> {
        constexpr static ValueType val = Expr<T, Expression, Env ...>::val;
    };

    template<typename T, typename Condition, typename Expression_1,
             typename Expression_2, typename ... Env>
    struct Expr<T, If<Condition, Expression_1, Expression_2>, Env ...> {
        constexpr static ValueType val = Expr<T, Choose<Expr<T, Condition, Env ...>::val,
                                              Expression_1, Expression_2>, Env ...>::val;
    };

    template<typename T, typename Expression_1, typename Expression_2, typename ... Env>
    struct Expr<T, Eq<Expression_1, Expression_2>, Env ...> {
        constexpr static bool val = Expr<T, Expression_1, Env ...>::val ==
                                    Expr<T, Expression_2, Env ...>::val;
    };

    template<typename T, typename Value, long long N, typename Expression, typename ... Env>
    struct Expr<T, Let<N, Value, Expression>, Env ...> {
        constexpr static ValueType val = Expr<T, Expression, Id<N>, Value, Env ...>::val;
    };

    template<typename T, long long N, typename ... Env>
    struct Expr<T, Ref<N>, Env ...> {
        using expr = typename FindInEnv<N, Env ...>::found;
        constexpr static ValueType val = Expr<T, expr, Env ...>::val;
    };

    template<typename T, typename ... Env>
    struct Expr<T, Lit<True>, Env ...> {
        constexpr static bool val = true;
    };

    template<typename T, typename ... Env>
    struct Expr<T, Lit<False>, Env ...> {
        constexpr static bool val = false;
    };

    template<typename T, typename ... Env>
    struct Expr<T, Lit<Fib<0>>, Env ...> {
        constexpr static ValueType val = 0;
    };

    template<typename T, typename ... Env>
    struct Expr<T, Lit<Fib<1>>, Env ...> {
        constexpr static ValueType val = 1;
    };

    template<typename T, int N, typename ... Env>
    struct Expr<T, Lit<Fib<N>>, Env ...> {
        static_assert(N >= 0);
        constexpr static ValueType val =
                Expr<T, Lit<Fib<N - 1>>>::val +
                Expr<T, Lit<Fib<N - 2>>>::val;
    };

    template<typename T, typename ... U, typename ... Env>
    struct Expr<T, Sum<U ...>, Env ...> {
        // muszą być co najmniej dwa argumenty
        static_assert(sizeof ... (U) > 1);
        constexpr static ValueType val = (Expr<T, U, Env ...>::val + ...);
    };

    template<typename T, typename U, typename ... Env>
    struct Expr<T, Inc1<U>, Env ...> {
        constexpr static ValueType val =
                Expr<T, U, Env ...>::val + Expr<T, Lit<Fib<1>>>::val;
    };

    template<typename T, typename U, typename ... Env>
    struct Expr<T, Inc10<U>, Env ...> {
        constexpr static ValueType val = Expr<T, U, Env ...>::val +
                                         Expr<T, Lit<Fib<10>>>::val;
    };

public:
    template<typename T, typename U = ValueType,
             typename enable_if<!is_integral<U>::value, int>::type = 0>
    constexpr static void eval() {
        cout << "Fibin doesn't support: " << typeid(ValueType).name() << endl;
    }

    template<typename T, typename U = ValueType,
             typename enable_if<is_integral<U>::value, int>::type = 0>
    constexpr static ValueType eval() {
        return Expr<ValueType, T>::val;
    }
};

#endif /* JNP1_4_FIBIN_H */
