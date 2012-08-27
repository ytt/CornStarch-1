#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "LinkableRichTextCtrl.hpp"

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_KEYDDOWN_ON_POSTPANE, wxKeyEvent);
// メッセージ投稿用ペイン
class CPanePost : public wxTextCtrl
{
    // wxWindowイベントを処理させたいクラスに利用するマクロ
    DECLARE_EVENT_TABLE();
public:
    CPanePost(void);
    ~CPanePost(void);

    // 初期化を行う
    void init(wxWindow* parent);
    void onKeyDown(wxKeyEvent& event);
};

}
