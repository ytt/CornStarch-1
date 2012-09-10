#include "MainNotifier.hpp"
#include "../Service/StringUtility.hpp"
namespace CornStarch
{
;

CMainNotifier::CMainNotifier(void)
#ifdef _WIN32
:m_taskbar(NULL)
#endif
{
}

CMainNotifier::~CMainNotifier(void)
{
#ifdef _WIN32
    delete m_taskbar;
#endif
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainNotifier::init(wxWindow* parent)
{
#ifdef _WIN32
    m_taskbar = new wxTaskBarIcon();
    m_taskbar->SetIcon(wxIcon());
#endif
}

// 通知を行う
void CMainNotifier::messageNotify(const wxString& title,
        const wxString& message)
{
#ifdef _WIN32
    m_taskbar->ShowBalloon(title, message, 15000, wxICON_INFORMATION);
#else
    wxString replacedTitle = CStringUtility::escape(title);
    wxString replacedMessage = CStringUtility::escape(message);
    system(
            wxString::Format(
                    "/usr/local/bin/growlnotify -t \"%s\" -a CornStarch -m \"%s\"",
                    replacedTitle, replacedMessage));
#endif
}

}
