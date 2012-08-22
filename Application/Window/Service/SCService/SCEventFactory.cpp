#include "SCEventFactory.hpp"
#include "../Event/ConnectionEventBase.hpp"
#include "../Event/DisconnectEvent.hpp"
#include "../Event/PartEvent.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/JoinEvent.hpp"
#include "../Event/MsgStreamEvent.hpp"
#include "../Event/ChannelStreamEvent.hpp"
#include "../Event/JoinStreamEvent.hpp"
#include "../Event/PartStreamEvent.hpp"
#include "../Event/UserStreamEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/GetMemberEvent.hpp"
#include "../Event/GetMemberInfoEvent.hpp"
#include "../Event/GetChannelEvent.hpp"
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
        CMsgStreamEvent* event = new CMsgStreamEvent();
        CMessageLog* log = new CMessageLog();
        log->init(message);
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);

        return event;
    }
    if (message.m_type == CSCMessageType::JOIN){
        CJoinStreamEvent* event = new CJoinStreamEvent();
        CJoinLog* log = new CJoinLog();
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);

        return event;
    }
    if (message.m_type == CSCMessageType::PART){
        CPartStreamEvent* event = new CPartStreamEvent();
        CPartLog* log = new CPartLog();
        log->setChannelName(message.m_channel);
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::TOPIC){
        CChannelStreamEvent* event = new CChannelStreamEvent();
        CTopicLog* log = new CTopicLog();
        log->setChannelName(message.m_channelData.m_name);
        log->setTopic(message.m_channelData.m_topic);
        log->setUserName(message.m_username);
        event->setServiceLog(log);
        return event;
    }
    if (message.m_type == CSCMessageType::NICK){
        CUserStreamEvent* event = new CUserStreamEvent();
        CMemberLog* log = new CMemberLog();
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

