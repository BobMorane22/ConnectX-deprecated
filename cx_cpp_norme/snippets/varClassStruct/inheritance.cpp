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

// Not OK, multiple inheritance (only one interface):
class Garply : public Foo, public IBar
{
	// Implementation...
};

// OK, multiple inheritance from interfaces:
class Quux : public IBar, public IBaz
{
	// Implementation (or nor)...
};