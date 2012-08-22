#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/taskbar.h>

namespace CornStarch
{;

// 通知を行う
class CMainNotifier
{
private:
#ifdef _WIN32
    wxTaskBarIcon* m_taskbar; // タスクバー
#endif
   // wxNotificationMessage* m_message;
public:
    CMainNotifier(void);
    ~CMainNotifier(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // 通知を行う
    void messageNotify(const wxString& title, const wxString& message);
};

}
