#include "InviteEvent.hpp"

namespace CornStarch
{
wxDECLARE_EVENT(myEVT_THREAD_INVITE, CInviteEvent);
CInviteEvent::CInviteEvent()
{
    this->SetEventType(myEVT_THREAD_INVITE); // イベントの種類をセット
}

CInviteEvent::~CInviteEvent()
{
}

} /* namespace CornStarch */
