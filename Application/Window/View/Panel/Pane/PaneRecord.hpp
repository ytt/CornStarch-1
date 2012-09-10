#pragma once
#include "LogTextCtrl.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <vector>
#include "../../../Service/ServiceHolder.hpp"
#include "MessageControlDoubleClickedEvent.hpp"

namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_MESSAGE_CONTROL_DOUBLECLICKED,CMessageControlDoubleClickedEvent);
// メッセージ一覧表示用ペイン
class CPaneRecord: public CLogTextCtrl
{
    static const int PANE_RECEVE_ID;
    DECLARE_EVENT_TABLE()
        ;
    void onDoubleClicked(wxMouseEvent& event);
    // サーバー名を表示
    void pushServerName(const wxString& serviceName);

    // 選択しているテキストからサービス名を取得
    wxString getServiceNameFromSelectedText(const wxString lineText);
    // 選択しているテキストからチャンネル名を取得
    wxString getChannelNameFromSelectedText(const wxString lineText);
public:

    CPaneRecord(void);
    ~CPaneRecord(void);
    // 初期化を行う
    void init(wxWindow* parent);

    // ログ一覧を表示
    void displayLogs(const std::vector<CMessage*>& logs,
            const CServiceHolder* services);

};

}
