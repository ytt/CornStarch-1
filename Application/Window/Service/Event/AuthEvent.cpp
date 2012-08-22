#include "AuthEvent.hpp"

namespace CornStarch
{;
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
CAuthEvent::CAuthEvent(void)
{
    this->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
}


CAuthEvent::~CAuthEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// 認証の成否をセット
void CAuthEvent::setAuthResult(bool auth)
{
    m_auth = auth;
}

// 認証の成否を取得
bool CAuthEvent::isAuthSucceeded(void) const
{
    return m_auth;
}

}
