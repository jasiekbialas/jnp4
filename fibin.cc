#include "fibin.h"

#include <iostream>

using namespace std;

int main() {

cout << Fib<19>::value() << endl;
cout << Lit<Fib<10>>::value() << endl;
cout << Lit<True>::value() << endl;
cout << Lit<False>::value() << endl;
cout << Inc1<Fib<19>>::value() << endl;
cout << Inc1<Lit<False>>::value() << endl;
cout << Inc10<Inc1<Lit<False>>>::value() << endl;
cout << Eq<Lit<Fib<0>>, Lit<Fib<1>>>::value() << endl;

}
