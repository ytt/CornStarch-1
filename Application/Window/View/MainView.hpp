#pragma once
#include "Menubar/MainMenuBar.hpp"
#include "Panel/MainPanel.hpp"
#include "MainNotifier.hpp"
#include "../Service/ChatServiceBase.hpp"
#include <map>

namespace CornStarch
{
;

// ビュー部分(メニューバー、画面、ダイアログ)を管理
class CMainView
{
private:
    CMainMenuBar* m_menuBar; // メニューバーを管理
    CMainPanel* m_panel; // 各ペインを管理
    CMainNotifier* m_notifier; // 通知を行う

public:
    CMainView(void);
    ~CMainView(void);

    // 初期化を行う
    void init(wxWindow* parent);

public:
    // 各ペインに関するメソッド

    // 投稿ペインのIDを取得する
    wxWindowID getPostPaneID(void) const;

    // チャンネルペインのIDを取得する
    wxWindowID getCnPaneID(void) const;

    // メンバーペインのIDを取得する
    wxWindowID getMemPaneID(void) const;

    // 指定したチャンネルを選択済み項目にする
    void setSelectedChannel(int serviceId,const wxString& channelName);

    // 投稿ペインにフォーカスを与える。
    void setFocusPostPane(void);

    // メッセージ一覧を表示する
    void displayMessages(const std::vector<CMessage*>& messages,
            const CNickTable& nickTable);

    // メッセージ一覧を表示する
    void addMessage(const CMessage* message);

    // 読み込んでないメッセージを通知する。
    void addUnreadMessage(const CChatMessage* message);

    // メンバー一覧を表示する
    void displayMembers(const std::vector<CMemberData*>& members);

    // チャンネル一覧を表示する
    void displayChannels(const std::map<int, CChatServiceBase*>& services);

    // メッセージ一覧をクリアする。
    void clearMessages(void);

    // メンバー一覧をクリアする
    void clearMembers(void);

    // チャンネル一覧をクリアする
    void clearChannels(void);

    // 投稿用ペインの文字を消す
    void clearPostPaneText(void);

    // ログ一覧にログを表示する
    void displayLogs(const std::vector<CMessage*>& logs,const CServiceHolder* services);

    // 一つ先のチャンネルを選択します。
    void selectNextChannel();

    // 一つ前のチャンネルを選択します。
    void selectPreviousChannel();

    // 投稿ペインに文字を設定する。
    void setTextPostPane(const wxString& value);

    // 投稿ペインに文字を取得する
    wxString getTextPostPane() const;
public:
    // メニューバーに関するメソッド

    // メニューバーを取得する
    CMainMenuBar* getMenuBar(void) const;

public:
    // ダイアログに関するメソッド

    // メッセージボックスを表示する
    void showMsgBox(const wxString& message);

public:
    // 通知に関するメソッド

    // メッセージを通知する
    void messageNotify(const wxString& title, const wxString& message);
};

}
