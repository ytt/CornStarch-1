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
CConnectionEventBase* CSCEventFactory::Create(CSCMessageData message)
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
        CStreamEvent<CMessageLog>* event = new CStreamEvent<CMessageLog>(myEVT_THREAD_STREAM_MSG_ADD);
        CMessageLog* log = new CMessageLog();
        log->init(new CMessageData(message));
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);

        return event;
    }
    if (message.m_type == CSCMessageType::JOIN){
        CStreamEvent<CJoinLog>* event = new CStreamEvent<CJoinLog>(myEVT_THREAD_STREAM_CH_JOIN);
        CJoinLog* log = new CJoinLog();
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);

        return event;
    }
    if (message.m_type == CSCMessageType::PART){
        CStreamEvent<CPartLog>* event = new CStreamEvent<CPartLog>(myEVT_THREAD_STREAM_CH_PART);
        CPartLog* log = new CPartLog();
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::TOPIC){

        CStreamEvent<CTopicLog>* event = new CStreamEvent<CTopicLog>(myEVT_THREAD_STREAM_CH_UPDATE);
        CTopicLog* log = new CTopicLog();
        log->setServiceId(m_connectionId);
        log->setChannelName(message.m_channelData.m_name);
        log->setTopic(message.m_channelData.m_topic);
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::NICK){
        CStreamEvent<CMemberLog>* event = new CStreamEvent<CMemberLog>(myEVT_THREAD_STREAM_USER_UPDATE);
        CMemberLog* log = new CMemberLog();
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

