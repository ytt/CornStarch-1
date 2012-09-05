#pragma once
#include "../../../../DataStruct/MemberData.hpp"
#include <wx/wxprec.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>
#include <vector>
#include <map>
#include "../../../Service/NickTable.hpp"
#include "LogTextCtrl.hpp"
#include "../../../Service/ServiceConfiguration.hpp"

namespace CornStarch
{
;

// メッセージ表示用ペイン
class CPaneMsg: public CLogTextCtrl
{
    static const wxColour COLOR_LIGHT_YELLOW;

    // 現在スクロールしているか
    bool m_isScrollingBack;
    // 前回のスクロール位置
    int m_beforeScroolHeight;
    // 最後に書き込んだ日付
    wxString m_lastDrawDateLine;
    // 表示設定
    const CServiceConfiguration* m_configuration;

    // フィルター
    const IFilter* m_filter;
//    // フィルターに通るか
//    bool isFilterPassed(const CMessage* message,const vector<IFilter*>& filters );
protected:
    // スクロールしたときのイベント
    void OnScroll(wxScrollWinEvent &event);
    // wxWindowイベントを処理させたいクラスに利用するマクロ
DECLARE_EVENT_TABLE()
    ;

    void pushLog(const CChatMessage* messageLog);
public:
    void pushLog(const CMessage* log);
    CPaneMsg(void);
    ~CPaneMsg(void);
    // 初期化を行う
    void init(wxWindow* parent);
    // 未読背景のリセット
    void clearUnreadBackgroundColor();

    void setFilter(const IFilter* filter)
    {
        m_filter = filter;
    }
    // 表示コンフィグの設定
    void setConfiguration(const CServiceConfiguration* configuration);
private:
    // 必要に応じて日付変更線を描画
    void drawDateLine(const wxString& now);
};

}
