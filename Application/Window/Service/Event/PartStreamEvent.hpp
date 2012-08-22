#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/PartLog.hpp"

namespace CornStarch
{
;

// チャンネルから誰かが離脱した際のイベント
class CPartStreamEvent: public CConnectionEventBase
{
//private:
//    wxString m_channel; // チャンネル名
//    wxString m_user; // ユーザ名

    CPartLog* m_serviceLog;
public:
    CPartStreamEvent(void);
    ~CPartStreamEvent(void);

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
