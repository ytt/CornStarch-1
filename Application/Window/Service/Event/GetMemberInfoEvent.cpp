#include "GetMemberInfoEvent.hpp"

namespace CornStarch
{
;
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);
CGetMemberInfoEvent::CGetMemberInfoEvent(void) :
        m_member(NULL)
{
    this->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
}

CGetMemberInfoEvent::~CGetMemberInfoEvent(void)
{
    delete m_member;
}

//////////////////////////////////////////////////////////////////////

// チャンネルをセット
void CGetMemberInfoEvent::setMember(const CMemberData& member)
{
    if (m_member == NULL){
        m_member = new CMemberData();
    }

    *m_member = member;
}

// チャンネルを取得
CMemberData CGetMemberInfoEvent::getMember(void) const
{
    return *m_member;
}

}
