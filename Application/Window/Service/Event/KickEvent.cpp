#include "KickEvent.hpp"
namespace CornStarch
{

wxDECLARE_EVENT(myEVT_THREAD_KICK, CKickEvent);
CKickEvent::CKickEvent()
{
    this->SetEventType(myEVT_THREAD_KICK); // イベントの種類をセット
}

CKickEvent::~CKickEvent()
{

}
}
