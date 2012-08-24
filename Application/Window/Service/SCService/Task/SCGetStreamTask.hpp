#pragma once
#include "SCTask.hpp"
#include "../SCResponseData.hpp"

namespace CornStarch
{
;
// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_DISCONNECT, CDisconnectEvent);

namespace StarChat
{
;

// ストリームを受信するためのタスク
class CSCGetStreamTask: public CSCTask
{
private:
    wxString m_userName;

public:
    CSCGetStreamTask(void);
    ~CSCGetStreamTask(void);

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }

private:
    ExitCode Entry(void);
    CSCResponseData* parseStream(const std::string& json);
};

}
}
