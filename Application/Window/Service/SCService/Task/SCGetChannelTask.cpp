﻿#include "SCGetChannelTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCGetChannelTask::CSCGetChannelTask(void)
{
}


CSCGetChannelTask::~CSCGetChannelTask(void)
{
}



// StarChatに対してリクエストを送信する
void CSCGetChannelTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetChannelsRequest(m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCGetChannelTask::notifyMessage(const string& responseBody)
{
    CSCJsonParser parser;
    CSCResponseData message;
    message.m_type = CSCMessageType::GET_CHANNEL;
    message.m_channels = parser.getChannels(responseBody);
    m_observer->onMessageReceived(&message);
}

}
}
