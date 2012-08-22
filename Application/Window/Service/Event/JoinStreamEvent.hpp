#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/JoinLog.hpp"

namespace CornStarch
{
;

// チャンネルに誰かが参加した際のイベント
class CJoinStreamEvent: public CConnectionEventBase
{
//private:
//    wxString m_channel; // チャンネル名
//    wxString m_user; // ユーザ名
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
//    // チャンネル名をセット
//    void setChannelName(const wxString& channel);
//
//    // ユーザ名をセット
//    void setUserName(const wxString& userName);
//
//    // チャンネル名を取得
//    wxString getChannelName(void) const;
//
//    // ユーザ名を取得
//    wxString getUserName(void) const;
};

}
