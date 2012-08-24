#include "PaneMsg.hpp"
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wx/event.h>
using namespace std;

namespace CornStarch
{
;

const int CPaneMsg::PANE_MSG_ID = 10000;
// イベントテーブル
BEGIN_EVENT_TABLE(CPaneMsg, CLinkableRichTextCtrl) //
EVT_SCROLLWIN( CPaneMsg::OnScroll)
END_EVENT_TABLE()
;

const wxColour CPaneMsg::COLOR_LIGHT_YELLOW = wxColour(255, 255, 180);
CPaneMsg::CPaneMsg(void) :
        m_beforeScroolHeight(0), m_isScrollingBack(false)
{
}

CPaneMsg::~CPaneMsg(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPaneMsg::init(wxWindow* parent)
{
    // 画面の初期化
    Create(parent, CPaneMsg::PANE_MSG_ID, wxEmptyString, wxDefaultPosition,
            wxDefaultSize,
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL /*|wxTE_DONTWRAP*/);

    // フォント設定
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));

    this->setNavigateHaldler();

}
void CPaneMsg::OnScroll(wxScrollWinEvent &event)
{
    if (event.GetPosition() != 0){
        m_isScrollingBack = true;
        // 一番下まですくロールしていれば、スクロール中を終了。
        if (m_beforeScroolHeight <= event.GetPosition()){
            m_beforeScroolHeight = event.GetPosition() - 1;
            m_isScrollingBack = false;
        } else{
        }
    }
    event.Skip(true);
}

void CPaneMsg::clearUnreadBackgroundColor()
{
    int index = this->GetLastPosition();
    this->SetStyle(0, index, wxTextAttr(wxNullColour, *wxWHITE));
}
void CPaneMsg::pushLog(const CMessage* messageLog)
{
    this->MoveEnd();
    CLogTextCtrl::pushLog(messageLog);
    if (m_isScrollingBack == false){
        this->ShowPosition(this->GetLastPosition());
    }
}
void CPaneMsg::pushLog(const CChatMessage* messageLog)
{
    wxString name = messageLog->getNick();
    wxString body = messageLog->getBody();
    wxString channel = messageLog->getChannelName();
    wxString time = messageLog->getTime("%H:%M");

    writeColoredText(time + " ", COLOR_GRAY); // 時間を灰で表示
    wxString nick = messageLog->getTempNick();
    if (nick != ""){
        writeColoredText("(" + nick + ") : ", COLOR_RED); // テンポラリー名を赤で表示
    } else{
        writeColoredText("(" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    }
    if (messageLog->isReaded() == false){
        this->BeginStyle(wxTextAttr(*wxBLACK, COLOR_LIGHT_YELLOW));
    } else{
        this->BeginStyle(wxTextAttr(*wxBLACK));
    }
    writeLinkableText(body);
    this->EndAllStyles();

}

// メッセージを表示する
void CPaneMsg::displayMessages(const vector<CMessage*>& messages,
        const CNickTable& nickTable)
{
    m_isScrollingBack = false;
    m_beforeScroolHeight = 0;

    this->Freeze();
    this->Clear();
    GetCaret()->Hide();
    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        CMessage* log = messages[i];
        wxString nickName = nickTable.getNickname(log->getUserName());
        log->setNick(nickName);
        pushLog(log);
        if (i < size - 1){
            drawDateLine(messages[i]->getTime("%Y/%m/%d(%a)"),
                    messages[i + 1]->getTime("%Y/%m/%d(%a)"));
        }
    }
    this->Thaw();
    this->ShowPosition(this->GetLastPosition());
}

// 必要に応じて日付変更線を描画
void CPaneMsg::drawDateLine(const wxString& now, const wxString& next)
{
    if (now == next){
        return;
    }

    this->Newline();
    AppendText("------" + next + "--------");
    this->Newline();
    this->Newline();
}

}
