#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/PartLog.hpp"

namespace CornStarch
{
;

// チャンネルから誰かが離脱した際のイベント
class CPartStreamEvent: public CConnectionEventBase
{
    CPartLog* m_serviceLog;
public:
    CPartStreamEvent(void);
    ~CPartStreamEvent(void);

    CPartLog* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(CPartLog* serviceLog)
    {
        m_serviceLog = serviceLog;
    }
};

}
