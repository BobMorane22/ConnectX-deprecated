class Person
{

public:

	Person(const std::string& p_name) : m_name{p_name}
	{
		//...
	}

	// code...

	std::string tellName() const {return m_name;} // preferred

private:

	std::string m_name;

};