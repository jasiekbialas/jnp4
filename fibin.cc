#include "fibin.h"

#include <iostream>

using namespace std;

int main() {

/*cout << Fib<19>::value() << endl;
cout << Lit<Fib<10>>::value() << endl;
cout << Lit<True>::value() << endl;
cout << Lit<False>::value() << endl;
cout << Inc1<Fib<19>>::value() << endl;
cout << Inc1<Lit<False>>::value() << endl;
cout << Inc10<Inc1<Lit<False>>>::value() << endl;
cout << Eq<Lit<Fib<0>>, Lit<Fib<1>>>::value() << endl;*/
cout << Fibin<int>::eval<Inc10<Inc1<Lit<Fib<10>>>>>() << endl;
Fibin<const char*>::eval<Inc1<Lit<Fib<10>>>>();

static_assert(1 == Fibin<uint8_t>::eval<If<Lit<False>, Lit<Fib<0>>, Lit<Fib<1>>>>());

static_assert(59 == Fibin<uint64_t>::eval<Invoke<Lambda<Var<1>,
            Sum<Ref<Var<1>>, Inc10<Lit<Fib<1>>>, Lit<Fib<2>>>>, Lit<Fib<3>>>>());
static_assert(1 == Fibin<int16_t>::eval<Let<Var<3>, Lit<Fib<0>>, Inc1<Ref<Var<3>>>>>());
}
