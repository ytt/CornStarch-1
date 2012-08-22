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
    static const int MAX_LENGTH = 256; // 時間表示形式の最大文字数
    wxString m_serviceName;
    wxString m_userName;
    wxString m_channelName;
    time_t m_time;

    int m_serviceId;

public:
    CServiceLog(void);
    virtual ~CServiceLog(void);
    virtual bool isUnknownNick(const wxString& name) const;
    virtual void updateNick(const wxString& nick);
    // 指定の形式で時刻を取得
    wxString getTime(const wxString& format) const
    {
        char buf[MAX_LENGTH];
        tm* timeStruct;

        // tm構造体形式に変換
        timeStruct = localtime(&m_time);

        // 表示形式を変換
        strftime(buf, sizeof(buf), format.c_str(), timeStruct);

        return wxString(buf);
    }
    wxString getChannelName() const
    {
        return m_channelName;
    }

    void setChannelName(wxString channelName)
    {
        m_channelName = channelName;
    }

    int getServiceId() const
    {
        return m_serviceId;
    }

    void setServiceId(int serviceId)
    {
        m_serviceId = serviceId;
    }

    time_t getTime() const
    {
        return m_time;
    }

    void setTime(time_t time)
    {
        m_time = time;
    }

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }

    wxString getServiceName() const
    {
        return m_serviceName;
    }

    void setServiceName(wxString serviceName)
    {
        m_serviceName = serviceName;
    }

}
;

}
