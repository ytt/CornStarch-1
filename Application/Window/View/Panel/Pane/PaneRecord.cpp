#include "PaneRecord.hpp"

using namespace std;

namespace CornStarch
{
;

const wxColour CPaneRecord::COLOR_BLACK = wxColour(0, 0, 0);
const wxColour CPaneRecord::COLOR_BLUE = wxColour(0, 0, 200);
const wxColour CPaneRecord::COLOR_GREEN = wxColour(0, 50, 0);
const wxColour CPaneRecord::COLOR_RED = wxColour(255, 0, 0);

CPaneRecord::CPaneRecord(void)
{
}

CPaneRecord::~CPaneRecord(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPaneRecord::init(wxWindow* parent)
{
    // テキスト領域の作成
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL);

    setNavigateHaldler();
    // フォントの設定(個人的にこれが好き)
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
    this->SetBackgroundColour(wxColour(200, 200, 200));
}

// ログ一覧を表示
void CPaneRecord::displayLogs(const vector<CServiceLog*>& logs)
{
    Clear();
    GetCaret()->Hide();

    size_t size = logs.size();
    for (size_t i = 0; i < size; i++){
        pushLog(*logs[i]);
        if (typeid(*logs[i]) == typeid(CMessageLog)){
            pushLog(*(CMessageLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CJoinLog)){
            pushLog(*(CJoinLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CPartLog)){
            pushLog(*(CPartLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CTopicLog)){
            pushLog(*(CTopicLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CMemberLog)){
            pushLog(*(CMemberLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CInviteLog)){
            pushLog(*(CInviteLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CKickLog)){
            pushLog(*(CKickLog*) logs[i]);
        }
        this->Newline();
    }
    this->ShowPosition(this->GetLastPosition());
}

//////////////////////////////////////////////////////////////////////
// メッセージログを表示
void CPaneRecord::pushLog(const CServiceLog& messageLog)
{
    wxString content = wxString::Format(wxT("(%s)"),
            messageLog.getServiceName());
    pushStringRow(content, COLOR_BLACK); // 本文を黒で表示

}
// 単色で文字列を追加する
void CPaneRecord::pushStringRow(const wxString& str, const wxColour& colour)
{
    // 文字列の挿入
    BeginStyle(wxTextAttr(colour));
    writeLinkableText(str);
    this->EndAllStyles();
}

// メッセージログを表示
void CPaneRecord::pushLog(const CMessageLog& messageLog)
{
    // 文字コード変換
    CMessageData message = messageLog.getMessage();
    wxString name = messageLog.getUserName();
    wxString body = message.m_body;
    wxString channel = message.m_channel;
    wxString time = message.getTime("%H:%M");

    // temporary_nickがあれば、本文の先頭に表示
    wxString nick = message.m_tempNick;
    if (nick != ""){
        body = "(" + nick + ") " + body;
    }
    pushStringRow("<" + channel + ">", COLOR_BLACK);
    pushStringRow(time + " ", COLOR_RED); // 時間を赤で表示
    pushStringRow( "(" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    pushStringRow(body, COLOR_BLACK); // 本文を黒で表示

}

// チャンネル参加ログを表示
void CPaneRecord::pushLog(const CJoinLog& joinLog)
{
    pushStringRow(
            joinLog.getUserName() + "が" + joinLog.getChannelName()
                    + "に参加しました", COLOR_GREEN);

}

// チャンネル離脱ログを表示
void CPaneRecord::pushLog(const CPartLog& partLog)
{
    if (partLog.getChannelName() != ""){
        pushStringRow(
                partLog.getUserName() + "が" + partLog.getChannelName()
                        + "から離脱しました", COLOR_GREEN);
    } else{
        pushStringRow(partLog.getUserName() + "が離脱しました", COLOR_GREEN);
    }
}

// メンバー情報更新ログを表示
void CPaneRecord::pushLog(const CMemberLog& memberLog)
{
    //CMemberData member = memberLog.getLog();
    pushStringRow(memberLog.getUserName() + "がニックネームを" + memberLog.getNickName() + "に変更しました",
            COLOR_GREEN);
}

// トピック変更ログを表示
void CPaneRecord::pushLog(const CTopicLog& topicLog)
{
    //CChannelData channel = topicLog.getLog();
    pushStringRow(topicLog.getChannelName()+ "のトピックが" + topicLog.getTopic()+ "に変更されました",
            COLOR_GREEN);

}

// 招待ログを表示
void CPaneRecord::pushLog(const CInviteLog& inviteLog)
{
    pushStringRow(inviteLog.getChannelName() + "に招待されました", COLOR_GREEN);

}
// キックログを表示
void CPaneRecord::pushLog(const CKickLog& kickLog)
{
    pushStringRow(
            kickLog.getUserName() + "が" + kickLog.getChannelName() + "からキックされました",
            COLOR_GREEN);
}
}
