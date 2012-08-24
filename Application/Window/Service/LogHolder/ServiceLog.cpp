#include "ServiceLog.hpp"

namespace CornStarch
{
;

CServiceLog::CServiceLog(void) :
        m_channelName(""), m_nick(""), m_tempNick(""), m_userName("")
{
    m_time = time(NULL);
}

CServiceLog::~CServiceLog(void)
{
}

}
