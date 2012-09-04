#include "MainWindow.hpp"
#include "wx/event.h"

namespace CornStarch
{;

// typedef
typedef void (wxEvtHandler::*AuthEventFunction)(CAuthEvent&);
typedef void (wxEvtHandler::*DisconnectEvtFunc)(CDisconnectEvent&);
typedef void (wxEvtHandler::*DelPartEvtFunction)(CPartEvent&);
typedef void (wxEvtHandler::*GetMemberEvtFunc)(CGetMemberEvent&);
typedef void (wxEvtHandler::*GetChannelEvtFunc)(CGetChannelEvent&);
typedef void (wxEvtHandler::*GetMessageEvtFunc)(CGetMessageEvent&);
typedef void (wxEvtHandler::*GetMemberInfoEvtFunc)(CGetMemberInfoEvent&);

typedef void (wxEvtHandler::*GetMsgStreamEvtFunc)(CStreamEvent<CChatMessage>&);
typedef void (wxEvtHandler::*GetMemStreamEvtFunc)(CStreamEvent<CMemberMessage>&);
typedef void (wxEvtHandler::*GetChStreamEvtFunc)(CStreamEvent<CTopicMessage>&);
typedef void (wxEvtHandler::*GetChPartStreamEvtFunc)(CStreamEvent<CPartMessage>&);
typedef void (wxEvtHandler::*GetChJoinStreamEvtFunc)(CStreamEvent<CJoinMessage>&);
typedef void (wxEvtHandler::*InviteEvtFunc)(CStreamEvent<CInviteMessage>&);
typedef void (wxEvtHandler::*KickEvtFunc)(CStreamEvent<CKickMessage>&);
typedef void (wxEvtHandler::*JoinEvtFunc)(CJoinEvent&);
typedef void (wxEvtHandler::*SelectEvtFunc)(CChannelSelectEvent&);

// define
wxDEFINE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDEFINE_EVENT(myEVT_THREAD_DISCONNECT,CDisconnectEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);

wxDEFINE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CStreamEvent<CChatMessage>);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CStreamEvent<CJoinMessage>);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_CH_PART, CStreamEvent<CPartMessage>);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CStreamEvent<CTopicMessage>);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CStreamEvent<CMemberMessage>);
wxDEFINE_EVENT(myEVT_THREAD_INVITE, CStreamEvent<CInviteMessage>);
wxDEFINE_EVENT(myEVT_THREAD_KICK, CStreamEvent<CKickMessage>);

wxDEFINE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);
wxDEFINE_EVENT(myEVT_THREAD_DELETE_PART, CPartEvent);
wxDEFINE_EVENT(myEVT_THREAD_POST_MESSAGE, wxThreadEvent);
wxDEFINE_EVENT(myEVT_SELECT_TREE_NODE, CChannelSelectEvent);
wxDEFINE_EVENT(myEVT_SELECT_TREE_NODE_RIGHT, CChannelSelectEvent);
wxDEFINE_EVENT(myEVT_FOCUSE_NEXT_INPUT_TEXT, wxThreadEvent);
wxDEFINE_EVENT(myEVT_KEYDDOWN_ON_POSTPANE, wxKeyEvent);

// イベントハンドラ
#define authEventHandler(func) wxEVENT_HANDLER_CAST(AuthEventFunction, func)
#define disconnectEventHandler(func) wxEVENT_HANDLER_CAST(DisconnectEvtFunc, func)
#define delPartEventHandler(func) wxEVENT_HANDLER_CAST(DelPartEvtFunction, func)
#define getMemberEventHandler(func) wxEVENT_HANDLER_CAST(GetMemberEvtFunc, func)
#define getChannelEventHandler(func) wxEVENT_HANDLER_CAST(GetChannelEvtFunc, func)
#define getMessageEventHandler(func) wxEVENT_HANDLER_CAST(GetMessageEvtFunc, func)
#define getMemberInfoEventHandler(func) wxEVENT_HANDLER_CAST(GetMemberInfoEvtFunc, func)
#define getMsgStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetMsgStreamEvtFunc, func)
#define getMemStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetMemStreamEvtFunc, func)
#define getChStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetChStreamEvtFunc, func)
#define getChJoinStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetChJoinStreamEvtFunc, func)
#define getChPartStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetChPartStreamEvtFunc, func)
#define joinEventHandler(func) wxEVENT_HANDLER_CAST(JoinEvtFunc, func)
#define selectEventHandler(func) wxEVENT_HANDLER_CAST(SelectEvtFunc, func)
#define inviteEventHandler(func) wxEVENT_HANDLER_CAST(InviteEvtFunc, func)
#define kickEventHandler(func) wxEVENT_HANDLER_CAST(KickEvtFunc, func)

#define EVT_DEL_PART(evt, id, func) wx__DECLARE_EVT1(evt, id, delPartEventHandler(func))
#define EVT_GET_AUTH(evt, id, func) wx__DECLARE_EVT1(evt, id, authEventHandler(func))
#define EVT_GET_DISCONNECT(evt, id, func) wx__DECLARE_EVT1(evt, id, disconnectEventHandler(func))
#define EVT_GET_MEMBER(evt, id, func) wx__DECLARE_EVT1(evt, id, getMemberEventHandler(func))
#define EVT_GET_CHANNEL(evt, id, func) wx__DECLARE_EVT1(evt, id, getChannelEventHandler(func))
#define EVT_GET_MESSAGE(evt, id, func) wx__DECLARE_EVT1(evt, id, getMessageEventHandler(func))
#define EVT_GET_MEMBER_INFO(evt, id, func) wx__DECLARE_EVT1(evt, id, getMemberInfoEventHandler(func))
#define EVT_GET_MSG_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getMsgStreamEventHandler(func))
#define EVT_GET_MEM_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getMemStreamEventHandler(func))
#define EVT_GET_CH_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getChStreamEventHandler(func))
#define EVT_GET_JOIN_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getChJoinStreamEventHandler(func))
#define EVT_GET_PART_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getChPartStreamEventHandler(func))
#define EVT_PUT_JOIN(evt, id, func) wx__DECLARE_EVT1(evt, id, joinEventHandler(func))
#define EVT_SELECT_TREE_NODE(evt, id, func) wx__DECLARE_EVT1(evt, id, selectEventHandler(func))

