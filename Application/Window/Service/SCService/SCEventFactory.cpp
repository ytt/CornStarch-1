#include "SCEventFactory.hpp"
#include "../Event/ConnectionEventBase.hpp"
#include "../Event/DisconnectEvent.hpp"
#include "../Event/PartEvent.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/JoinEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/GetMemberEvent.hpp"
#include "../Event/GetMemberInfoEvent.hpp"
#include "../Event/GetChannelEvent.hpp"
#include "../Event/StreamEvent.hpp"
#include "../IMessageConnectionObserver.hpp"

namespace CornStarch
{

namespace StarChat
{
CSCEventFactory::CSCEventFactory()
{

}

CSCEventFactory::~CSCEventFactory()
{
}
CConnectionEventBase* CSCEventFactory::Create(CSCResponseData message)
{
    if (message.m_type == CSCMessageType::GET_CHANNEL){
        CGetChannelEvent* event = new CGetChannelEvent();
        event->setChannels(message.m_channels); // 値取得
        return event;
    }
    if (message.m_type == CSCMessageType::GET_MEMBER){
        CGetMemberInfoEvent* event = new CGetMemberInfoEvent();
        event->setMember(message.m_member); // 値取得
        return event;
    }
    if (message.m_type == CSCMessageType::GET_MEMBERS){
        CGetMemberEvent* event = new CGetMemberEvent();
        event->setMembers(message.m_members); // 値取得
        event->setChannel(message.m_channel);
        return event;
    }
    if (message.m_type == CSCMessageType::GET_MESSAGES){
        CGetMessageEvent* event = new CGetMessageEvent();
        event->setMessages(message.m_messages); // 値取得
        event->setChannel(message.m_channel); // チャンネル
        return event;
    }
    if (message.m_type == CSCMessageType::MESSAGE){
        CStreamEvent<CChatMessage>* event = new CStreamEvent<CChatMessage>(myEVT_THREAD_STREAM_MSG_ADD);
        CChatMessage* log = new CChatMessage();
        log->init(&message);
        log->setServiceId(m_connectionId);
        event->setServiceLog(log);

        return event;
    }
    if (message.m_type == CSCMessageType::JOIN){
        CStreamEvent<CJoinMessage>* event = new CStreamEvent<CJoinMessage>(myEVT_THREAD_STREAM_CH_JOIN);
        CJoinMessage* log = new CJoinMessage();
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);

        return event;
    }
    if (message.m_type == CSCMessageType::PART){
        CStreamEvent<CPartMessage>* event = new CStreamEvent<CPartMessage>(myEVT_THREAD_STREAM_CH_PART);
        CPartMessage* log = new CPartMessage();
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::TOPIC){

        CStreamEvent<CTopicMessage>* event = new CStreamEvent<CTopicMessage>(myEVT_THREAD_STREAM_CH_UPDATE);
        CTopicMessage* log = new CTopicMessage();
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channelData.m_name);
        log->setTopic(message.m_channelData.m_topic);
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::NICK){
        CStreamEvent<CMemberMessage>* event = new CStreamEvent<CMemberMessage>(myEVT_THREAD_STREAM_USER_UPDATE);
        CMemberMessage* log = new CMemberMessage();
        log->setServiceId(m_connectionId);
        log->setUserName(message.m_member.m_name);
        log->setNickName(message.m_member.m_nick);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::JOIN_REPLY){
        CJoinEvent* event = new CJoinEvent();
        event->SetString(message.m_channel); // 新チャンネル名
        return event;
    }
    if (message.m_type == CSCMessageType::PART_REPLY){
        CConnectionEventBase* event = new CPartEvent();
        event->SetString(message.m_channel);
        return event;
    }
    return NULL;
}
}
} // namespace CornStarch

