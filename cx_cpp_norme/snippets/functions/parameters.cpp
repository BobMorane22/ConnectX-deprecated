// No need for references: default types
int max(int p_firstNumber, int p_secondNumber)
{
    int maximum{0};

    if(p_firstNumber < p_secondNumber)
    {
        maximum = p_secondNumber;
    }
    else
    {
        maximum = p_firstNumber;
    }

    return maximum;
}

// References needed: objects
std::string makeFullName(const std::string& p_firstName, 
                         const std::string& p_lastName)
{
    return p_firstName + " " + p_lastName;
}
