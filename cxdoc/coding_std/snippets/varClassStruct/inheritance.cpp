// OK, single inheritance:
class Qux : public Foo
{
    // Implementation...
};

// Not OK, multiple inheritance:
class Quux : public Foo, public Waldo
{
    // Implementation...
};

// OK, multiple inheritance (only one interface):
class Garply : public Foo, public IBar
{
    // Implementation...
};

// OK, multiple inheritance from interfaces:
class Quux : public IBar, public IBaz
{
    // Implementation (or not)...
};

// Not OK, multiple inheritance of two (2) abstract 
// classes which are not interfaces:
class Quuux : public Foo, Waldo
{
    //...
}
