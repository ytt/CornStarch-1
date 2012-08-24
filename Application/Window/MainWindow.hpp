#pragma once
#include "View/MainView.hpp"
#include "Service/LogHolder/LogHolder.hpp"
#include "Serializer/ServiceSerializer.hpp"
#include "Serializer/ServiceSerializerWin.hpp"
#include "Service/ServiceHolder.hpp"
#include "Service/InputManager.hpp"
#include "Service/ClientCommandInvoker.hpp"
#include "Service/Event/StreamEvent.hpp"

namespace CornStarch
{
;

// ビューコントローラとなるウィンドウクラス
class CMainWindow: public wxFrame,public CClientCommandInvoker
{
private:

    CMainView* m_view; // ビューの挙動を管理
    CLogHolder* m_logHolder; // チャットのログを保持
    CInputManager* m_inputManager; // 入力補助
    // サービス一覧の保持
    CServiceHolder* m_serviceHolder;

    // wxWindowイベントを処理させたいクラスに利用するマクロ
DECLARE_EVENT_TABLE()

public:
    CMainWindow(void);
    ~CMainWindow(void);

    // 初期化を行う
    void init(void);
    // コマンドの実行
    bool invoke(const wxString& text);

    // 表示が終わった後によばれます。
    void onShowed();
private:
    // 新規サービスの作成
    void registerService();
    // 未読に移動
    void moveToUnread();
    // 画面操作に関するイベントハンドラを設定する
    void initHandle(void);

    // Modelがあれば画面を更新する
    void updateAllView(int serviceId, const wxString& channel);

    // メッセージ画面を更新する(Modelがある場合)
    void updateMessageView(int serviceId, const wxString& channel);

    // メンバー画面を更新する(Modelがある場合)
    void updateMemberView(int serviceId, const wxString& channel);

    // チャンネル画面とタイトルバーを更新する(Modelがある場合)
    void updateChannelView(int serviceId, const wxString& channel);

    // タイトルバーにタイトルを表示する
    void displayTitle(const wxString& channel, const wxString& topic,
            int serviceId);

    // すべての画面をクリアする。
    void clearAllView();

    // サービスを削除する。
    void deleteService(int serviceId);

    // チャンネル追加ダイアログを表示する
    void showAddChannleDialog(int serviceId);

    // トピック変更ダイアログを表示する
    void showChangeTopicDialog(int serviceId);

    // ニックネーム変更ダイアログを表示する。
    void showChangeNicknameDialog(int serviceId);
    // サービスを再読み込みする。
    void updateService(int serviceId);
    // サービスを切断する
    void disconnect(int serviceId);
private:
    // メニュー系

    // 終了
    void onQuit(wxCommandEvent& event);

    // 検索
    void onFind(wxCommandEvent& event);

    // 全てを選択
    void onSelectAll(wxCommandEvent& event);

    // 送信履歴
    void onSendHistory(wxCommandEvent& event);


    // 入力補助
    void onAutoComplete(wxCommandEvent& event);

    // 　サービス登録
    void onServiceRegister(wxCommandEvent& event);

    // サーバー削除
    void onDeleteService(wxCommandEvent& event);

    // チャンネルに参加メニュー
    void onJoin(wxCommandEvent& event);

    // チャンネルから離脱メニュー
    void onPart(wxCommandEvent& event);

    // 表示を更新
    void onUpdateDisplay(wxCommandEvent& event);

    // ニックネーム変更
    void onNickChange(wxCommandEvent& event);

    // トピック変更
    void onChangeTopic(wxCommandEvent& event);

    // トピック変更
    void onMoveToUnread(wxCommandEvent& event);
private:
    // 画面系

    // 投稿ペインでEnterキーを押下
    void onEnter(wxCommandEvent& event);

    //　キーを押された時。
    void onTextUpdated(wxCommandEvent& event);

    // メンバーがダブルクリック
    void onMemberDoubleClicked(wxCommandEvent& event);

    // チャンネル選択時
    void onChannelSelected(CChannelSelectEvent& event);

    // チャンネルペインを右クリック時
    void onChannelRightClicked(CChannelSelectEvent& event);

private:
    // 通信系

    // メッセージ投稿終了時
    void onFinishPostMessage(wxThreadEvent& event);

    // 認証情報の受信時
    void onGetAuth(CAuthEvent& event);

    // 切断情報の受信時
    void onDisconnect(CDisconnectEvent& event);

    // メッセージ一覧受信時
    void onGetMessages(CGetMessageEvent& event);

    // メンバー一覧受信時
    void onGetMembers(CGetMemberEvent& event);

    // チャンネル一覧受信時
    void onGetChannels(CGetChannelEvent& event);

    // チャンネル参加時
    void onJoinChannel(CJoinEvent& event);

    // チャンネル離脱時
    void onPartChannel(CPartEvent& event);

    // メンバー情報の受信時
    void onGetMemberInfo(CGetMemberInfoEvent& event);

    // メッセージストリーム受信時
    void onMsgStream(CStreamEvent<CMessageLog>& event);

    // チャンネル参加ストリーム受信時
    void onJoinStream(CStreamEvent<CJoinLog>& event);

    // チャンネル離脱ストリーム受信時
    void onPartStream(CStreamEvent<CPartLog>& event);

    // チャンネル更新ストリーム受信時
    void onChannelStream(CStreamEvent<CTopicLog>& event);

    // ユーザ情報更新ストリーム受信時
    void onUserStream(CStreamEvent<CMemberLog>& event);
    // チャンネル更新ストリーム受信時
    void onInvite(CStreamEvent<CInviteLog>& event);

    // ユーザ情報更新ストリーム受信時
    void onKick(CStreamEvent<CKickLog>& event);

};

}
