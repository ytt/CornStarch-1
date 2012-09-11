#pragma once
#include "View/MainView.hpp"
#include "Service/Message/MessageHolder.hpp"
#include "Serializer/ServiceSerializer.hpp"
#include "Service/ServiceHolder.hpp"
#include "Service/InputManager.hpp"
#include "Service/ClientCommandInvoker.hpp"
#include "Service/Event/StreamEvent.hpp"

namespace CornStarch
{
;

// ビューコントローラとなるウィンドウクラス
class CMainWindow: public wxFrame, public CClientCommandInvoker
{
private:

    CMainView* m_view; // ビューの挙動を管理
    CMessageHolder* m_logHolder; // チャットのログを保持
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
    void showChangeTopicDialog(int serviceId, wxString channelName);

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

    // 保存
    void onSave(wxCommandEvent& event);
    // 読み込み
    void onLoad(wxCommandEvent& event);
    // 拡大
    void onZoom(wxCommandEvent& event);
    // 縮小
    void onShrink(wxCommandEvent& event);
    // コピー
    void onCopy(wxCommandEvent& event);
    // 全てを選択
    void onSelectAll(wxCommandEvent& event);
    // 検索
    void onFind(wxCommandEvent& event);

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

    // 未読移動
    void onMoveToUnread(wxCommandEvent& event);

    // タブの追加
    void onAddTab(wxCommandEvent& event);

    // タブの削除
    void onRemoveTab(wxCommandEvent& event);

    // 次のタブを選択
    void onSelectNextTab(wxCommandEvent& event);

    // 前のタブを選択
    void onSelectPreviousTab(wxCommandEvent& event);
private:
    // 画面系

    // 投稿ペインでEnterキーを押下
    void onEnter(wxCommandEvent& event);
    // 検索ダイアログでEnterキーを押下
    void onEnterFind(wxCommandEvent& event);
    //　キーを押された時。
    void onTextUpdated(wxCommandEvent& event);

    // メンバーがダブルクリック
    void onMemberDoubleClicked(wxCommandEvent& event);

    // チャンネル選択時
    void onChannelSelected(CChannelSelectEvent& event);

    // チャンネルを選択
    void selectChannel(int serviceId,wxString channelName);
    // チャンネルペインを右クリック時
    void onChannelRightClicked(CChannelSelectEvent& event);

    // テキストボックスの次がフォーカスされた時。
    void onFocusedNextTextBox(wxFocusEvent& event);

    // 入力テキストでTabを押されて次のコントロールにフォーカスが来た時
    void onFocusNextText(wxThreadEvent& event);

    // ポストペインでキーを押した時
    void onKeyDownOnPostPane(wxKeyEvent& event);

    // メッセージをダブルクリックされた時
    void onMessageControlDoubleClicked(CMessageControlDoubleClickedEvent& event);
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
    void onMsgStream(CStreamEvent<CChatMessage>& event);

    // チャンネル参加ストリーム受信時
    void onJoinStream(CStreamEvent<CJoinMessage>& event);

    // チャンネル離脱ストリーム受信時
    void onPartStream(CStreamEvent<CPartMessage>& event);

    // チャンネル更新ストリーム受信時
    void onChannelStream(CStreamEvent<CTopicMessage>& event);

    // ユーザ情報更新ストリーム受信時
    void onUserStream(CStreamEvent<CMemberMessage>& event);
    // チャンネル更新ストリーム受信時
    void onInvite(CStreamEvent<CInviteMessage>& event);

    // ユーザ情報更新ストリーム受信時
    void onKick(CStreamEvent<CKickMessage>& event);

};

}
