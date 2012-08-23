#ifndef KICKEVENT_HPP_
#define KICKEVENT_HPP_
#include "ConnectionEventBase.hpp"
#include "../LogHolder/KickLog.hpp"

namespace CornStarch
{
class CKickEvent: public CConnectionEventBase
{
    CKickLog* m_serviceLog;
public:
    CKickEvent();
    virtual ~CKickEvent();


    CKickLog* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(CKickLog* serviceLog)
    {
        m_serviceLog = serviceLog;
    }
};
}
#endif /* KICKEVENT_HPP_ */
