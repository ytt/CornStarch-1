#ifndef INVITEEVENT_HPP_
#define INVITEEVENT_HPP_
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/InviteLog.hpp"

namespace CornStarch
{

class CInviteEvent: public CConnectionEventBase
{
    CInviteLog* m_serviceLog;
//    wxString m_channel; // チャンネル名
//    wxString m_user; // ユーザ名
public:
    CInviteEvent();
    virtual ~CInviteEvent();
//    wxString getChannel() const
//    {
//        return m_channel;
//    }
//
//    void setChannel(wxString channel)
//    {
//        m_channel = channel;
//    }
//
//    wxString getUser() const
//    {
//        return m_user;
//    }
//
//    void setUser(wxString user)
//    {
//        m_user = user;
//    }
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
