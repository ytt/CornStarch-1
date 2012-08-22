#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{
;

// トピック変更のログ
class CTopicLog: public CServiceLog
{
private:
    //CChannelData* m_channel;

    //new
    wxString m_topic;
public:
    CTopicLog(void);
    ~CTopicLog(void);

    // 初期化を行う
    void init(const CChannelData& channel);

//    // ログを取得する
//    CChannelData getLog(void) const;

    wxString getTopic() const
    {
        return m_topic;
    }

    void setTopic(wxString topic)
    {
        m_topic = topic;
    }
};

}
