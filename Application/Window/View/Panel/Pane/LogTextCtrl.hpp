
#ifndef LOGTEXTCTRL_HPP_
#define LOGTEXTCTRL_HPP_

#include "../../../Service/Message/ChatMessage.hpp"
#include "../../../Service/Message/MemberMessage.hpp"
#include "../../../Service/Message/JoinMessage.hpp"
#include "../../../Service/Message/PartMessage.hpp"
#include "../../../Service/Message/TopicMessage.hpp"
#include "../../../Service/Message/InviteMessage.hpp"
#include "../../../Service/Message/KickMessage.hpp"
#include "LinkableRichTextCtrl.hpp"

namespace CornStarch
{

class CLogTextCtrl: public CLinkableRichTextCtrl
{
protected:
    static const wxColour COLOR_BLACK;
    static const wxColour COLOR_GREEN;
    static const wxColour COLOR_RED;
    static const wxColour COLOR_BLUE;
    // メッセージログを表示
    virtual void pushLog(const CChatMessage* messageLog);

    // チャンネル参加ログを表示
    void pushLog(const CJoinMessage* joinLog);

    // チャンネル離脱ログを表示
    void pushLog(const CPartMessage* partLog);

    // メンバー情報更新ログを表示
    void pushLog(const CMemberMessage* memberLog);

    // トピック変更ログを表示
    void pushLog(const CTopicMessage* topicLog);
    // 招待ログを表示
    void pushLog(const CInviteMessage* inviteLog);
    // キックログを表示
    void pushLog(const CKickMessage* kickLog);


public:
    CLogTextCtrl();
    virtual ~CLogTextCtrl();

    virtual void pushLog(const CMessage* log);
    // 単色で文字列を追加する
    void writeColoredText(const wxString& str, const wxColour& colour);

};

} /* namespace CornStarch */
#endif /* LOGTEXTCTRL_HPP_ */
