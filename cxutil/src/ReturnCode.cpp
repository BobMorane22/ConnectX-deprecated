#include <cassert>
#include <iostream>

#include "ReturnCode.h"

using namespace cxutil;

const std::string ReturnCode::NO_MESSAGE { "" };

typedef ReturnCode::Code Code;

ReturnCode::ReturnCode( Code p_code, const std::string p_message )
{
}

ReturnCode::~ReturnCode()
{
    // The return code should have been tested
    // at least once:
    assert( m_tested );
}

bool ReturnCode::isOk()
{
    m_tested = true;

    return m_code == Code::OK;
}

bool ReturnCode::isWarning()
{
    m_tested = true;

    return m_code == Code::WARNING;
}

bool ReturnCode::isError()
{
    m_tested = true;

    return m_code == Code::ERROR;
}

bool ReturnCode::isCancelled()
{
    m_tested = true;

    return m_code == Code::CANCEL;
}

bool ReturnCode::holdsMessage() const
{
    return !m_message.empty();
}

bool ReturnCode::isTested() const
{
    return m_tested;
}

std::string ReturnCode::message() const
{
    return m_message;
}

Code ReturnCode::code() const
{
    return m_code;
}