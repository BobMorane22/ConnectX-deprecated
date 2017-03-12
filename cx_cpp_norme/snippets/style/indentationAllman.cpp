// OK: Clear and well spaced-out
void Foo::aMethod(int p_x, int p_y)
{
	if(p_x == p_y)
	{
		doSomething();
		z++;
	}
	else
	{
		doSomethingElse();
		z--;
	}
}

// Not OK: Less clear and more error prone, esppecially for brace matching.
void Foo::aMethod(int p_x, int p_y){

	if(p_x == p_y){
		doSomething();
		m_z++;
	}
	else{
		doSomethingElse();
		m_z--;
	}
}