#include "ChannelStreamEvent.hpp"

using namespace std;

namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
CChannelStreamEvent::CChannelStreamEvent(void)
{
    this->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
}

CChannelStreamEvent::~CChannelStreamEvent(void)
{
}


}
