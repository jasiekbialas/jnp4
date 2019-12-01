#ifndef JNP1_4_FIBIN_H
#define JNP1_4_FIBIN_H

template <int N>
class Fib {
public:
    constexpr static unsigned long long value() {
        static_assert(N >= 0);
        if (N == 0) {
            return 0;
        } else if (N == 1) {
            return 1;
        } else {
            unsigned long long first = 0;
            unsigned long long second = 1;
            unsigned long long result = 1;

            for (int i = 0; i < N - 1; i++) {
                result = first + second;
                first = second;
                second = result;
            }

            return result;
        }
    };
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
