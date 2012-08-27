#pragma once
#include "LogTextCtrl.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <vector>
#include "../../../Service/ServiceHolder.hpp"

namespace CornStarch
{;

// メッセージ一覧表示用ペイン
class CPaneRecord : public CLogTextCtrl
{
    static const int PANE_RECEVE_ID;

    // サーバー名を表示
    void pushServerName(const wxString& serviceName);
public:
    CPaneRecord(void);
    ~CPaneRecord(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // ログ一覧を表示
    void displayLogs(const std::vector<CMessage*>& logs,const CServiceHolder* services);


};

}
