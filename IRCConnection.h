﻿/*
 * IRCConnection.h
 *
 *  Created on: 2012/07/13
 */

#ifndef IRCCONNECTION_H_
#define IRCCONNECTION_H_
#include "header.hpp"
#include "IConnection.hpp"
#include "IRCClient.h"
#include "ChannelData.hpp"

namespace CornStarch
{
namespace IRC
{
class CIRCConnection: public IConnection
{
	CIRCClient *m_client;
	wxEvtHandler* m_handler;
	int m_connectionId;
	vector<CChannelData*> m_channels;
public:
	CIRCConnection();
	virtual ~CIRCConnection(void);

	//override 初期化を行う
	void init(int connectionId, wxEvtHandler* handler);

	//override メッセージを投稿するタスク(別スレッド)を開始する
	void startPostMessageTask(const IUser* user, const wxString& message,
			const wxString& channel);

	//override チャンネルのメッセージを取得するタスク(別スレッド)を開始する
	void startGetMessageTask(const IUser* user, const wxString& channel);

	//override チャンネルのメンバーを取得するタスク(別スレッド)を開始する
	void startGetMemberTask(const IUser* user, const wxString& channel);

	//override ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
	void startGetChannelTask(const IUser* user);

	//override チャンネルから離脱するタスク(別スレッド)を開始する
	void startPartTask(const IUser* user, const wxString& channel);

	//override チャンネルに参加するタスク(別スレッド)を開始する
	void startJoinTask(const IUser* user, const wxString& channel);

	//override メンバーの情報を取得するタスク(別スレッド)を開始する
	void startGetMemberInfoTask(const IUser* user, const wxString& userName);

	//override ニックネームを変更するタスク(別スレッド)を開始する(未実装)
	void startNickChangeTask(const IUser* user, const wxString& nick)
	{
	}

	//override トピックを変更するタスク(別スレッド)を開始する(未実装)
	void startChangeTopicTask(const IUser* user, const wxString& topic)
	{
	}

	//override ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
	void startAuthTask(const IUser* user);

	//override ストリーム通信タスク(別スレッド)を開始
	void startStreamTask(const IUser* user);

	//override 認証用タスク(別スレッド)を削除する
	void deleteAuthTask(void);

private:

};
}
} /* namespace CornStarch */
#endif /* IRCCONNECTION_H_ */
