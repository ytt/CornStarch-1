#include "PartStreamEvent.hpp"

using namespace std;

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
CPartStreamEvent::CPartStreamEvent(void)
{
    this->SetEventType(myEVT_THREAD_STREAM_CH_PART);
}


CPartStreamEvent::~CPartStreamEvent(void)
{
}

}
