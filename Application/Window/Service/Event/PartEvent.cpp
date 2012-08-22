#include "PartEvent.hpp"

namespace CornStarch
{
;
wxDECLARE_EVENT(myEVT_THREAD_DELETE_PART, CPartEvent);
CPartEvent::CPartEvent()
{
    this->SetEventType(myEVT_THREAD_DELETE_PART); // イベントの種類をセット
}

CPartEvent::~CPartEvent()
{
}

}
