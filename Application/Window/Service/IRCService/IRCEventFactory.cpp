#include "IRCEventFactory.hpp"

#include "../Event/AuthEvent.hpp"
#include "../Event/DisconnectEvent.hpp"
#include "../Event/GetMemberEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/ConnectionEventBase.hpp"
#include "../Event/StreamEvent.hpp"

#include "IRCCommand.hpp"
#include <vector>
#include "../StringUtility.hpp"

namespace CornStarch
{
;
namespace IRC
{
;

CConnectionEventBase* CIRCEventFactory::Create(const CIRCResponseData& message)
{
    if (message.m_statusCode == IRCCommand::PRIVMSG){
        return createPrivateMessageEvent(message);
    }
    if (message.m_statusCode == IRCCommand::PART){
        return createPartMessageEvent(message);
    }
    if (message.m_statusCode == IRCCommand::JOIN){
        return createJoinMessageEvent(message);
    }
    if (message.m_statusCode == IRCCommand::TOPIC){
        return createTopicMessageEvent(message);
    }
    if (message.m_statusCode == IRCCommand::QUIT){
        // すべてのチャンネルへのPartEventの作成

        CStreamEvent<CPartMessage>* event = new CStreamEvent<CPartMessage>(myEVT_THREAD_STREAM_CH_PART);
        CPartMessage* log = new CPartMessage();
        log->setServiceId(m_connectionId);
        log->setChannelName("");
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_statusCode == IRCCommand::NICK){
        return createNickMessageEvent(message);
    }
    if (message.m_statusCode == IRCCommand::KICK){
        return createKickEvent(message);
    }
    if (message.m_statusCode == IRCCommand::INVITE){
        return createInviteEvent(message);
    }
    if (message.m_statusCode == IRCCommand::NAMES_REPLY){
        addNames(message);
    }
    if (message.m_statusCode == IRCCommand::TOPIC_REPLY){
        return createTopicEvent(message);
    }
    if (message.m_statusCode == IRCCommand::NAMES_REPLY_END){ //ユーザー名羅列終了リプライ
        return createNamesEvent(message);
    }
    if (message.m_statusCode == IRCCommand::INVALID_USERNAME
            || message.m_statusCode == IRCCommand::INVALID_CHANNEL){ //　不適切
            //エラー
        CAuthEvent* event = new CAuthEvent();
        event->setAuthResult(false);
        return event;
    }
    return NULL;

}

CConnectionEventBase* CIRCEventFactory::createNickMessageEvent(
        const CIRCResponseData& message) const
{
    // Eventの作成
    CStreamEvent<CMemberMessage>* event = new CStreamEvent<CMemberMessage>(myEVT_THREAD_STREAM_USER_UPDATE);
    CMemberMessage* log = new CMemberMessage();
    log->setServiceId(m_connectionId);
    log->setUserName(message.m_username);
    log->setNickName(message.m_body);
    event->setServiceLog(log);
    return event;
}
CConnectionEventBase* CIRCEventFactory::createTopicMessageEvent(
        const CIRCResponseData& message) const
{
    // Eventの作成
    CStreamEvent<CTopicMessage>* event = new CStreamEvent<CTopicMessage>(myEVT_THREAD_STREAM_CH_UPDATE);
    CTopicMessage* log = new CTopicMessage();
    log->setServiceId(m_connectionId);
    log->setTopic(message.m_body);
    log->setChannelName(message.m_channel);
    log->setUserName(message.m_username);
    event->setServiceLog(log);
    return event;
}
CConnectionEventBase* CIRCEventFactory::createJoinMessageEvent(
        const CIRCResponseData& message) const
{
    // Eventの作成
    CStreamEvent<CJoinMessage>* event = new CStreamEvent<CJoinMessage>(myEVT_THREAD_STREAM_CH_JOIN);
    CJoinMessage* log = new CJoinMessage();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_body);
    log->setUserName(message.m_username);
    event->setServiceLog(log);

    return event;
}
CConnectionEventBase* CIRCEventFactory::createPartMessageEvent(
        const CIRCResponseData& message) const
{
    // Eventの作成
    CStreamEvent<CPartMessage>* event = new CStreamEvent<CPartMessage>(myEVT_THREAD_STREAM_CH_PART);
    CPartMessage* log = new CPartMessage();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_channel);
    log->setUserName(message.m_username);
    event->setServiceLog(log);

    return event;

}
CConnectionEventBase* CIRCEventFactory::createPrivateMessageEvent(
        const CIRCResponseData& message) const
{
    // Eventの作成
    CStreamEvent<CChatMessage>* event = new CStreamEvent<CChatMessage>(myEVT_THREAD_STREAM_MSG_ADD);

    CChatMessage* log = new CChatMessage();
    log->init(&message);
    log->setServiceId(m_connectionId);
    event->setServiceLog(log);

    return event;
}

void CIRCEventFactory::addNames(const CIRCResponseData& message)
{
    int index = message.m_param.find(":");
    wxString names = message.m_param.substr(index + 1);
    m_namesBuffer += names;
}
CConnectionEventBase* CIRCEventFactory::createNamesEvent(
        const CIRCResponseData& message)
{
    vector<CMemberData*> result;
    vector<wxString> names = CStringUtility::split(m_namesBuffer, " ");

    // 各メンバについてループ
    int size = (int) names.size();
    for (int i = 0; i < size; i++){
        if (names[i].size() != 0 && names[i] != "\r"){
            // パラメータの取得
            CMemberData* mem = new CMemberData();
            wxString name =names[i];
            wxString nickName =name;
            if(name.find("@") ==0)
            {
                name = name.substr(1);
            }
            mem->m_name = name; // 名前
            mem->m_nick = nickName; // ニックネーム
            result.push_back(mem);
        }
    }

    CGetMemberEvent* event = new CGetMemberEvent();
    event->setMembers(result);
    event->setChannel(message.m_target);
    m_namesBuffer = "";
    return event;
}

CConnectionEventBase* CIRCEventFactory::createTopicEvent(
        const CIRCResponseData& message) const
{
    return NULL;
}

CConnectionEventBase* CIRCEventFactory::createKickEvent(
        const CIRCResponseData& message) const
{
    CStreamEvent<CKickMessage>* event = new CStreamEvent<CKickMessage>(myEVT_THREAD_KICK);
    CKickMessage* log = new CKickMessage();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_channel);
    log->setUserName(message.m_username);
    log->setTarget(message.m_target);
    event->setServiceLog(log);
    return event;
}

CConnectionEventBase* CIRCEventFactory::createInviteEvent(
        const CIRCResponseData& message) const
{
    CStreamEvent<CInviteMessage>* event = new CStreamEvent<CInviteMessage>(myEVT_THREAD_INVITE);
    CInviteMessage* log = new CInviteMessage();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_body);
    log->setUserName(message.m_username);
    event->setServiceLog(log);
    return event;
}
}
}

