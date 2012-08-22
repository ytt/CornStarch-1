#ifndef KICKLOG_HPP_
#define KICKLOG_HPP_
#include "ServiceLog.hpp"
namespace CornStarch
{;

class CKickLog:public CServiceLog
{

    wxString m_target; // ユーザ名
//    wxString m_channel; // チャンネル名
public:
    CKickLog();
    virtual ~CKickLog();

    // 初期化を行う
//    void init(const wxString& name, const wxString& channel);
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
//    wxString getUsername() const
//    {
//        return m_username;
//    }
//
//    void setUsername(wxString username)
//    {
//        m_username = username;
//    }

    wxString getTarget() const
    {
        return m_target;
    }

    void setTarget(wxString target)
    {
        m_target = target;
    }
};
}
#endif /* KICKLOG_HPP_ */
