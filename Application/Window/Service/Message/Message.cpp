#include "Message.hpp"

namespace CornStarch
{
;

CMessage::CMessage(void) :
        m_channelName(""), m_nick(""), m_tempNick(""), m_userName("")
{
    m_time = time(NULL);
}

CMessage::~CMessage(void)
{
}

}
