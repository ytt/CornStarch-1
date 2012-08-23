#pragma once
#include "../../../../DataStruct/MessageData.hpp"
#include "../../../../DataStruct/MemberData.hpp"
#include <wx/wxprec.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>
#include <vector>
#include <map>
#include "../../../Service/NickTable.hpp"
#include "LogTextCtrl.hpp"

namespace CornStarch
{;

// メッセージ表示用ペイン
class CPaneMsg : public CLogTextCtrl
{
    static const int PANE_MSG_ID;
    static const wxColour COLOR_LIGHT_YELLOW;


    bool m_isScrollingBack;
    int m_beforeScroolHeight;
protected:
    void OnScroll(wxScrollWinEvent &event);
    // wxWindowイベントを処理させたいクラスに利用するマクロ
    DECLARE_EVENT_TABLE();

    void pushLog(const CMessageLog* messageLog);
public:
    void pushLog(const CServiceLog* log);

    CPaneMsg(void);
    ~CPaneMsg(void);

    // 初期化を行う
    void init(wxWindow* parent);
    // メッセージを再描画する
    void displayMessages(const std::vector<CServiceLog*>& messages,
        const CNickTable& nickTable);

//    // メッセージを追加する
//    void addMessage(const CMessageData* message,
//            const std::map<wxString, wxString>& nickTable);
    void clearUnreadBackgroundColor();
private:

    // ユーザ名に対応するニックネームを取得する
//    wxString getNickName(const wxString& userName,
//        const std::map<wxString, wxString>& nickTable);

    // 必要に応じて日付変更線を描画
    void drawDateLine(const wxString& now, const wxString& next);
};

}
