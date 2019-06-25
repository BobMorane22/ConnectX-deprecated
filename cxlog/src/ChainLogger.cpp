#include "../include/ChainLogger.h"

void cxlog::ChainLogger::setSucessor(std::unique_ptr<ILogger>&& p_sucessor)
{
    m_successor = std::move(p_sucessor);
}

bool cxlog::ChainLogger::hasSucessor() const
{
    if(m_successor != nullptr)
    {
        return true;
    }

    return false;
}
