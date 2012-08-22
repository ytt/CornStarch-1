#include "MsgStreamEvent.hpp"

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
CMsgStreamEvent::CMsgStreamEvent(void)
{
   this->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
}


CMsgStreamEvent::~CMsgStreamEvent(void)
{
}


}
