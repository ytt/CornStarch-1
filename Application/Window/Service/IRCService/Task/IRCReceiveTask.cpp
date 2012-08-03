﻿#include "IRCReceiveTask.hpp"
#include "../IRCParser.hpp"
#include "../IRCCommand.hpp"
#include  "../StringUtility.hpp"
#include "../../Event/AuthEvent.hpp"
#include "../../Event/DisconnectEvent.hpp"
#include "../../Event/GetMemberEvent.hpp"
#include "../../Event/MsgStreamEvent.hpp"
#include "../../Event/GetMessageEvent.hpp"
#include "../../Event/MsgStreamEvent.hpp"
#include "../../Event/ChannelStreamEvent.hpp"
#include "../../Event/JoinStreamEvent.hpp"
#include "../../Event/PartStreamEvent.hpp"
#include "../../Event/UserStreamEvent.hpp"
#include "../../Event/AuthEvent.hpp"
#include "../../Event/ConnectionEventBase.hpp"

namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_DISCONNECT, CDisconnectEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
namespace IRC
{
;
CIRCReceiveTask::CIRCReceiveTask(wxThreadKind kind) :
        CIRCTask(kind), m_receiveBuffer(""), m_namesBuffer(""), isConnectedToIRCService(
                false)
{

}

CIRCReceiveTask::~CIRCReceiveTask()
{
}

void CIRCReceiveTask::pong(const wxString& value)
{
    wxString content(wxString::Format(wxT("%s %s"), IRCCommand::PONG, value));
    m_client->addCommandQueue(content);
}
// Run実行時に呼ばれる本体
wxThread::ExitCode CIRCReceiveTask::Entry(void)
{
    CIRCParser parser;
    //　ソケットが切断されているか、自分で終了しようとしていればループ終了
    while (m_client->isSocketConnected() && this->TestDestroy() == false){
        m_receiveBuffer += m_client->recieveData();

        if (m_receiveBuffer != ""
                && m_receiveBuffer.Find("\n") != wxString::npos){
            vector<wxString> messages = CStringUtility::split(m_receiveBuffer,
                    "\n");
            int messageSize = messages.size();
            for (int index = 0; index < messages.size(); index++){
                // PING応答
                if (messages[index].find(IRCCommand::PING) == 0){
                    wxString pingValue = CStringUtility::split(messages[index],
                            ":")[1];
                    pong(pingValue);
                } else if (messages[index].find(IRCCommand::_ERROR) == 0){
                    // エラー
                    break;
                } else{
                    // イベント生成
                    CIRCMessageData message = parser.parse(messages[index]);
                    CConnectionEventBase* event = createEvent(message);
                    if (event != NULL){
                        event->setConnectionId(m_connectionId);
                        wxQueueEvent(m_handler, event);
                    }
                }
            }
            m_receiveBuffer = "";
        }
        // IRCプロトコルの最大値を超えるメッセージを受信している場合は、バッファをクリアする。
        if (m_receiveBuffer.Length() > 512){
            m_receiveBuffer = "";
        }
        wxUsleep(100);
    }
    // 故意でない切断時
    if (this->TestDestroy() == false){
        if (isConnectedToIRCService){   // IRCに接続中
            CDisconnectEvent* event = new CDisconnectEvent();
            event->SetEventType(myEVT_THREAD_DISCONNECT); // イベントの種類をセット
            event->setConnectionId(m_connectionId);
            wxQueueEvent(m_handler, event);
        } else // IRCに接続できていない
        {
            CAuthEvent* event = new CAuthEvent();
            event->setAuthResult(false);
            event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
            event->setConnectionId(m_connectionId);
             wxQueueEvent(m_handler, event);
        }
    }
    // 成功時
    return (wxThread::ExitCode) 0;
}

CConnectionEventBase* CIRCReceiveTask::createEvent(
        const CIRCMessageData& message)
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
        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
        return event;
    }
    if (message.m_statusCode == IRCCommand::OK){ // 接続開始リプライ
        isConnectedToIRCService = true;
        //接続
        CAuthEvent* event = new CAuthEvent();
        event->setAuthResult(true);
        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
        return event;
    }
    return NULL;
}

CConnectionEventBase* CIRCReceiveTask::createNickMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CMemberData member;
    member.m_name = wxString(message.m_username);
    member.m_nick = wxString(message.m_body);

    CUserStreamEvent* event = new CUserStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
    event->setMember(member);
    return event;
}
CConnectionEventBase* CIRCReceiveTask::createTopicMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CChannelData channel;
    channel.m_name = wxString(message.m_channel);
    channel.m_topic = wxString(message.m_body);

    CChannelStreamEvent* event = new CChannelStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
    event->setChannel(channel);
    return event;
}
CConnectionEventBase* CIRCReceiveTask::createJoinMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CJoinStreamEvent* event = new CJoinStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
    event->setChannelName(message.m_body);
    event->setUserName(message.m_username);
    return event;
}
CConnectionEventBase* CIRCReceiveTask::createPartMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CPartStreamEvent* event = new CPartStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_PART);
    event->setChannelName(message.m_channel);
    event->setUserName(message.m_username);
    return event;

}
CConnectionEventBase* CIRCReceiveTask::createPrivateMessageEvent(
        const CIRCMessageData& message) const
{
    // Eventの作成
    CMsgStreamEvent* event = new CMsgStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
    event->setMessage(message);
    return event;
}

void CIRCReceiveTask::addNames(const CIRCMessageData& message)
{
    int index = message.m_param.find(":");
    wxString names = message.m_param.substr(index + 1);
    m_namesBuffer += names;
}
CConnectionEventBase* CIRCReceiveTask::createNamesEvent(
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
            mem->m_name = names[i]; // 名前(name)
            mem->m_nick = names[i]; // ニックネーム(name)
            // vectorに追加
            result.push_back(mem);
        }
    }

    CGetMemberEvent* event = new CGetMemberEvent();
    event->setMembers(result); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MEMBER); // イベントの種類をセット
    m_namesBuffer = "";
    return event;
}

CConnectionEventBase* CIRCReceiveTask::createTopicEvent(
        const CIRCMessageData& message) const
{
    return NULL;
}

CConnectionEventBase* CIRCReceiveTask::createKickEvent(
        const CIRCMessageData& message) const
{
    return NULL;
}

CConnectionEventBase* CIRCReceiveTask::createInviteEvent(
        const CIRCMessageData& message) const
{
    return NULL;
}

}
} /* namespace CornStarch */
