#include "MessageLog.hpp"

using namespace std;

namespace CornStarch
{
;

CMessageLog::CMessageLog(void):m_isReaded(true),m_body("")
{
}

CMessageLog::~CMessageLog(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMessageLog::init(const CResponseData* message)
{
    this->setTempNick(message->m_tempNick);
    this->setUserName(message->m_username);
    this->setChannelName(message->m_channel);
    this->setTime(message->m_time);
    this->setBody(message->m_body);
    this->setId(message->m_id);
}


}
