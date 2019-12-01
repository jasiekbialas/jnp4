#ifndef JNP1_4_FIBIN_H
#define JNP1_4_FIBIN_H

template <int N>
class Fib {
public:
    constexpr static unsigned long long value() {
        return Fib<N - 1>::value() + Fib<N - 2>::value();
    };
};

template <>
class Fib<0> {
public:
    constexpr static unsigned long long value() {
        return 0;
    }
};

template <>
class Fib<1> {
public:
    constexpr static unsigned long long value() {
        return 1;
    }
};

class True {};

class False {};

template <class T>
class Lit;

template <int n>
class Lit<Fib<n>> {
public:
    constexpr static unsigned long long value() {
        return Fib<n>::value();
    }
};

template <>
class Lit<True> {
public:
    constexpr static bool value() {
        return true;
    }
};

template <>
class Lit<False> {
public:
    constexpr static bool value() {
        return false;
    }
};

template <class T>
class Inc1 {
public:
    constexpr static unsigned long long value() {
        return T::value() + Fib<1>::value();
    }
};

template <class T>
class Inc10 {
public:
    constexpr static unsigned long long value() {
        return T::value() + Fib<10>::value();
    }
};

template <class T1, class T2>
class Eq {
public:
    constexpr static bool value() {
        return T1::value() == T2::value();
    }
};

#endif /* JNP1_4_FIBIN_H */
