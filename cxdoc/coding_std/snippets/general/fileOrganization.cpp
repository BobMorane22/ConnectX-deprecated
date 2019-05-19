// Foo.cpp (excluded from build):
template<typename T>
T Foo<T>::doSomething()
{
    // code...
}

// Foo.h
template<typename T> 
class Foo
{
public:

    T doSomething();

private:

    T m_anAttribute;
};

#include "Foo.cpp" // Important!