#define EVT_KEYDDOWN_ON_POSTPANE(evt, id, func) wx__DECLARE_EVT1(evt, id, wxKeyEventHandler(func))
#define EVT_FOCUSE_NEXT_INPUT_TEXT(evt, id, func) wx__DECLARE_EVT1(evt, id, wxThreadEventHandler(func))
#define EVT_INVITE(evt, id, func) wx__DECLARE_EVT1(evt, id, inviteEventHandler(func))
#define EVT_KICK(evt, id, func) wx__DECLARE_EVT1(evt, id, kickEventHandler(func))

// イベントテーブルの登録
BEGIN_EVENT_TABLE(CMainWindow, wxFrame)

    // メニューバー
    EVT_MENU(wxID_EXIT, CMainWindow::onQuit) // 終了
    EVT_MENU(wxID_COPY, CMainWindow::onCopy) // 終了
    EVT_MENU(CMenuPart::MENU_EDIT_FIND, CMainWindow::onFind) // 検索

    EVT_MENU(CMenuPart::MENU_SERVER_ADD, CMainWindow::onServiceRegister) // サーバの登録
    EVT_MENU(CMenuPart::MENU_SERVER_DELETE, CMainWindow::onDeleteService) // サーバの削除
    EVT_MENU(CMenuPart::MENU_SERVER_NICK_CHANGE, CMainWindow::onNickChange) // ニックネーム変更
    EVT_MENU(CMenuPart::MENU_CHANNEL_JOIN, CMainWindow::onJoin) // チャンネルに参加
    EVT_MENU(CMenuPart::MENU_CHANNEL_PART, CMainWindow::onPart) // チャンネルから離脱
    EVT_MENU(CMenuPart::MENU_CHANNEL_TOPIC_CHANGE, CMainWindow::onChangeTopic) // トピック変更

    EVT_MENU(CMenuPart::MENU_SERVER_MOVETO_UNREAD, CMainWindow::onMoveToUnread) // 未読へ移動
    EVT_MENU(CMenuPart::MENU_UPDATE, CMainWindow::onUpdateDisplay) // 更新


    // 通信による結果を受け取ったとき
    EVT_GET_AUTH(myEVT_THREAD_GET_PING, wxID_ANY, CMainWindow::onGetAuth)
    EVT_GET_DISCONNECT(myEVT_THREAD_DISCONNECT, wxID_ANY, CMainWindow::onDisconnect)
    EVT_DEL_PART(myEVT_THREAD_DELETE_PART, wxID_ANY, CMainWindow::onPartChannel)
    EVT_GET_MEMBER(myEVT_THREAD_GET_MEMBER, wxID_ANY, CMainWindow::onGetMembers)
    EVT_GET_MESSAGE(myEVT_THREAD_GET_MESSAGE, wxID_ANY, CMainWindow::onGetMessages)
    EVT_GET_CHANNEL(myEVT_THREAD_GET_CHANNEL, wxID_ANY, CMainWindow::onGetChannels)
    EVT_GET_MEMBER_INFO(myEVT_THREAD_GET_MEMBER_INFO, wxID_ANY, CMainWindow::onGetMemberInfo)    
    EVT_GET_MSG_STREAM(myEVT_THREAD_STREAM_MSG_ADD, wxID_ANY, CMainWindow::onMsgStream)
    EVT_GET_MEM_STREAM(myEVT_THREAD_STREAM_USER_UPDATE, wxID_ANY, CMainWindow::onUserStream)
    EVT_GET_CH_STREAM(myEVT_THREAD_STREAM_CH_UPDATE, wxID_ANY, CMainWindow::onChannelStream)
    EVT_GET_JOIN_STREAM(myEVT_THREAD_STREAM_CH_JOIN, wxID_ANY, CMainWindow::onJoinStream)
    EVT_GET_PART_STREAM(myEVT_THREAD_STREAM_CH_PART, wxID_ANY, CMainWindow::onPartStream)
    EVT_PUT_JOIN(myEVT_THREAD_PUT_JOIN, wxID_ANY, CMainWindow::onJoinChannel)
    EVT_KICK(myEVT_THREAD_KICK, wxID_ANY, CMainWindow::onKick)
    EVT_INVITE(myEVT_THREAD_INVITE, wxID_ANY, CMainWindow::onInvite)
        
    // チャンネルツリーの項目を選択
    EVT_SELECT_TREE_NODE(myEVT_SELECT_TREE_NODE, wxID_ANY, CMainWindow::onChannelSelected)
    EVT_SELECT_TREE_NODE(myEVT_SELECT_TREE_NODE_RIGHT, wxID_ANY, CMainWindow::onChannelRightClicked)

    // テキストボックスでTabを押してフォーカスを移動した
    EVT_FOCUSE_NEXT_INPUT_TEXT(myEVT_FOCUSE_NEXT_INPUT_TEXT, wxID_ANY, CMainWindow::onFocusNextText)

    // テキストボックスでキーを押した
    EVT_KEYDDOWN_ON_POSTPANE(myEVT_KEYDDOWN_ON_POSTPANE, wxID_ANY, CMainWindow::onKeyDownOnPostPane)
END_EVENT_TABLE();



}
