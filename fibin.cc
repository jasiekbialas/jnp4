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

}
