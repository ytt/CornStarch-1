﻿#ifndef IConnection_H_
#define IConnection_H_
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "IUser.hpp"
#include "IMessageConnectionObserver.hpp"

using namespace std;

namespace CornStarch
{;

// 通信部分のインターフェース
class IConnection : public IMessageConnectionObserver
{

public:
    IConnection(){
    }
    virtual ~IConnection() {
    }

    // 初期化を行う
    virtual void init(int connectionId,wxEvtHandler* handler) = 0;

    // 切断を行う。
    virtual void disconnect() = 0;

    // メッセージを投稿するタスク(別スレッド)を開始する
    virtual void startPostMessageTask(const IUser* user, const wxString& message,
        const wxString& channel)=0;

    // チャンネルのメッセージを取得するタスク(別スレッド)を開始する
    virtual void startGetMessageTask(const IUser* user, const wxString& channel)=0;

    // チャンネルのメンバーを取得するタスク(別スレッド)を開始する
    virtual void startGetMemberTask(const IUser* user, const wxString& channel)=0;

    // ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
    virtual void startGetChannelTask(const IUser* user)=0;

    // チャンネルから離脱するタスク(別スレッド)を開始する
    virtual void startPartTask(const IUser* user, const wxString& channel)=0;

    // チャンネルに参加するタスク(別スレッド)を開始する
    virtual void startJoinTask(const IUser* user, const wxString& channel)=0;

    // メンバーの情報を取得するタスク(別スレッド)を開始する
    virtual void startGetMemberInfoTask(const IUser* user,const wxString& name)=0;

    // ニックネームを変更するタスク(別スレッド)を開始する
    virtual void startNickChangeTask(const IUser* user, const wxString& nick) = 0;

    // トピックを変更するタスク(別スレッド)を開始する
    virtual void startChangeTopicTask(const IUser* user, const wxString& topic) = 0;

    // ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
    virtual void startAuthTask(const IUser* user)=0;

    // ストリーム通信タスク(別スレッド)を開始
    virtual void startStreamTask(const IUser* user)=0;

    // ホストを取得
    virtual wxString getHost() const = 0;

    // ホストを設定
    virtual void setHost(const wxString& host) = 0;

    // ポートを設定
    virtual void setPort(int port) =0;
    // ポートを取得
    virtual int getPort() const = 0;
};

}
#endif /* IConnection_H_ */
