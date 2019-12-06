//#include "fibin.h"
#include "fibin2.h"

#include <iostream>

using namespace std;

int main() {

    static_assert(4 == Fibin<int>::eval<Inc1<Sum<Lit<Fib<1>>, Lit<Fib<2>>, Inc1<Lit<Fib<0>>>>>>());
    static_assert(4181 == Fibin<int>::eval<Lit<Fib<19>>>());
    static_assert(112 == Fibin<int>::eval<Inc10<Inc1<Inc1<Lit<Fib<10>>>>>>());
    static_assert(61 == Fibin<uint8_t>::eval<Lit<Fib<17>>>());
    static_assert(59 == Fibin<uint64_t>::eval<Invoke<Lambda<Var("x"), Sum<Ref<Var("x")>, Inc10<Lit<Fib<1>>>, Lit<Fib<2>>>>, Lit<Fib<3>>>>());

    using Scoping =
    Let<
            Var("const"),
            Lit<Fib<9>>,
            Let<
                    Var("f"),
                    Lambda<
                            Var("x"),
                            Sum<
                                    Ref<Var("const")>,
                                    Ref<Var("x")>
                            >
                    >,
                    Let<
                            Var("const"),
                            Lit<Fib<10>>,
                            Invoke<
                                    Ref<Var("f")>,
                                    Lit<Fib<0>>
                            >
                    >
            >
    >;
    static_assert(34 == Fibin<int>::eval<Scoping>());
    static_assert(2 == Fibin<uint>::eval<Invoke<Let<Var("x"), Lit<Fib<1>>, Lambda<Var("x"), Ref<Var("x")> > >, Lit<Fib<3>> > >());

}
