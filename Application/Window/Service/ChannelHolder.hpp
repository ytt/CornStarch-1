﻿#pragma once
#include <map>
#include "ChannelStatus.hpp"
#include "../../DataStruct/ChannelData.hpp"

namespace CornStarch
{;

// チャンネル一覧を保持する
class CChannelHolder
{
private:
    std::map<wxString, CChannelStatus*> m_channels; // チャンネル一覧
    bool m_isLoaded;
public:
    CChannelHolder(void);
    ~CChannelHolder(void);

    // 初期化を行う
    void init(void);

    // チャンネル一覧をセットする
    void setChannels(const std::vector<CChannelData*>& channels);

    // チャンネル一覧を取得する
    std::vector<CChannelStatus*> getChannels(void) const;

    // 既にチャンネル一覧を取得したか
    bool hasReceivedChannel(void) const;

    // チャンネルを追加する
    void setChannel(const wxString& channelName,const wxString& topic);

    // チャンネルを削除する
    void popChannel(const wxString& channel);

    // チャンネル名からtopicを取得する
    wxString getTopic(const wxString& channel);

    // チャンネル一覧のメモリ領域を削除する
    void deleteChannels(void);

    // 一番頭のチャンネルを取得する
    wxString getFirstChannel(void);

    /////////////////////////////////////////////////////////////



    // チャンネルのメッセージ一覧を取得する
    std::vector<CServiceLog*> getLogs(const wxString& channel);

    // チャンネルのメンバー一覧を取得する
    std::vector<CMemberData*> getMembers(const wxString& channel);

    // チャンネルのメッセージを追加する
    void pushLog(const wxString& channel, CServiceLog* message);

    // チャンネルのメンバーを追加する
    void pushMember(const wxString& channel, const CMemberData& member);

    // チャンネルのメッセージ一覧をセットする
    void setLogs(const wxString& channel, const std::vector<CServiceLog*>& messages);

    // チャンネルのメンバー一覧をセットする
    void setMembers(const wxString& channel, const std::vector<CMemberData*>& members);

    // メンバーを消す
    void popMember(const wxString& channel, const wxString& userName);

    // メンバー情報を更新する
    void updateMember(const wxString& userName,const wxString& nick);

    // メッセージIDを更新する
    void onUpdateMessageId(const CMessageLog* message);
    
    // チャンネルのメッセージ情報を収集したか
    bool hasReceivedMessage(const wxString& channel);

    // チャンネルのメッセージ情報を収集したか
    bool hasReceivedMember(const wxString& channel);

    // 同じメッセージ内容のものがあるか
    bool hasSameMessage(const CMessageLog* message);

    // チャンネルを取得する。
    CChannelStatus* getChannel(const wxString& channel) ;

};

}
