#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/MemberLog.hpp"

namespace CornStarch
{
;

// ユーザ情報更新時のイベント
class CUserStreamEvent: public CConnectionEventBase
{
    CMemberLog* m_serviceLog;
public:
    CUserStreamEvent(void);
    ~CUserStreamEvent(void);
    CMemberLog* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(CMemberLog* serviceLog)
    {
        this->m_serviceLog = serviceLog;
    }
};

}
