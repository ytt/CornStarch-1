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
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL );

    setNavigateHaldler();
    // フォントの設定(個人的にこれが好き)
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
    this->SetBackgroundColour(wxColour(200, 200, 200));
}

// ログ一覧を表示
void CPaneRecord::displayLogs(const vector<CChatLog*>& logs)
{
    Clear();
    GetCaret()->Hide();

    size_t size = logs.size();
    for (size_t i = 0; i < size; i++){
        pushLog(*logs[i]);
        switch (logs[i]->getLogType()) {
        case CChatLog::LOG_MESSAGE:
            pushLog(*(CMessageLog*) logs[i]);
            break;
        case CChatLog::LOG_JOIN:
            pushLog(*(CJoinLog*) logs[i]);
            break;
        case CChatLog::LOG_PART:
            pushLog(*(CPartLog*) logs[i]);
            break;
        case CChatLog::LOG_TOPIC:
            pushLog(*(CTopicLog*) logs[i]);
            break;
        case CChatLog::LOG_USER:
            pushLog(*(CMemberLog*) logs[i]);
            break;
        case CChatLog::LOG_INVITE:
            pushLog(*(CInviteLog*) logs[i]);
            break;
        case CChatLog::LOG_KICK:
            pushLog(*(CKickLog*) logs[i]);
            break;
        }
    }
    this->ShowPosition(this->GetLastPosition());
}

//////////////////////////////////////////////////////////////////////
// メッセージログを表示
void CPaneRecord::pushLog(const CChatLog& messageLog)
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
    CMessageData message = messageLog.getLog();
    wxString name = messageLog.getNickName();
    wxString body = message.m_body;
    wxString channel = message.m_channel;
    wxString time = message.getTime("%H:%M");

    // temporary_nickがあれば、本文の先頭に表示
    wxString nick = message.m_tempNick;
    if (nick != ""){
        body = "(" + nick + ") " + body;
    }

    pushStringRow(time + " ", COLOR_RED); // 時間を赤で表示
    pushStringRow("<" + channel + "> (" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    pushStringRow(body, COLOR_BLACK); // 本文を黒で表示
    this->Newline();
}

// チャンネル参加ログを表示
void CPaneRecord::pushLog(const CJoinLog& joinLog)
{
    pushStringRow(
            joinLog.getNickName() + "が" + joinLog.getLog().m_channel
                    + "に参加しました", COLOR_GREEN);
    this->Newline();

}

// チャンネル離脱ログを表示
void CPaneRecord::pushLog(const CPartLog& partLog)
{
    if (partLog.getLog().m_channel != ""){
        pushStringRow(
                partLog.getNickName() + "が" + partLog.getLog().m_channel
                        + "から離脱しました", COLOR_GREEN);
    } else{
        pushStringRow(partLog.getNickName() + "が離脱しました", COLOR_GREEN);
    }
    this->Newline();
}

// メンバー情報更新ログを表示
void CPaneRecord::pushLog(const CMemberLog& memberLog)
{
    CMemberData member = memberLog.getLog();
    pushStringRow(member.m_name + "がニックネームを" + member.m_nick + "に変更しました",
            COLOR_GREEN);
    this->Newline();
}

// トピック変更ログを表示
void CPaneRecord::pushLog(const CTopicLog& topicLog)
{
    CChannelData channel = topicLog.getLog();
    pushStringRow(channel.m_name + "のトピックが" + channel.m_topic + "に変更されました",
            COLOR_GREEN);

    this->Newline();
}

// 招待ログを表示
void CPaneRecord::pushLog(const CInviteLog& inviteLog)
{
    pushStringRow(inviteLog.getChannel() + "に招待されました", COLOR_GREEN);

    this->Newline();
}
// キックログを表示
void CPaneRecord::pushLog(const CKickLog& kickLog)
{
    pushStringRow(
            kickLog.getUsername() + "が" + kickLog.getChannel() + "からキックされました",
            COLOR_GREEN);
    this->Newline();
}
}
