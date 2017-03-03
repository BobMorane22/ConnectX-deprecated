int main()
{
	// OK
	const double PI{3.1416};
	const std::string FRENCH_SALUTATION{"Bonjour"};

	// Not OK
	const char MyChar{'a'};		// Not in UPPERCASE.
	const Bar  SOME-NEW-OBJECT;	// Does not use underscores.
	const Foo  SomeNewObject;   // Not in UPPERCASE and does 
								// not use underscores.

	return 0;
}