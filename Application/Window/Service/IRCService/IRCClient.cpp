﻿#include "IRCClient.hpp"
#include "Task/IRCStartTask.hpp"
#include "Task/IRCSendTask.hpp"
#include "IRCCommand.hpp"
#include "Task/IRCReceiveTask.hpp"
namespace CornStarch
{
;
namespace IRC
{
;

using namespace std;
BEGIN_EVENT_TABLE(CIRCClient, wxEvtHandler)
EVT_SOCKET(SOCKET_ID, CIRCClient::onSocketEvent)
END_EVENT_TABLE()
CIRCClient::CIRCClient() :m_conenctTask(NULL),
        m_receiveTask(NULL), m_sendTask(NULL), m_isConnectedToIRCService(false)
{
    m_commandQueue = new wxMessageQueue<wxString>();
}
void CIRCClient::onSocketEvent(wxSocketEvent &event)
{
    if(event.GetSocketEvent() == wxSOCKET_LOST)
    {
        disconnect();
    }
}
CIRCClient::~CIRCClient(void)
{
    delete m_conenctTask;
    delete m_commandQueue;
    delete m_receiveTask;
    delete m_sendTask;
}
void CIRCClient::init(IMessageConnectionObserver* observer)
{
    CSocketClient::init();
    m_observer = observer;
    m_socket->SetTimeout(2);

    m_socket->SetNotify(
            wxSOCKET_INPUT_FLAG | wxSOCKET_CONNECTION_FLAG
                    | wxSOCKET_LOST_FLAG);

    m_socket->SetEventHandler(*this, SOCKET_ID);
    m_socket->Notify(true);
}
void CIRCClient::startAsync(const wxString& userName, const wxString& password)
{
    if (m_socket->IsConnected()){
        return;
    }

    // 通信開始用スレッド
    CIRCStartTask *task = new CIRCStartTask(wxTHREAD_JOINABLE);
    task->init(this);
    task->setUserName(userName);
    task->setPassword(password);
    m_conenctTask = task;

    // 送信用スレッド
    CIRCSendTask *sendTask = new CIRCSendTask(wxTHREAD_JOINABLE);
    sendTask->init(this);
    m_sendTask = sendTask;

    //　受信用スレッド
    CIRCReceiveTask *receiveTask = new CIRCReceiveTask(wxTHREAD_JOINABLE);
    receiveTask->init(this);
    m_receiveTask = receiveTask;

    task->continueWith(sendTask);
    task->continueWith(receiveTask);
    startThread(task);
}

void CIRCClient::addCommandQueue(const wxString& content)
{
    m_commandQueue->Post(content);
}
void CIRCClient::sendCommand(const wxString& command)
{
    send(command);
    if (m_socket->Error()){
        if (m_isConnectedToIRCService){ // IRCに接続中
            getObserver()->onDisconnected();
        } else{ // IRCに接続できていない
            getObserver()->onConnectionFailed();
        }
    }
}
void CIRCClient::startThread(wxThread* task)
{
    if (task->Create() != wxTHREAD_NO_ERROR){
        delete task;
        task = NULL;
        return;
    }

    // 別スレッドを走らせる
    if (task->Run() != wxTHREAD_NO_ERROR){
        delete task;
        task = NULL;
        return;
    }
}
void CIRCClient::quitAsync(void)
{
    wxString content(IRCCommand::QUIT);
    addCommandQueue(content);
}
void CIRCClient::pong(const wxString& value)
{
    wxString content(wxString::Format(wxT("%s %s"), IRCCommand::PONG, value));
    addCommandQueue(content);
}
void CIRCClient::disconnect(void)
{
    //スレッドの終了待機
    if (m_conenctTask != NULL && m_conenctTask->IsAlive()){
        if (m_conenctTask->IsRunning()){
            m_conenctTask->Delete();
        }
    }
    if (m_sendTask != NULL && m_sendTask->IsAlive()){
        if (m_sendTask->IsRunning()){
            m_sendTask->Delete();
        }
    }
    if (m_receiveTask != NULL && m_receiveTask->IsAlive()){
        if (m_receiveTask->IsRunning()){
            m_receiveTask->Delete();
        }
    }
    this->close();
}
wxString CIRCClient::recieveData()
{
    this->m_buffer = "";
    this->receive();
    return wxString(this->m_buffer.c_str(), wxConvUTF8);
}
void CIRCClient::joinAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxT("%s %s"), IRCCommand::JOIN, channelName));
    addCommandQueue(content);
}
void CIRCClient::partAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxT("%s %s"), IRCCommand::PART, channelName));
    addCommandQueue(content);
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxT("%s %s"), IRCCommand::TOPIC, channelName));
    addCommandQueue(content);

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxT("%s %s"), IRCCommand::NAMES, channelName));
    addCommandQueue(content);
}

void CIRCClient::sendMessageAsync(const wxString& target,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s %s :%s"), IRCCommand::PRIVMSG, target,
                    content));
    addCommandQueue(contentWxString);
}
void CIRCClient::sendNoticeAsync(const wxString& target,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s %s :%s"), IRCCommand::NOTICE, target,
                    content));

    addCommandQueue(contentWxString);
}
void CIRCClient::changeTopicAsync(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s %s :%s"), IRCCommand::TOPIC, channelName,
                    content));
    addCommandQueue(contentWxString);
}
void CIRCClient::changeNicknameAsync(const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s :%s"), IRCCommand::NICK, content));
    addCommandQueue(contentWxString);
}
}
} /* namespace CornStarch */
