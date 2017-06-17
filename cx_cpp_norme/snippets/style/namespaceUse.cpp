#include <iostream>

// No tricks:
std::cout << "No tricks: the scope must be added."; // or
STD::cout << "We can add it with a MACRO as well.";

// With using directives:
using namespace std;
cout << "Using directive"; // or

USING_NAMESPACE_STD
cout << "Using directive hidden in a MACRO";

// and so on...


