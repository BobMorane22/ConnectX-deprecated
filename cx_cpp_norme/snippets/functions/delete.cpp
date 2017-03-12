class Person
{

public:

	Person() = delete;

	Person(const std::string& p_name) : m_name{p_name}
	{
		//...
	}

private:

	std::string m_name;

};