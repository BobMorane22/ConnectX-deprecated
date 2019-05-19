std::string myString{"some text..."};

// Could be better...
for(int i = 0; i < myString.size(); ++i)
{
	std::cout << myString[i];
}

// Better...
string::iterator it;

for(it = myString.begin(); it != myString.end(); ++it)
{
    cout << *it;
}

// Awesome!
for(auto& letter : myString)
{
    cout << letter;
}


