#include "JoinStreamEvent.hpp"

using namespace std;

namespace CornStarch
{;
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
CJoinStreamEvent::CJoinStreamEvent(void)
{
   this->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
}


CJoinStreamEvent::~CJoinStreamEvent(void)
{
}



}
