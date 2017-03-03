// ---------------------------------------------
// Foo.h: Foo class interface.
// ---------------------------------------------
class Foo
{
public:

	Foo();
	void aMethod();

private:

	int m_attribute;
};


// ---------------------------------------------
// Foo.cpp: Foo class method implementations.
// ---------------------------------------------
Foo::Foo() : m_attribute{0}
{
	// Other potential work here...
}

void Foo::aMethod()
{
	// Some stuff...
}


// ---------------------------------------------
// test_Foo.cpp: All Foo's unit tests.
// ---------------------------------------------
TEST(Foo, SomeTest)
{
	// Test here...
}