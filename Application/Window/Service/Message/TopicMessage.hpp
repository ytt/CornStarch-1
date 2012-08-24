#pragma once
#include "Message.hpp"

namespace CornStarch
{
;

// トピック変更のログ
class CTopicMessage: public CMessage
{
private:
    wxString m_topic;
public:
    CTopicMessage(void);
    ~CTopicMessage(void);


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
