
#ifndef LOGTEXTCTRL_HPP_
#define LOGTEXTCTRL_HPP_

#include "../../../Service/LogHolder/MessageLog.hpp"
#include "../../../Service/LogHolder/MemberLog.hpp"
#include "../../../Service/LogHolder/JoinLog.hpp"
#include "../../../Service/LogHolder/PartLog.hpp"
#include "../../../Service/LogHolder/TopicLog.hpp"
#include "../../../Service/LogHolder/InviteLog.hpp"
#include "../../../Service/LogHolder/KickLog.hpp"
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
    virtual void pushLog(const CMessageLog* messageLog);

    // チャンネル参加ログを表示
    void pushLog(const CJoinLog* joinLog);

    // チャンネル離脱ログを表示
    void pushLog(const CPartLog* partLog);

    // メンバー情報更新ログを表示
    void pushLog(const CMemberLog* memberLog);

    // トピック変更ログを表示
    void pushLog(const CTopicLog* topicLog);
    // 招待ログを表示
    void pushLog(const CInviteLog* inviteLog);
    // キックログを表示
    void pushLog(const CKickLog* kickLog);


public:
    CLogTextCtrl();
    virtual ~CLogTextCtrl();

    virtual void pushLog(const CServiceLog* log);
    // 単色で文字列を追加する
    void writeColoredText(const wxString& str, const wxColour& colour);

};

} /* namespace CornStarch */
#endif /* LOGTEXTCTRL_HPP_ */
