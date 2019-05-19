class Base
{

public:
    virtual int foo() const
    {
        // ...
    }
};

class Derived : public Base
{

public:
    virtual int foo() override   // Oops! No const, so compilation fails...
    {
       // ...
    }
};
