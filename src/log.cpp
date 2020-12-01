#include "log.h"

Log::Log(std::ostream& cout):
    m_cout(cout),
    m_print(true),
    m_quitOnMessageEnd(false)
{
}

Log::Log(Log const& other):
    m_cout(other.m_cout),
    m_quitOnMessageEnd(other.m_quitOnMessageEnd)
{
}

Log::~Log()
{
    if(m_print) m_cout << std::endl;

    if(m_quitOnMessageEnd)
    {
        std::exit(EXIT_FAILURE);
    }
}

Log Log::ensure(bool test)
{
    Log ret = Log(std::cerr);
    if(test)
        ret.m_print = false;
    else
        ret.m_quitOnMessageEnd = true;
    return ret;
}
