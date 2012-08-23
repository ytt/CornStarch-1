#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{
;

// トピック変更のログ
class CTopicLog: public CServiceLog
{
private:
    wxString m_topic;
public:
    CTopicLog(void);
    ~CTopicLog(void);


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
