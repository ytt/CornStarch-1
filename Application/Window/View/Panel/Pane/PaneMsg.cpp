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
void CPaneMsg::pushLog(const CServiceLog* messageLog)
{
    this->MoveEnd();
    CLogTextCtrl::pushLog(messageLog);
    if (m_isScrollingBack == false){
        this->ShowPosition(this->GetLastPosition());
    }
}
void CPaneMsg::pushLog(const CMessageLog* messageLog)
{
    // 文字コード変換
    CMessageData* message = messageLog->getMessage();
    wxString name = messageLog->getNick();
    wxString body = message->m_body;
    wxString channel = message->m_channel;
    wxString time = message->getTime("%H:%M");

    // temporary_nickがあれば、本文の先頭に表示
    wxString nick = message->m_tempNick;
    if (nick != ""){
        body = "(" + nick + ") " + body;
    }
    writeColoredText(time + " ", COLOR_RED); // 時間を赤で表示
    writeColoredText("(" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    if (message->m_isReaded == false){
        this->BeginStyle(wxTextAttr(*wxBLACK, COLOR_LIGHT_YELLOW));
    } else{
        this->BeginStyle(wxTextAttr(*wxBLACK));
    }
    writeLinkableText(body);
    this->EndAllStyles();

}

//void CPaneMsg::addMessage(const CMessageData* message,
//        const map<wxString, wxString>& nickTable)
//{
//    this->Freeze();
//    this->MoveEnd();
//    int index = this->GetLastPosition();
//
//    // 時刻
//    wxString date = message->getTime("%H:%M");
//    writeColoredText(date,*wxRED);
//
//    // 名前
//    int nickIndex = index + date.size();
//    wxString nick = getNickName(message->m_username, nickTable);
//    nick = " (" + nick + "):";
//    if (message->m_tempNick != ""){
//        nick += " (" + message->m_tempNick + ") ";
//    }
//    writeColoredText(nick,*wxBLUE);
//
//    //本文
//    wxString body = message->m_body;
//
//    // 未読の背景色設定
//    if (message->m_isReaded == false){
//        this->BeginStyle(wxTextAttr(*wxBLACK, COLOR_LIGHT_YELLOW));
//    } else{
//        this->BeginStyle(wxTextAttr(*wxBLACK));
//    }
//    writeLinkableText(body);
//    this->EndStyle();
//
//    this->Newline();
//    this->Thaw();
//    if (m_isScrollingBack == false){
//        this->ShowPosition(this->GetLastPosition());
//    }
//    this->EndAllStyles();
//}
// メッセージを表示する
void CPaneMsg::displayMessages(const vector<CServiceLog*>& messages,
        const CNickTable& nickTable)
{
    m_isScrollingBack = false;
    m_beforeScroolHeight = 0;

    this->Freeze();
    this->Clear();
    GetCaret()->Hide();
    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        CServiceLog* log = messages[i];
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
