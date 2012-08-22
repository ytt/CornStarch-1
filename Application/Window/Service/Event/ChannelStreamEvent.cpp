#include "ChannelStreamEvent.hpp"

using namespace std;

namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
CChannelStreamEvent::CChannelStreamEvent(void) :
        m_channelData(NULL)
{
    this->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
}

CChannelStreamEvent::~CChannelStreamEvent(void)
{
    delete m_channelData;
}

//////////////////////////////////////////////////////////////////////

// チャンネルを取得する
CChannelData CChannelStreamEvent::getChannel(void) const
{
    return *m_channelData;
}

// チャンネルをセットする
void CChannelStreamEvent::setChannel(const CChannelData& channel)
{
    if (m_channelData == NULL){
        m_channelData = new CChannelData();
    }

    *m_channelData = channel;
}

}
