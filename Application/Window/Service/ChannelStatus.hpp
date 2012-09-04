#pragma once
#include "MemberVec.hpp"
#include "Message/MessageHolder.hpp"
#include "Message/ChatMessage.hpp"
#include "Filter/IFilter.hpp"
using namespace std;
namespace CornStarch
{
;
// チャンネルの内部状態(誰がいるかやメッセージなど)を管理
class CChannelStatus
{
private:
    wxString m_topic; // トピック
    CMemberVec* m_members; // メンバー一覧
    wxString m_channelName; // チャンネル名
    int m_unreadCount; // 未読数
    CMessageHolder* m_logHolder;
    bool m_isLoaded;


public:
    CChannelStatus(void);
    ~CChannelStatus(void);

    // 初期化を行う
    void init(void);

    // トピックをセットする
    void setTopic(const wxString& topic);

    // トピックを取得する
    wxString getTopic(void) const;

    // メッセージ一覧を取得する
    std::vector<CMessage*> getLog(void) const;

    // メンバー一覧を取得する
    std::vector<CMemberData*> getMembers(void) const;

    // メッセージを追加する
    void pushLog( CMessage* log);

    // メンバーを追加する
    void pushMember(const CMemberData& member);

    // メッセージ一覧をセットする
    void setMessages(const std::vector<CMessage*>& logs);

    // メンバー一覧をセットする
    void setMembers(const std::vector<CMemberData*>& members);

    // メッセージを取得し終えたか
    bool hasReceivedMessage(void) const;

    // メンバを取得し終えたか
    bool hasReceivedMember(void) const;

    // ID不明かつ同じ投稿内容のメッセージがあるか
    bool hasSameMessage(const CChatMessage* message) const;

    // 同じ内容のメッセージについてIDを更新
    void updateMessageId(const CChatMessage* message);

    // メンバー情報を更新する
    void updateMember(const wxString& userName,const wxString& nick);

    // メンバー情報を消す
    void popMember(const wxString& userName);

    // 未読をクリア
    void clearUnreadCount();

    // チャンネル名の取得
    wxString getChannelName() const
    {
        return m_channelName;
    }

    // チャンネル名の設定
    void setChannelName(wxString channelName)
    {
        m_channelName = channelName;
    }
    // 未読数の取得
    int getUnreadCount() const
    {
        return m_unreadCount;
    }

    // 未読数の追加
    void addUnreadCount()
    {
        m_unreadCount++;
    }

};

}
