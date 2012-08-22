#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/TopicLog.hpp"

namespace CornStarch
{
;

// チャンネル情報更新時のイベント
class CChannelStreamEvent: public CConnectionEventBase
{
//private:
//    CChannelData* m_channelData; // チャンネル情報
    CTopicLog* m_serviceLog;
public:
    CChannelStreamEvent(void);
    ~CChannelStreamEvent(void);
    CTopicLog* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(CTopicLog* serviceLog)
    {
        m_serviceLog = serviceLog;
    }
//
//    // チャンネルを取得する
//    CChannelData getChannel(void) const;
//
//    // チャンネルをセットする
//    void setChannel(const CChannelData& channel);
}

;

}
