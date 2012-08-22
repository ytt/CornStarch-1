#include "GetMemberEvent.hpp"

using namespace std;

namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
CGetMemberEvent::CGetMemberEvent(void)
{
    this->SetEventType(myEVT_THREAD_GET_MEMBER); // イベントの種類をセット
}

CGetMemberEvent::~CGetMemberEvent(void)
{
    int size = (int) (m_members.size());
    for (int i = 0; i < size; i++){
        delete m_members[i];
    }
}
wxString CGetMemberEvent::getChannel() const
{
    return m_channel;
}

void CGetMemberEvent::setChannel(wxString channel)
{
    m_channel = channel;
}
void CGetMemberEvent::setMembers(const vector<CMemberData*>& members)
{
    m_members = members;
}

vector<CMemberData*> CGetMemberEvent::getMembers(void) const
{
    return m_members;
}

}

