#include "PaneMsg.hpp"
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;

namespace CornStarch
{
;
const int CPaneMsg::PANE_MSG_ID = 10000;
const wxColour CPaneMsg::COLOR_LIGHT_YELLOW = wxColour(255, 255, 180);
CPaneMsg::CPaneMsg(void)
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

void CPaneMsg::clearUnreadBackgroundColor()
{
    int index = this->GetLastPosition();
    this->SetStyle(0, index, wxTextAttr(wxNullColour, *wxWHITE));
}
void CPaneMsg::addMessage(const CMessageData* message,
        const map<wxString, wxString>& nickTable)
{
    int index = this->GetLastPosition();

    // 時刻
    wxString date = message->getTime("%H:%M");

    this->BeginStyle(wxTextAttr(*wxRED));
    this->WriteText(date);

    // 名前
    int nickIndex = index + date.size();
    wxString nick = getNickName(message->m_username, nickTable);
    nick = " (" + nick + "):";
    if (message->m_tempNick != ""){
        nick += " (" + message->m_tempNick + ") ";
    }
    this->BeginStyle(wxTextAttr(*wxBLUE));
    this->WriteText(nick);

    //本文
    int bodyIndex = nickIndex += nick.size();
    wxString body = message->m_body;

    // 未読の背景色設定
    if (message->m_isReaded == false){
        this->BeginStyle(wxTextAttr(*wxBLACK, COLOR_LIGHT_YELLOW));
    }
    else
    {
        this->BeginStyle(wxTextAttr(*wxBLACK));
    }
    writeLinkableText(body);
    this->EndStyle();

    this->Newline();
    this->ShowPosition(this->GetLastPosition());
    this->EndAllStyles();
}
// メッセージを表示する
void CPaneMsg::displayMessages(const vector<CMessageData*>& messages,
        const map<wxString, wxString>& nickTable)
{

    this->Freeze();
    this->Clear();
    GetCaret()->Hide();
    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        addMessage(messages[i], nickTable);
        if (i < size - 1){
            drawDateLine(messages[i]->getTime("%Y/%m/%d(%a)"),
                    messages[i + 1]->getTime("%Y/%m/%d(%a)"));
        }
    }
    this->Thaw();
    this->ShowPosition(this->GetLastPosition());
}

//////////////////////////////////////////////////////////////////////

// ユーザ名に対応するニックネームを取得する
wxString CPaneMsg::getNickName(const wxString& userName,
        const map<wxString, wxString>& nickTable)
{
    // テーブルに存在しない時、本名を返す
    if (nickTable.find(userName) == nickTable.end()){
        return userName;
    }

    // ニックネームを返す
    return nickTable.find(userName)->second;
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
