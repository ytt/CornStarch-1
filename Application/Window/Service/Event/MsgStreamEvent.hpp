#pragma once
#include "ConnectionEventBase.hpp"
#include "../LogHolder/MessageLog.hpp"

namespace CornStarch
{
;

// メッセージ受信時のイベント
class CMsgStreamEvent: public CConnectionEventBase
{
    CMessageLog* m_sericeLog;
public:
    CMsgStreamEvent(void);
    ~CMsgStreamEvent(void);
    CMessageLog* getServiceLog() const
    {
        return m_sericeLog;
    }

    void setServiceLog(CMessageLog* serverLog)
    {
        m_sericeLog = serverLog;
    }
}

;

}
