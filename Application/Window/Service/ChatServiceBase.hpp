﻿#pragma once
#include "ChannelHolder.hpp"
#include "NickTable.hpp"
#include "IUser.hpp"
#include "IConnection.hpp"
#include "ICommandInvoker.hpp"
#include "Message/ChatMessage.hpp"
#include "ServiceConfiguration.hpp"

namespace CornStarch
{
;

// 通信のModelコンテンツを扱うクラス
class CChatServiceBase
{
public:
    // チャットの種類
    enum CHAT_TYPE
    {
        STAR_CHAT = 0, IRC,
    };
    enum CONNECTION_STATE
    {
        CONNECTED = 0, CONNECTING = 1, DISCONNECT = 2
    };
protected:
    // イベントハンドラ
    wxEvtHandler* m_handler;
    // コマンドからの命令実行者
    ICommandInvoker* m_commandInvoker;
    // StarChatのデータ部
    IConnection* m_connect; // 通信を司るクラス
    CChannelHolder* m_channel; // チャンネル情報を保持
    IUser* m_user; // ユーザ情報
    CNickTable* m_nickTable; // ニックネームテーブル

    CServiceConfiguration* m_configuration; // サービスの設定項目
    // 名前
    wxString m_name;
    // ID
    int m_id;


    // チャットの種類
    CHAT_TYPE m_type;
    // 接続状態
    CONNECTION_STATE m_state;
    // 保存されていたチャンネル
    vector<wxString> savedChannels;
public:
    CChatServiceBase(void);
    virtual ~CChatServiceBase(void);

    // IDを取得
    int getId() const
    {
        return m_id;
    }
    // IDを設定
    void setId(int id)
    {
        m_id = id;
    }

    // 接続されているかを取得
    bool IsConnected() const
    {
        return m_state == CChatServiceBase::CONNECTED;
    }

    // 雪族されているかを設定
    void setConnected(bool isConnected)
    {
        if (isConnected){
            m_state = CChatServiceBase::CONNECTED;
        } else{
            m_state = CChatServiceBase::DISCONNECT;
        }
    }

    // 保存されていたチャンネルを設定します。
    void setSavedChannels(vector<wxString> savedChannels)
    {
        this->savedChannels = savedChannels;
    }

    // 名前を取得
    wxString getName() const
    {
        return m_name;
    }

    // 名前を設定
    void setName(wxString name)
    {
        m_name = name;
    }
    // ホストを取得
    wxString getHost() const
    {
        return m_connect->getHost();
    }
    // コマンドの取得。
    ICommandInvoker* getCommandInvoker() const
    {
        return m_commandInvoker;
    }
    // ホストを設定
    void setHost(wxString value)
    {
        m_connect->setHost(value);
    }
    // ホストを取得
    int getPort() const
    {
        return m_connect->getPort();
    }

    // ホストを設定
    void setPort(int value)
    {
        m_connect->setPort(value);
    }
    // チャットの種類を取得
    CHAT_TYPE getChatType(void) const
    {
        return m_type;
    }
    CServiceConfiguration* getConfiguration() const
     {
         return m_configuration;
     }

     void setConfiguration(CServiceConfiguration* configuration)
     {
         m_configuration = configuration;
     }
    // ユーザーの取得
    IUser* getUser() const
    {
        return m_user;
    }
    // 初期化を行う
    virtual void init(wxEvtHandler* handler) = 0;

    // ユーザ登録を行った際のデータ更新
    void registerUser(const wxString& userName, const wxString& pass);

    // ユーザ登録を行った際のデータ更新
    void registerUserBasiscEncoded(const wxString& userName,
            const wxString& pass);

    // チャンネルに参加を行う際
    void joinChannel(const wxString& channel);

    // チャンネルから離脱する際
    void partChannel(const wxString& channel);

    // ログの追加
    void addLog(CMessage* log);
    // 接続する
    void connect(void);
    // 再接続を行う
    virtual void reconnect(void) = 0;
    // 切断を行う。
    void disconnect(void);
    // 各チャンネルの情報を破棄
    void clearChannels(void);

    // ニックネームテーブルを破棄
    void clearNickTable(void);

    // 現在のチャンネル名を取得
    wxString getCurrentChannel(void) const;

    // メッセージを生成
    CChatMessage* generateMessage(const wxString& body);

    // メッセージを投稿した際
    void postMessage(CChatMessage* message);

    // チャンネルを選択した際
    void selectChannel(const wxString& channel);

    // チャンネルを取得
    std::vector<CChannelStatus*> getChannels(void) const;

    // チャンネル一覧を取得
    CChannelStatus* getChannel(const wxString& channel) const;
    // メッセージ一覧を取得
    std::vector<CMessage*> getLogs(const wxString& channel) const;

    // メンバー一覧を取得
    std::vector<CMemberData*> getMembers(const wxString& channel) const;

    // ニックネームテーブルを取得
    CNickTable getNickTable(void) const;

    // ユーザが呼ばれたか
    bool isUserCalled(const wxString& message);

    // メンバーのニックネームを取得
    wxString getMemberNick(const wxString& member);

    // メンバーの本名を取得
    wxString getMemberRealName(const wxString& nick) const;

    // チャンネルのトピックを取得
    wxString getTopic(const wxString& channel);

    // このクライアントから投稿されたメッセージか
    bool isPostedThisClient(const CChatMessage* message);

    // メッセージ表示を行う際
    void onUpdateMessageView(const wxString& channel);

    // メンバー表示を行う際
    void onUpdateMemberView(const wxString& channel);

    // チャンネル表示を行う際
    void onUpdateChannelView(void);

    // ニックネームの変更を行う際
    void onNickChange(const wxString& nick);

    // トピックの変更を行う際
    void onChangeTopic(const wxString& topic);

    /////////////////////////////////////////

    // 認証が成功した場合
    virtual void onAuthSucceeed(void);

    // メッセージ一覧を取得した場合
    void onGetMessages(const wxString channleName,
            const std::vector<CResponseData*>& messages);

    // メンバー一覧を取得した場合
    void onGetMembers(const wxString& channel, const std::vector<CMemberData*>& members);

    // チャンネル一覧を取得した場合
    void onGetChannels(const std::vector<CChannelData*>& channels);

    // チャンネル参加成功時
    void onJoinChannel(const wxString& channel);

    // チャンネル離脱成功時
    void onPartChannel(const wxString& channel);

    // メンバー情報を取得した場合
    void onGetMemberStatus(const CMemberData& member);

    // メッセージストリームを取得した場合
    void onGetMessageStream( CChatMessage* message);

    // チャンネル参加ストリームを受信
    void onGetJoinStream(const wxString& channel, const wxString& name);

    // チャンネル離脱ストリームを受信
    void onGetPartStream(const wxString& channel, const wxString& name);

    // チャンネル情報更新ストリームを受信
    void onGetChannelStream(const wxString& channelName,const wxString& topic);

    // ユーザ情報更新ストリームの受信
    void onGetUserStream(const wxString& userName,const wxString& nick);
}





;

}
