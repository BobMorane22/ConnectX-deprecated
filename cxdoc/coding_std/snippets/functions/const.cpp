// Person.h
class Person
{

public:

    Person(const std::string& p_name) : m_name{p_name}
    {
        //...
    }

    // code...
    bool checkName(const std::string& p_aName) const

private:

    std::string m_name;

};

// Person.cpp
bool checkName(const std::string& p_aName) const
{
    return m_name = p_aName; // Oops: forgotten "="! Compilation fails
}
