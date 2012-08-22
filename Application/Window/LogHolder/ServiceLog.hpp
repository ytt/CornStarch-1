#pragma once
#include <wx/string.h>
#include "../../DataStruct/MemberData.hpp"
#include "../../DataStruct/MessageData.hpp"
#include "../../DataStruct/SubscribeData.hpp"
#include "../../DataStruct/ChannelData.hpp"

namespace CornStarch
{
;

// チャットのログを管理
class CServiceLog
{
    wxString m_serviceName;
    wxString m_userName;
    wxString m_channelName;
    time_t m_time; // UNIX時間
    int m_serviceId;

//public:
//    // チャットログのタイプ
//    enum LOG_TYPE
//    {
//        LOG_MESSAGE, LOG_JOIN, LOG_PART, LOG_TOPIC, LOG_USER, LOG_INVITE,
//        LOG_KICK
//    };

//protected:
//    LOG_TYPE m_type; // ログのタイプ

public:
    CServiceLog(void);
    virtual ~CServiceLog(void);

//    // ログの種類を取得
//    LOG_TYPE getLogType(void) const;

    // 本名に対応するニックネームが未知か
    virtual bool isUnknownNick(const wxString& name) const;

    // ニックネームを更新する
    virtual void updateNick(const wxString& nick);

    wxString getServiceName() const
    {
        return m_serviceName;
    }

    void setServiceName(wxString serviceName)
    {
        m_serviceName = serviceName;
    }
};

}
