#pragma once
#include <wx/string.h>
#include "../../../DataStruct/MessageData.hpp"

namespace CornStarch
{
;

// サービスのログを管理
class CServiceLog
{
    static const int MAX_LENGTH = 256;

    wxString m_nick;
    wxString m_tempNick;
    wxString m_userName;
    wxString m_channelName;
    time_t m_time;
    int m_serviceId;

public:
    CServiceLog(void);
    virtual ~CServiceLog(void);

    wxString getTempNick() const
    {
        return m_tempNick;
    }

    void setTempNick(wxString tempNick)
    {
        m_tempNick = tempNick;
    }

    wxString getNick() const
    {
        return m_nick;
    }

    void setNick(wxString nick)
    {
        m_nick = nick;
    }

    wxString getTime(const wxString& format) const
    {
        char buf[MAX_LENGTH];
        tm* timeStruct;
        timeStruct = localtime(&m_time);
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

}
;

}
