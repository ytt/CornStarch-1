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
void CLogTextCtrl::pushLog(const CServiceLog* log)
{
    this->Freeze();
    if (typeid(*log) == typeid(CMessageLog)){
        pushLog(dynamic_cast<const CMessageLog*>(log));
    } else if (typeid(*log) == typeid(CJoinLog)){
        pushLog(dynamic_cast<const CJoinLog*>(log));
    } else if (typeid(*log) == typeid(CPartLog)){
        pushLog(dynamic_cast<const CPartLog*> (log));
    } else if (typeid(*log) == typeid(CTopicLog)){
        pushLog(dynamic_cast<const CTopicLog*>(log));
    } else if (typeid(*log) == typeid(CMemberLog)){
        pushLog(dynamic_cast<const CMemberLog*>(log));
    } else if (typeid(*log) == typeid(CInviteLog)){
        pushLog(dynamic_cast<const CInviteLog*>(log));
    } else if (typeid(*log) == typeid(CKickLog)){
        pushLog(dynamic_cast<const CKickLog*>( log));
    }
    this->Newline();
    this->Thaw();
}
// メッセージログを表示
void CLogTextCtrl::pushLog(const CMessageLog* messageLog)
{
    // 文字コード変換
    CMessageData message = messageLog->getMessage();
    wxString name = messageLog->getNick();
    wxString body = message.m_body;
    wxString channel = message.m_channel;
    wxString time = message.getTime("%H:%M");

    // temporary_nickがあれば、本文の先頭に表示
    wxString nick = message.m_tempNick;
    if (nick != ""){
        body = "(" + nick + ") " + body;
    }
    writeColoredText(time + " ", COLOR_RED); // 時間を赤で表示
    writeColoredText("(" + name + ") : ", COLOR_BLUE); // 名前を青で表示
    writeColoredText(body, COLOR_BLACK); // 本文を黒で表示

}

// チャンネル参加ログを表示
void CLogTextCtrl::pushLog(const CJoinLog* joinLog)
{
    writeColoredText(
            joinLog->getUserName() + "が" + joinLog->getChannelName() + "に参加しました",
            COLOR_GREEN);

}

// チャンネル離脱ログを表示
void CLogTextCtrl::pushLog(const CPartLog* partLog)
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
void CLogTextCtrl::pushLog(const CMemberLog* memberLog)
{
    //CMemberData member = memberLog.getLog();
    writeColoredText(
            memberLog->getNick() + "がニックネームを" + memberLog->getNickName()
                    + "に変更しました", COLOR_GREEN);
}

// トピック変更ログを表示
void CLogTextCtrl::pushLog(const CTopicLog* topicLog)
{
    //CChannelData channel = topicLog.getLog();
    writeColoredText(
            topicLog->getChannelName() + "のトピックが" + topicLog->getTopic()
                    + "に変更されました", COLOR_GREEN);

}

// 招待ログを表示
void CLogTextCtrl::pushLog(const CInviteLog* inviteLog)
{
    writeColoredText(inviteLog->getNick() + "に招待されました", COLOR_GREEN);

}
// キックログを表示
void CLogTextCtrl::pushLog(const CKickLog* kickLog)
{
    writeColoredText(
            kickLog->getUserName() + "が" + kickLog->getNick() + "からキックされました",
            COLOR_GREEN);
}
} /* namespace CornStarch */
