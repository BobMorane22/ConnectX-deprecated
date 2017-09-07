class Incrementer : public cxutil::ISubject
{
public:

    Incrementer(){}
    ~Incrementer() = default;
    
    void increment()
    {
        ++m_data;
        notifyObservers(); // Registered observers notified here!
    }
    
    int data() const {return m_data;}
    
private:

    int m_data{0};
};
