// No need to get the subject object:
void ChecksForIncrement::update(cxutil::ISubject* p_subject)
{
    (void)p_subject;
    m_hasBeenIncremented = true;
}

// Gets the subject object (Incrementer):
void CopiesIncrementerData::update(cxutil::ISubject* p_subject)
{
    Incrementer* incrementer {dynamic_cast<Incrementer*>(p_subject)};
    CX_ASSERT(incrementer != nullptr);
    
    m_data = incrementer->data();
}
