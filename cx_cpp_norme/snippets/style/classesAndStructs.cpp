// OK
class Foo
{
public:
	Foo(int p_value);

private:
	int m_value;
};

// OK
struct Bar
{
	int m_firstValue;
	int m_secondValue;
};

// Not OK. Could be mistaken for a variable name.
class foo
{
public:
	Foo(int p_value);

private:
	int m_value;
};
