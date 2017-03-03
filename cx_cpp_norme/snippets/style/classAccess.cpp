// OK, everything is in order
class Foo
{
public:

	Foo();
	Foo(int p_value);

protected:
	void writeOverData(p_newValue);

private:
	int m_value;
};


// Not OK: private comes before public. Furthermore, it is useless here.
class Foo
{
private:

	int m_value;

public:

	Foo(int p_value);
};


// Not OK: public sections should be merged at the top.
class Foo
{
public:

	Foo(int p_value);

protected:
	void writeOverData(p_newValue);

private:
	int m_value;

public:
	Foo();
};