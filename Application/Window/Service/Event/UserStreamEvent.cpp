#include "UserStreamEvent.hpp"

namespace CornStarch
{;
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);
CUserStreamEvent::CUserStreamEvent(void)
{
    this->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
}


CUserStreamEvent::~CUserStreamEvent(void)
{
}



}
