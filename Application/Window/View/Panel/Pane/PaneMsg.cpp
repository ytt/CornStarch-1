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
            wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxTE_RICH2/*|wxTE_DONTWRAP*/);

    // フォント設定
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));

    // リンククリック時
    this->Connect(CPaneMsg::PANE_MSG_ID, wxEVT_COMMAND_TEXT_URL,
            wxTextUrlEventHandler(CPaneMsg::onNavigate));
}
void CPaneMsg::onNavigate(wxTextUrlEvent& event)
{
    wxString url = event.GetString();
    wxString command = "open " + url;
    system(command.c_str());
}
bool CPaneMsg::containsOver4ByteText(const wxString& content) const
{
    string body = string(content.c_str());
    int checkIndex = 0;
    while (checkIndex < body.size()){
        int length = mblen(&(body[checkIndex]), MB_CUR_MAX);
        if (length >= 4){
            return true;
        }
        checkIndex += length;
    }
    return false;
}
void CPaneMsg::clearUnreadBackgroundColor()
{
    int index = this->GetLastPosition();
    this->SetStyle(0, index, wxTextAttr(wxNullColour, *wxWHITE));
}
void CPaneMsg::addContent(const wxString& content)
{
    int urlIndex = content.find("http", 0);
    if (urlIndex != wxString::npos){
        // リンクが始まるまでの文字を表示
        if (urlIndex != 0){
            WriteText(content.substr(0, urlIndex));
        }
        int endIndex = 0;
        while (urlIndex != wxString::npos){
            endIndex = content.find(" ", urlIndex);

            wxString url;
            if (endIndex != wxString::npos){
                url = content.substr(urlIndex, endIndex-urlIndex);
            } else{
                url = content.substr(urlIndex);
            }
            this->BeginUnderline();
            this->BeginURL(url);
            WriteText(url);
            this->EndURL();
            this->EndUnderline();

            if (endIndex != wxString::npos){
                urlIndex = content.find("http", endIndex);
                // 次のリンクまでの文字を表示
                if(urlIndex != wxString::npos)
                {
                    WriteText(content.substr(endIndex,urlIndex-endIndex));
                }
            } else{
                // 継続文字がなければ終了。
                return;
            }
        }
        // 残りの文字を表示
        WriteText(content.substr(endIndex));
    } else{

        WriteText(content);
    }
}
void CPaneMsg::addMessage(const CMessageData* message,
        const map<wxString, wxString>& nickTable)
{
    int index = this->GetLastPosition();

    // 時刻
    wxString date = message->getTime("%H:%M");
    this->WriteText(date);
    this->SetStyle(index, index + date.length(), wxTextAttr(*wxRED));

    // 名前
    int nickIndex = index + date.size();
    wxString nick = getNickName(message->m_username, nickTable);
    nick = " (" + nick + "):";
    if (message->m_tempNick != ""){
        nick += " (" + message->m_tempNick + ") ";
    }
    this->WriteText(nick);
    this->SetStyle(nickIndex, nickIndex + nick.size(), wxTextAttr(*wxBLUE));

    //本文
    int bodyIndex = nickIndex += nick.size();
    wxString body = message->m_body;

    // 4byte文字を非表示にする。
    if (containsOver4ByteText(body) == false){
        addContent(body);
        this->SetStyle(bodyIndex, bodyIndex + body.Length(),
                wxTextAttr(*wxBLACK));

        // 未読の背景色設定
        if (message->m_isReaded == false){
            this->SetStyle(index, bodyIndex + body.Length(),
                    wxTextAttr(wxNullColour, COLOR_LIGHT_YELLOW));
        }
    }
    this->Newline();
    this->ShowPosition(this->GetLastPosition());
}
// メッセージを表示する
void CPaneMsg::displayMessages(const vector<CMessageData*>& messages,
        const map<wxString, wxString>& nickTable)
{
    this->Freeze();
    this->Clear();
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
