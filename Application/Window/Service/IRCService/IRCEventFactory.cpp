#include "IRCEventFactory.hpp"

#include "../Event/AuthEvent.hpp"
#include "../Event/DisconnectEvent.hpp"
#include "../Event/GetMemberEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/ConnectionEventBase.hpp"
#include "../LogHolder/MessageLog.hpp"
#include "../LogHolder/MemberLog.hpp"
#include "../LogHolder/JoinLog.hpp"
#include "../LogHolder/PartLog.hpp"
#include "../LogHolder/TopicLog.hpp"
#include "../LogHolder/InviteLog.hpp"
#include "../LogHolder/KickLog.hpp"
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

CConnectionEventBase* CIRCEventFactory::Create(const CIRCMessageData& message)
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

        CStreamEvent<CPartLog>* event = new CStreamEvent<CPartLog>(myEVT_THREAD_STREAM_CH_PART);
        CPartLog* log = new CPartLog();
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
        const CIRCMessageData& message) const
{
    // Eventの作成

    CStreamEvent<CMemberLog>* event = new CStreamEvent<CMemberLog>(myEVT_THREAD_STREAM_USER_UPDATE);
    CMemberLog* log = new CMemberLog();
    log->setServiceId(m_connectionId);
    log->setUserName(message.m_username);
    log->setNickName(message.m_body);
    event->setServiceLog(log);
    //event->setMember(member);
    return event;
}
CConnectionEventBase* CIRCEventFactory::createTopicMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CStreamEvent<CTopicLog>* event = new CStreamEvent<CTopicLog>(myEVT_THREAD_STREAM_CH_UPDATE);
    CTopicLog* log = new CTopicLog();
    log->setServiceId(m_connectionId);
    log->setTopic(message.m_body);
    log->setChannelName(message.m_channel);
    log->setUserName(message.m_username);
    event->setServiceLog(log);
    return event;
}
CConnectionEventBase* CIRCEventFactory::createJoinMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CStreamEvent<CJoinLog>* event = new CStreamEvent<CJoinLog>(myEVT_THREAD_STREAM_CH_JOIN);
    CJoinLog* log = new CJoinLog();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_body);
    log->setUserName(message.m_username);
    event->setServiceLog(log);

    return event;
}
CConnectionEventBase* CIRCEventFactory::createPartMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CStreamEvent<CPartLog>* event = new CStreamEvent<CPartLog>(myEVT_THREAD_STREAM_CH_PART);
    CPartLog* log = new CPartLog();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_channel);
    log->setUserName(message.m_username);
    event->setServiceLog(log);

    return event;

}
CConnectionEventBase* CIRCEventFactory::createPrivateMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CStreamEvent<CMessageLog>* event = new CStreamEvent<CMessageLog>(myEVT_THREAD_STREAM_MSG_ADD);

    CMessageLog* log = new CMessageLog();
    log->init(&message);
    log->setServiceId(m_connectionId);
    event->setServiceLog(log);

    return event;
}

void CIRCEventFactory::addNames(const CIRCMessageData& message)
{
    int index = message.m_param.find(":");
    wxString names = message.m_param.substr(index + 1);
    m_namesBuffer += names;
}
CConnectionEventBase* CIRCEventFactory::createNamesEvent(
        const CIRCMessageData& message)
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
        const CIRCMessageData& message) const
{
    return NULL;
}

CConnectionEventBase* CIRCEventFactory::createKickEvent(
        const CIRCMessageData& message) const
{
    CStreamEvent<CKickLog>* event = new CStreamEvent<CKickLog>(myEVT_THREAD_KICK);
    CKickLog* log = new CKickLog();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_channel);
    log->setUserName(message.m_username);
    log->setTarget(message.m_target);
    event->setServiceLog(log);
    return event;

}

CConnectionEventBase* CIRCEventFactory::createInviteEvent(
        const CIRCMessageData& message) const
{
    CStreamEvent<CInviteLog>* event = new CStreamEvent<CInviteLog>(myEVT_THREAD_INVITE);
    CInviteLog* log = new CInviteLog();
    log->setServiceId(m_connectionId);
    log->setChannelName(message.m_body);
    log->setUserName(message.m_username);
    event->setServiceLog(log);
    return event;
}
}
}

