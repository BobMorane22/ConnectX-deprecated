int main()
{
	// OK
	int aNewVariable{0};
	Foo someNewObject;

	// Not OK
	char MyChar{'a'};		// Not in camelCase.
	Bar  SOME_NEW_OBJECT;	// Not in camelCase and uses underscores.

	return 0;
}