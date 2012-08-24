#ifndef IRCEVENTFACTORY_HPP_
#define IRCEVENTFACTORY_HPP_

#include "IRCResponseData.hpp"
#include "../Event/ConnectionEventBase.hpp"
namespace CornStarch
{
;
namespace IRC
{
;
class CIRCEventFactory
{
    int m_connectionId;
    // 名前一覧のバッファ
    wxString m_namesBuffer;
    // 名前一覧の名前をバッファに追加します。
    void addNames(const CIRCResponseData& param);
    // ニックネームイベントを生成します。
    CConnectionEventBase* createNickMessageEvent(
            const CIRCResponseData& message) const;
    // トピックイベントを生成します。
    CConnectionEventBase* createTopicMessageEvent(
            const CIRCResponseData& message) const;
    // 参加イベントを生成します。
    CConnectionEventBase* createJoinMessageEvent(
            const CIRCResponseData& message) const;
    // 離脱イベントを作成します。
    CConnectionEventBase* createPartMessageEvent(
            const CIRCResponseData& message) const;
    // メッセージのイベントを作成します。
    CConnectionEventBase* createPrivateMessageEvent(
            const CIRCResponseData& message) const;
    //　名前一覧取得のイベントを作成します。
    CConnectionEventBase* createNamesEvent(const CIRCResponseData& message);
    // 招待イベントを作成します。
    CConnectionEventBase* createInviteEvent(
            const CIRCResponseData& message) const;
    // キックイベントを作成します。
    CConnectionEventBase* createKickEvent(const CIRCResponseData& message) const;
    // トピック取得のイベントを作成します。
    CConnectionEventBase* createTopicEvent(
            const CIRCResponseData& message) const;
public:
    CIRCEventFactory():m_namesBuffer("")
    {
    }
    virtual ~CIRCEventFactory()
    {
    }
    CConnectionEventBase* Create(const CIRCResponseData& message);

    int getConnectionId() const
    {
        return m_connectionId;
    }

    void setConnectionId(int connectionId)
    {
        m_connectionId = connectionId;
    }
};
}
}
#endif /* IRCEVENTFACTORY_HPP_ */
