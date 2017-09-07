// First observer:
class ChecksForIncrement : public cxutil::IObserver
{
public:

    ChecksForIncrement(){}
    ~ChecksForIncrement() = default;
    
    void update(cxutil::ISubject* p_subject)
    {
        (void)p_subject;
        m_hasBeenIncremented = true;
    }
    
    bool hasBeenIncremented() const {return m_hasBeenIncremented;}
    
private:

    bool m_hasBeenIncremented{false};
};

// Second observer:
class CopiesIncrementerData : public cxutil::IObserver
{
public:

    CopiesIncrementerData(){}
    ~CopiesIncrementerData() = default;
    
    void update(cxutil::ISubject* p_subject)
    {
        Incrementer* incrementer {dynamic_cast<Incrementer*>(p_subject)};
        CX_ASSERT(incrementer != nullptr);
        
        m_data = incrementer->data();
    }
    
    int data() const {return m_data;}
    
private:

    int m_data{0};
};
