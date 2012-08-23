#ifndef INVITEEVENT_HPP_
#define INVITEEVENT_HPP_
#include "ConnectionEventBase.hpp"
#include "../LogHolder/InviteLog.hpp"

namespace CornStarch
{

class CInviteEvent: public CConnectionEventBase
{
    CInviteLog* m_serviceLog;
public:
    CInviteEvent();
    virtual ~CInviteEvent();
    CInviteLog* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(CInviteLog* serviceLog)
    {
        m_serviceLog = serviceLog;
    }
}



;

} /* namespace CornStarch */
#endif /* INVITEEVENT_HPP_ */
