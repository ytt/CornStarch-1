#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/JoinLog.hpp"

namespace CornStarch
{
;

// チャンネルに誰かが参加した際のイベント
class CJoinStreamEvent: public CConnectionEventBase
{
    CJoinLog* m_serviceLog;
public:
    CJoinStreamEvent(void);
    ~CJoinStreamEvent(void);

    CJoinLog* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(CJoinLog* serviceLog)
    {
        m_serviceLog = serviceLog;
    }
};

}
