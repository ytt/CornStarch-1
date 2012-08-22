#ifndef KICKEVENT_HPP_
#define KICKEVENT_HPP_
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/KickLog.hpp"

namespace CornStarch
{
class CKickEvent: public CConnectionEventBase
{
//    wxString m_channel; // チャンネル名
//    wxString m_user; // ユーザ名
    CKickLog* m_serviceLog;
public:
    CKickEvent();
    virtual ~CKickEvent();
//
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
