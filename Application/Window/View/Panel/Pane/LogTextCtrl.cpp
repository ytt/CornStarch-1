#include "LogTextCtrl.hpp"

namespace CornStarch
{

const wxColour CLogTextCtrl::COLOR_BLACK = wxColour(0, 0, 0);
const wxColour CLogTextCtrl::COLOR_BLUE = wxColour(0, 0, 200);
const wxColour CLogTextCtrl::COLOR_GREEN = wxColour(0, 50, 0);
const wxColour CLogTextCtrl::COLOR_RED = wxColour(255, 0, 0);

CLogTextCtrl::CLogTextCtrl()
{
}

CLogTextCtrl::~CLogTextCtrl()
{
}

// 単色で文字列を追加する
void CLogTextCtrl::writeColoredText(const wxString& str, const wxColour& colour)
{
    // 文字列の挿入
    BeginStyle(wxTextAttr(colour));
    writeLinkableText(str);
    this->EndAllStyles();
}
void CLogTextCtrl::pushLog(const CMessage* log)
{
    this->Freeze();
    if (typeid(*log) == typeid(CChatMessage)){
        pushLog(dynamic_cast<const CChatMessage*>(log));
    } else if (typeid(*log) == typeid(CJoinMessage)){
        pushLog(dynamic_cast<const CJoinMessage*>(log));
    } else if (typeid(*log) == typeid(CPartMessage)){
        pushLog(dynamic_cast<const CPartMessage*> (log));
    } else if (typeid(*log) == typeid(CTopicMessage)){
        pushLog(dynamic_cast<const CTopicMessage*>(log));
    } else if (typeid(*log) == typeid(CMemberMessage)){
        pushLog(dynamic_cast<const CMemberMessage*>(log));
    } else if (typeid(*log) == typeid(CInviteMessage)){
        pushLog(dynamic_cast<const CInviteMessage*>(log));
    } else if (typeid(*log) == typeid(CKickMessage)){
        pushLog(dynamic_cast<const CKickMessage*>( log));
    }
    this->Newline();
    this->Thaw();
}
// メッセージログを表示
void CLogTextCtrl::pushLog(const CChatMessage* messageLog)
{
    // 文字コード変換
    wxString name = messageLog->getNick();
    wxString body = messageLog->getBody();
    wxString channel = messageLog->getChannelName();
    wxString time = messageLog->getTime("%H:%M");

    // temporary_nickがあれば、本文の先頭に表示
    wxString nick = messageLog->getTempNick();
    if (nick != ""){
        body = "(" + nick + ") " + body;
    }
    writeColoredText(time + " ", COLOR_RED); // 時間を赤で表示
    writeColoredText("(" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    writeColoredText(body, COLOR_BLACK); // 本文を黒で表示
}

// チャンネル参加ログを表示
void CLogTextCtrl::pushLog(const CJoinMessage* joinLog)
{
    writeColoredText(
            joinLog->getUserName() + "が" + joinLog->getChannelName() + "に参加しました",
            COLOR_GREEN);

}

// チャンネル離脱ログを表示
void CLogTextCtrl::pushLog(const CPartMessage* partLog)
{
    if (partLog->getChannelName() != ""){
        writeColoredText(
                partLog->getUserName() + "が" + partLog->getChannelName()
                        + "から離脱しました", COLOR_GREEN);
    } else{
        writeColoredText(partLog->getNick() + "が離脱しました", COLOR_GREEN);
    }
}

// メンバー情報更新ログを表示
void CLogTextCtrl::pushLog(const CMemberMessage* memberLog)
{
    //CMemberData member = memberLog.getLog();
    writeColoredText(
            memberLog->getNick() + "がニックネームを" + memberLog->getNickName()
                    + "に変更しました", COLOR_GREEN);
}

// トピック変更ログを表示
void CLogTextCtrl::pushLog(const CTopicMessage* topicLog)
{
    //CChannelData channel = topicLog.getLog();
    writeColoredText(
            topicLog->getChannelName() + "のトピックが" + topicLog->getTopic()
                    + "に変更されました", COLOR_GREEN);

}

// 招待ログを表示
void CLogTextCtrl::pushLog(const CInviteMessage* inviteLog)
{
    writeColoredText(inviteLog->getNick() + "に招待されました", COLOR_GREEN);

}
// キックログを表示
void CLogTextCtrl::pushLog(const CKickMessage* kickLog)
{
    writeColoredText(
            kickLog->getUserName() + "が" + kickLog->getNick() + "からキックされました",
            COLOR_GREEN);
}
} /* namespace CornStarch */
