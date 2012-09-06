#include "DefineEventTable.hpp" // イベントテーブル
#include "MainWindow.hpp"
#include <wx/defs.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include "View/Dialog/ChangeTopicDialog.hpp"
#include "View/Dialog/AuthDialog.hpp"
#include "View/Dialog/NickChangeDialog.hpp"
#include "View/Dialog/ChannelDialog.hpp"
#include "View/Dialog/SelectionDialog.hpp"
#include "View/Dialog/FilterDialog.hpp"

using namespace std;

namespace CornStarch
{
;

//////////////////////////////////////////////////////////////////////

CMainWindow::CMainWindow(void) :
        m_view(NULL), m_logHolder(NULL)
{
}

CMainWindow::~CMainWindow(void)
{
    m_serviceHolder->save();

    delete m_inputManager;
    delete m_view;
    delete m_logHolder;
    delete m_serviceHolder;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainWindow::init(void)
{
    // viewの初期化
    m_view = new CMainView();
    m_view->init(this);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

    SetMenuBar(m_view->getMenuBar()); // メニューバー

    // ログ保持部の初期化
    m_logHolder = new CMessageHolder();
    m_inputManager = new CInputManager();
    m_serviceHolder = new CServiceHolder();
    m_serviceHolder->load(GetEventHandler());
    // イベントハンドラの初期化
    initHandle();

}
void CMainWindow::onShowed()
{
    if (m_serviceHolder->getServices().size() == 0){
        registerService();
    }
}
//////////////////////////////////////////////////////////////////////

// 画面操作に関するイベントハンドラを設定する
void CMainWindow::initHandle(void)
{
    // エンターキー押下時
    this->Connect(m_view->getPostPaneID(), wxEVT_COMMAND_TEXT_ENTER,
            wxCommandEventHandler(CMainWindow::onEnter));

    // テキスト入力時
    this->Connect(m_view->getPostPaneID(), wxEVT_COMMAND_TEXT_UPDATED,
            wxCommandEventHandler(CMainWindow::onTextUpdated));

    // メンバーがダブルクリックされたとき
    this->Connect(m_view->getMemPaneID(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,
            wxCommandEventHandler(CMainWindow::onMemberDoubleClicked));

}
// 検索
void CMainWindow::onFind(wxCommandEvent& event)
{

}
// コピー
void CMainWindow::onCopy(wxCommandEvent& event)
{
    wxWindow* focus = wxWindow::FindFocus();
    wxRichTextCtrl* paneMsg = dynamic_cast<wxRichTextCtrl*>(focus);
    if (paneMsg != NULL){
        paneMsg->Copy();
    }
}
// 全てを選択
void CMainWindow::onSelectAll(wxCommandEvent& event)
{
    wxWindow* focus = wxWindow::FindFocus();
    wxRichTextCtrl* paneMsg = dynamic_cast<wxRichTextCtrl*>(focus);
    if (paneMsg != NULL){
        paneMsg->SelectAll();
    }
}
// ポストペインの文字が変更された
void CMainWindow::onTextUpdated(wxCommandEvent& event)
{
    if (m_inputManager->isChangingText() == false){
        m_inputManager->setCurrentInput(m_view->getTextPostPane());
        m_inputManager->resetIndex();
    }
    m_inputManager->setChangingText(false);
}
// Modelがあれば画面を更新する
void CMainWindow::updateAllView(int connectionId, const wxString& channel)
{
    updateMessageView(connectionId, channel);
    updateMemberView(connectionId, channel);
    updateChannelView(connectionId, channel);
}

// メッセージ画面を更新する(Modelがある場合)
void CMainWindow::updateMessageView(int connectionId, const wxString& channel)
{
    if (connectionId == m_serviceHolder->getCurrentServiceId()){
        CChatServiceBase* service = m_serviceHolder->getService(connectionId);
        service->onUpdateMessageView(channel);

        // メッセージを表示
        m_view->displayMessages(service->getLogs(channel),
                service->getNickTable(), channel, service->getConfiguration());

        // 未読リセット
        CChannelStatus* channelStatus = service->getChannel(channel);
        if (channelStatus != NULL){
            channelStatus->clearUnreadCount();
        }
    }
}

// メンバー画面を更新する(Modelがある場合)
void CMainWindow::updateMemberView(int connectionId, const wxString& channel)
{
    if (connectionId == m_serviceHolder->getCurrentServiceId()){
        CChatServiceBase* service = m_serviceHolder->getService(connectionId);
        service->onUpdateMemberView(channel);

        // メンバーを表示
        m_view->displayMembers(service->getMembers(channel));
    }
}

// チャンネル画面とタイトルバーを更新する(Modelがある場合)
void CMainWindow::updateChannelView(int connectionId, const wxString& channel)
{
    CChatServiceBase* service = m_serviceHolder->getService(connectionId);
    service->onUpdateChannelView();

    // チャンネルを表示
    displayTitle(channel, service->getTopic(channel), connectionId);
    m_view->displayChannels(m_serviceHolder->getServices());
    if (connectionId == m_serviceHolder->getCurrentServiceId()){
        m_view->setSelectedChannel(connectionId, service->getCurrentChannel());
    }
}

// タイトルバーにタイトルを表示する
void CMainWindow::displayTitle(const wxString& channel, const wxString& topic,
        int serviceId)
{
    // 現在見ているサーバではなかったら
    if (serviceId != m_serviceHolder->getCurrentServiceId()){
        return;
    }

    CChatServiceBase* service = m_serviceHolder->getService(serviceId);

    // チャンネル名が空の時、サーバ名を表示
    if (channel == ""){
        SetTitle(
                service->getName() + "(" + service->getUser()->getNickName()
                        + ")");
        return;
    }

    // 改行を消してタイトルを表示
    wxString tpc = topic;
    tpc.Replace("\r\n", " ");
    tpc.Replace("\n", " ");
    this->SetTitle(
            service->getName() + "(" + service->getUser()->getNickName() + ")【"
                    + channel + "】" + tpc);
}

// すべての画面をクリアする。
void CMainWindow::clearAllView()
{
    m_view->clearChannels();
    m_view->clearMembers();
    m_view->clearMessages();
}

//////////////////////////////////////////////////////////////////////

// 終了
void CMainWindow::onQuit(wxCommandEvent& event)
{
    Close(true);
}

// サービス登録
void CMainWindow::onServiceRegister(wxCommandEvent& event)
{
    registerService();
}
void CMainWindow::registerService()
{
    CAuthDialog authDlg;
    authDlg.init(this, "サーバー登録");
    // 認証ダイアログを表示
    if (authDlg.ShowModal() == wxID_OK){
        // ここでサーバの追加を行う
        CChatServiceBase* contents = authDlg.getNewService();
        if (contents != NULL){
            m_serviceHolder->addNewService(contents, GetEventHandler());
            // 表示の更新
            updateAllView(contents->getId(), contents->getCurrentChannel());
        }
    }
}
bool CMainWindow::invoke(const wxString& text)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());

    if (text.StartsWith(CClientCommandInvoker::CONNECT)){
        service->reconnect();
        return true;
    } else if (text.StartsWith(CClientCommandInvoker::DELETE)){
        deleteService(service->getId());
        return true;
    } else if (text.StartsWith(CClientCommandInvoker::DISCONNECT)){
        disconnect(service->getId());
        return true;
    } else if (text.StartsWith(CClientCommandInvoker::JUMP)){
        this->moveToUnread();
        return true;
    } else if (text.StartsWith(CClientCommandInvoker::NEW)){
        registerService();
        return true;
    } else if (text.StartsWith(CClientCommandInvoker::QUIT)){
        Close(true);
        return true;
    }

    return service->getCommandInvoker()->invoke(text);
    //return false;
}
// チャンネルに参加メニュー
void CMainWindow::onJoin(wxCommandEvent& event)
{
    showAddChannleDialog(m_serviceHolder->getCurrentServiceId());
}

// サーバー削除
void CMainWindow::onDeleteService(wxCommandEvent& event)
{
    deleteService(m_serviceHolder->getCurrentServiceId());
}

// チャンネルから離脱メニュー
void CMainWindow::onPart(wxCommandEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    if (contents == NULL){
        return;
    }

    // 未ログインの時
    if (!contents->IsConnected()){
        return;
    }

    // チャンネル名のベクターを作成
    vector<wxString> channelNames;
    vector<CChannelStatus*> channels = contents->getChannels();
    vector<CChannelStatus*>::iterator it = channels.begin();
    while (it != channels.end()){
        channelNames.push_back((*it)->getChannelName());
        it++;
    }

    // ダイアログを表示
    CSelectionDialog dialog;
    dialog.init(this, "チャンネル名を指定", "サーバー名：", contents->getName(), "チャンネル名：",
            channelNames);
    if (dialog.ShowModal() == wxID_OK){
        contents->partChannel(dialog.getValue());
    }
}

// 表示を更新
void CMainWindow::onUpdateDisplay(wxCommandEvent& event)
{
    updateService(m_serviceHolder->getCurrentServiceId());
}

void CMainWindow::updateService(int serviceId)
{
    CChatServiceBase* service = m_serviceHolder->getService(serviceId);
    if (service != NULL){
        //　再接続
        service->reconnect();
        service->clearChannels();
        service->clearNickTable();

        // 表示を更新
        if (serviceId == m_serviceHolder->getCurrentServiceId()){
            updateAllView(m_serviceHolder->getCurrentServiceId(),
                    service->getCurrentChannel());
        } else{
            m_view->displayChannels(m_serviceHolder->getServices());
        }
    }
}
// 入力テキストでTabを押されて次のコントロールにフォーカスが来た時
void CMainWindow::onFocusNextText(wxThreadEvent& event)
{
    CChatServiceBase * service = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    m_view->setTextPostPane(
            m_inputManager->getAutoCompletionText(m_view->getTextPostPane(),
                    service, getCommandList()));
}
// タブの追加
void CMainWindow::onAddTab(wxCommandEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    if (contents == NULL || contents->getCurrentChannel() == ""){
        return;
    }
    CChannelStatus* channel = contents->getChannel(
            contents->getCurrentChannel());

    vector<wxString> userNames;
    vector<CMemberData*> members = channel->getMembers();
    vector<CMemberData*>::iterator it = members.begin();
    while (it != members.end()){
        userNames.push_back((*it)->m_nick);
        it++;
    }

    // ダイアログを表示
    CFilterDialog dialog;
    dialog.init(this, contents->getCurrentChannel(), userNames);
    if (dialog.ShowModal() == wxID_OK){
        IFilter* filter = dialog.getFilter();
        if (filter != NULL){
            contents->getConfiguration()->addFilter(
                    contents->getCurrentChannel(), filter);
            updateMessageView(m_serviceHolder->getCurrentServiceId(),
                    contents->getCurrentChannel());
        }
    }
}
// 次のタブを選択
void CMainWindow::onSelectNextTab(wxCommandEvent& event)
{
    m_view->selectNextTab();
}

// 前のタブを選択
void CMainWindow::onSelectPreviousTab(wxCommandEvent& event)
{
    m_view->selectPreviousTab();
}
// タブの削除
void CMainWindow::onRemoveTab(wxCommandEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    if (contents == NULL || contents->getCurrentChannel() == ""){
        return;
    }
    vector<IFilter*>* filters = contents->getConfiguration()->getFilters(
            contents->getCurrentChannel());

    // フィルター名の取得
    vector<wxString> filterNames;
    vector<IFilter*>::iterator it = filters->begin();
    while (it != filters->end()){
        filterNames.push_back((*it)->getName());
        it++;
    }

    // ダイアログを表示
    CSelectionDialog dialog;
    dialog.init(this, "タブ名を指定", "チャンネル名：", contents->getCurrentChannel(),
            "タブ名：", filterNames);
    if (dialog.ShowModal() == wxID_OK){
        contents->getConfiguration()->removeFilter(
                contents->getCurrentChannel(), dialog.getValue());
        updateMessageView(m_serviceHolder->getCurrentServiceId(),
                contents->getCurrentChannel());
    }
}
// 次の未読チャンネルを選択。
void CMainWindow::onMoveToUnread(wxCommandEvent& event)
{
    moveToUnread();
}

void CMainWindow::moveToUnread()
{
    map<int, CChatServiceBase*> services = m_serviceHolder->getServices();
    map<int, CChatServiceBase*>::iterator it = services.begin();
    bool isFoundCurrentNode = false;
    int serviceId = -1;
    wxString channelName = "";

    while (it != services.end()){
        CChatServiceBase* service = (*it).second;
        vector<CChannelStatus*> channels = service->getChannels();
        vector<CChannelStatus*>::iterator channel = channels.begin();
        while (channel != channels.end()){
            if ((*channel)->getUnreadCount() != 0 && serviceId == 0){
                // 未読ノードを初めて見つける
                serviceId = service->getId();
                channelName = (*channel)->getChannelName();
            }

            if ((*channel)->getUnreadCount() != 0 && isFoundCurrentNode){
                // 現在のノード以降に未読ノードを見つける
                m_view->setSelectedChannel(service->getId(),
                        (*channel)->getChannelName());
                return;
            }
            // 現在選択しているノードにたどり着く。
            if (service->getId() == m_serviceHolder->getCurrentServiceId()
                    && (*channel)->getChannelName()
                            == service->getCurrentChannel()){
                isFoundCurrentNode = true;
            }
            channel++;
        }
        it++;
    }
    // 現在のノード以降で見つからなかったら、はじめに見つかった未読ノードを選択。
    if (serviceId != -1){
        m_view->setSelectedChannel(serviceId, channelName);
    }
}

// サービスを切断する
void CMainWindow::disconnect(int serviceId)
{
    CChatServiceBase* service = m_serviceHolder->getService(serviceId);
    if (service != NULL){
        service->disconnect();
        m_view->displayChannels(m_serviceHolder->getServices());
    }
}
// ニックネーム変更
void CMainWindow::onNickChange(wxCommandEvent& event)
{
    showChangeNicknameDialog(m_serviceHolder->getCurrentServiceId());
}

// トピック変更
void CMainWindow::onChangeTopic(wxCommandEvent& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    if (service != NULL){
        showChangeTopicDialog(m_serviceHolder->getCurrentServiceId(),
                service->getCurrentChannel());
    }
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインでEnterキーを押下
void CMainWindow::onEnter(wxCommandEvent& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());

    wxString body = event.GetString();
    if (service == NULL || body == ""){
        return;
    }
    bool isCommand = invoke(body);
    if (isCommand){
        // 表示の更新
        m_view->clearPostPaneText();
        return;
    }
    if (service->getCurrentChannel() == "" || service->IsConnected() == false){
        return;
    }
    // 送信履歴を追加
    m_inputManager->addHistory(body);
    // コンテンツの更新
    CChatMessage* log = service->generateMessage(body);
    service->postMessage(log);
    m_view->addMessage(log);

    // 表示の更新
    m_view->clearPostPaneText();

}

// メンバーがダブルクリック
void CMainWindow::onMemberDoubleClicked(wxCommandEvent& event)
{
//    CChatServiceBase* contents = m_serviceHolder->getService(
//            m_serviceHolder->getCurrentServiceId());

    wxString content = wxString::Format(wxT("%s %s%s "
    ), m_view->getTextPostPane(), event.GetString(), ":");
    m_view->setTextPostPane(content);
    //wxString name = contents->getMemberRealName(event.GetString());
    //wxMessageBox("名前：" + name, event.GetString() + "のユーザ情報");
}

// チャンネル選択時
void CMainWindow::onChannelSelected(CChannelSelectEvent& event)
{
    // 選択したコンテンツを取得
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getServerId());
    // 選択したのがサーバ名だったとき
    if (event.isServerSelected()){
        m_serviceHolder->setCurrentServiceId(event.getServerId());
        m_view->clearMessages();
        m_view->clearMembers();
        displayTitle("", "", m_serviceHolder->getCurrentServiceId());

        service->selectChannel("");
        return;
    }

    // サーバーIDとチャンネル名を取得
    wxString channel = event.getChannelName();
    m_serviceHolder->setCurrentServiceId(event.getServerId());
    // コンテンツの更新
    service->selectChannel(channel);

    // 画面表示を更新
    displayTitle(channel, service->getTopic(channel), event.getServerId());
    updateMessageView(m_serviceHolder->getCurrentServiceId(),
            service->getCurrentChannel());
    updateMemberView(m_serviceHolder->getCurrentServiceId(),
            service->getCurrentChannel());

    // 投稿ペインにフォーカス
    m_view->setFocusPostPane();
}

// 保存
void CMainWindow::onSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Export"), "", "",
            "CornStarch Config (*.csconf)|*.csconf",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL){
        return; // the user changed idea...
    }

    m_serviceHolder->exportService(saveFileDialog.GetPath());
}
// 読み込み
void CMainWindow::onLoad(wxCommandEvent& event)
{
    m_serviceHolder->importService();
}

// 拡大
void CMainWindow::onZoom(wxCommandEvent& event)
{
    map<int, CChatServiceBase*> services = m_serviceHolder->getServices();
    map<int, CChatServiceBase*>::iterator it = services.begin();
    while (it != services.end()){
        CServiceConfiguration* configuration = (*it).second->getConfiguration();
        configuration->setFontSize(configuration->getFontSize() + 2);
        it++;
    }

    CChatServiceBase* service = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    if (service != NULL){
        updateMessageView(m_serviceHolder->getCurrentServiceId(),
                service->getCurrentChannel());
    }
}
// 縮小
void CMainWindow::onShrink(wxCommandEvent& event)
{
    map<int, CChatServiceBase*> services = m_serviceHolder->getServices();
    map<int, CChatServiceBase*>::iterator it = services.begin();
    while (it != services.end()){
        CServiceConfiguration* configuration = (*it).second->getConfiguration();
        configuration->setFontSize(configuration->getFontSize() - 2);
        it++;
    }

    CChatServiceBase* service = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());
    if (service != NULL){
        updateMessageView(m_serviceHolder->getCurrentServiceId(),
                service->getCurrentChannel());
    }
}

// ポストペインでキーを押した時
void CMainWindow::onKeyDownOnPostPane(wxKeyEvent& event)
{
    if (event.GetModifiers() == wxMOD_ALT){
        if (event.GetKeyCode() == WXK_SPACE){
            moveToUnread();
        }
    }
    if (event.GetKeyCode() == WXK_UP){
        if (event.GetModifiers() == wxMOD_ALT | wxMOD_CMD){
            m_view->selectPreviousChannel();
        } else{
            m_inputManager->setChangingText(true);
            m_view->setTextPostPane(m_inputManager->getHistory());
        }
    }
    if (event.GetKeyCode() == WXK_DOWN){
        if (event.GetModifiers() == wxMOD_ALT | wxMOD_CMD){
            m_view->selectNextChannel();
        } else{
            m_inputManager->setChangingText(true);
            m_view->setTextPostPane(m_inputManager->getHistoryBefore());
        }
    }
}
// チャンネルペインを右クリック時
void CMainWindow::onChannelRightClicked(CChannelSelectEvent& event)
{
    enum
    {
        Id_DeleteServer = 1, Id_AddChannel = 2, Id_DeleteChannel = 3,
        Id_ChangeTopic = 4, Id_ChangeNickname = 5, Id_Refresh = 6,
        Id_Disconnect = 7
    };

    int serviceId = event.getServerId();
    CChatServiceBase* service = m_serviceHolder->getService(serviceId);

    wxMenu menu;
    if (event.isServerSelected()){
        menu.Append(Id_DeleteServer, "サーバの削除");
        menu.Append(Id_Refresh, "サーバの再読み込み");
        if (service->IsConnected()){
            menu.Append(Id_Disconnect, "サーバの切断");
        }
        if (service->IsConnected()){
            menu.AppendSeparator();
        }
    }
    if (service->IsConnected()){
        menu.Append(Id_AddChannel, "チャンネルの追加");
        if (event.isServerSelected() == false){
            menu.Append(Id_DeleteChannel, "チャンネルの削除");
            menu.Append(Id_ChangeTopic, "トピックの変更");
        }
        menu.Append(Id_ChangeNickname, "ニックネームの変更");
    }

    wxString channel = event.getChannelName();
    switch (this->GetPopupMenuSelectionFromUser(menu)) {
    case Id_DeleteServer:
        deleteService(serviceId);
        break;
    case Id_AddChannel:
        showAddChannleDialog(serviceId);
        break;
    case Id_DeleteChannel:
        m_serviceHolder->deleteChannel(serviceId, channel);
        break;
    case Id_ChangeTopic:
        showChangeTopicDialog(serviceId, channel);
        break;
    case Id_ChangeNickname:
        showChangeNicknameDialog(serviceId);
        break;
    case Id_Refresh:
        updateService(serviceId);
        break;
    case Id_Disconnect:
        disconnect(serviceId);
        break;
    }
}

//////////////////////////////////////////////////////////////////////

// メッセージ投稿終了時
void CMainWindow::onFinishPostMessage(wxThreadEvent& event)
{
}

// 認証情報の受信時
void CMainWindow::onGetAuth(CAuthEvent& event)
{
    // サービスIDが不明な場合
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());
    if (service == NULL){
        return;
    }

    // 認証に失敗
    if (!event.isAuthSucceeded()){

        wxMessageBox("接続に失敗しました");

        // サービスの削除
        m_serviceHolder->deleteService(event.getConnectionId());

        // 表示の更新
        m_view->displayChannels(m_serviceHolder->getServices());

    } else{
        // コンテンツの更新
        service->onAuthSucceeed();
        service->setConnected(true);

        // 表示の更新
        updateAllView(event.getConnectionId(), service->getCurrentChannel());
    }

}
//
// 切断情報の受信時
void CMainWindow::onDisconnect(CDisconnectEvent& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());
    if (service != NULL){
        disconnect(event.getConnectionId());
        wxMessageBox(
                wxString::Format(wxT("サーバー[%s(%s)]切断されました。再接続を行う際は更新してください。"),
                        service->getName(), service->getHost()));
    }
}
// メッセージ一覧受信時
void CMainWindow::onGetMessages(CGetMessageEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            event.getConnectionId());
    if (contents != NULL){
        // メッセージを追加
        contents->onGetMessages(event.getChannel(), event.getMessages());

        // 表示の更新
        updateMessageView(event.getConnectionId(),
                contents->getCurrentChannel());
    }
}

// メンバー一覧受信時
void CMainWindow::onGetMembers(CGetMemberEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            event.getConnectionId());
    if (contents != NULL){
        // メンバーの追加
        contents->onGetMembers(event.getChannel(), event.getMembers());
        if (m_serviceHolder->getCurrentServiceId() == event.getConnectionId()
                && contents->getCurrentChannel() == event.getChannel()){
            // 表示の更新
            updateMemberView(event.getConnectionId(),
                    contents->getCurrentChannel());
        }
    }
}

// チャンネル一覧受信時
void CMainWindow::onGetChannels(CGetChannelEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            event.getConnectionId());
    if (contents != NULL){
        // チャンネルの追加
        vector<CChannelData*> channels = event.getChannels();
        contents->onGetChannels(channels);
        vector<CChannelData*>::iterator it = channels.begin();
        while (it != channels.end()){
            contents->getConfiguration()->addDefaultFilter((*it)->m_name);
            it++;
        }
        // 表示の更新
        updateChannelView(event.getConnectionId(),
                contents->getCurrentChannel());
        updateMemberView(event.getConnectionId(),
                contents->getCurrentChannel());
        updateMessageView(event.getConnectionId(),
                contents->getCurrentChannel());
    }
}

// チャンネル参加時
void CMainWindow::onJoinChannel(CJoinEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            event.getConnectionId());
    contents->onJoinChannel(event.GetString());

}

// チャンネル離脱時
void CMainWindow::onPartChannel(CPartEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            event.getConnectionId());
    contents->onPartChannel(event.GetString());

    // 表示の更新
    updateAllView(event.getConnectionId(), contents->getCurrentChannel());
}

// メンバー情報の受信時
void CMainWindow::onGetMemberInfo(CGetMemberInfoEvent& event)
{
    CChatServiceBase* contents = m_serviceHolder->getService(
            event.getConnectionId());

    // データ更新
    CMemberData data = event.getMember();
    contents->onGetMemberStatus(data);

    // 表示を更新
    updateMemberView(event.getConnectionId(), contents->getCurrentChannel());
    updateMessageView(event.getConnectionId(), contents->getCurrentChannel());
    m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder);
}

// メッセージストリーム受信時
void CMainWindow::onMsgStream(CStreamEvent<CChatMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());
    CChatMessage* message = event.getServiceLog();
    wxString nickName = service->getNickTable().getNickname(
            message->getUserName());
    message->setNick(nickName);

    bool isMyPost = service->isPostedThisClient(message);
    if (!isMyPost){
        if (event.getConnectionId() == m_serviceHolder->getCurrentServiceId()
                && service->getCurrentChannel() == message->getChannelName()){
            // メッセージを表示
            message->setReaded(true);
            m_view->addMessage(event.getServiceLog());

        } else{
            // 未読追加。
            CChannelStatus* channelStatus = service->getChannel(
                    message->getChannelName());
            if (channelStatus != NULL){
                channelStatus->addUnreadCount();
                message->setReaded(false);
                m_view->addUnreadMessage(message);
            }
        }
        m_logHolder->pushLog(event.getServiceLog());
    }
    // 通知があったとき && 自分以外の人から
    if (service->isUserCalled(message->getBody()) && !isMyPost){
        m_view->messageNotify("通知", "呼ばれました");
    }
    service->onGetMessageStream(message);
    // メッセージをログ一覧に表示
    m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン
}

// チャンネル参加ストリーム受信時
void CMainWindow::onJoinStream(CStreamEvent<CJoinMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());

    // 処理待ちに追加
    CJoinMessage* log = event.getServiceLog();
    service->onGetJoinStream(log->getChannelName(), log->getUserName());

    m_logHolder->pushLog(event.getServiceLog());
    service->addLog(event.getServiceLog());

    // 表示の更新
    m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン
    if (log->getChannelName() == service->getCurrentChannel()
            && m_serviceHolder->getCurrentServiceId()
                    == event.getConnectionId()){

        m_view->addMessage(event.getServiceLog());
        updateMemberView(event.getConnectionId(), log->getChannelName());
    }
}

// チャンネル離脱ストリーム受信時
void CMainWindow::onPartStream(CStreamEvent<CPartMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());
    if (service != NULL){

        CPartMessage* partLog = event.getServiceLog();
        wxString name = partLog->getUserName();
        wxString channel = partLog->getChannelName();

        // データ更新
        service->onGetPartStream(channel, name);
        service->addLog(event.getServiceLog());

        m_logHolder->pushLog(event.getServiceLog());

        // 表示の更新
        m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン
        if ((channel == service->getCurrentChannel() || channel == "")
                && m_serviceHolder->getCurrentServiceId()
                        == event.getConnectionId()){

            m_view->addMessage(event.getServiceLog());
            updateMemberView(event.getConnectionId(),
                    service->getCurrentChannel());
        }
    }
}

// チャンネル更新ストリーム受信時
void CMainWindow::onChannelStream(CStreamEvent<CTopicMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());

    // データ更新
    CTopicMessage* log = event.getServiceLog();
    wxString channelName = log->getChannelName();
    wxString topic = log->getTopic();
    service->onGetChannelStream(channelName, topic);
    service->addLog(event.getServiceLog());

    m_logHolder->pushLog(event.getServiceLog());

    // 表示の更新
    m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン

    // 現在のチャンネルならばタイトルを更新
    if (event.getServiceLog()->getChannelName() == service->getCurrentChannel()
            && m_serviceHolder->getCurrentServiceId()
                    == event.getConnectionId()){

        m_view->addMessage(event.getServiceLog());
        displayTitle(channelName, topic, event.getConnectionId());
    }
}

// ユーザ情報更新ストリーム受信時
void CMainWindow::onUserStream(CStreamEvent<CMemberMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());

    // データ更新
    CMemberMessage* log = event.getServiceLog();
    service->onGetUserStream(log->getUserName(), log->getNickName());
    m_logHolder->pushLog(event.getServiceLog());
    service->addLog(event.getServiceLog());

    // 表示の更新
    wxString ch = service->getCurrentChannel();
    if (m_serviceHolder->getCurrentServiceId() == event.getConnectionId()){

        m_view->addMessage(event.getServiceLog());
        displayTitle(ch, service->getTopic(ch), event.getConnectionId());
        updateMemberView(event.getConnectionId(), service->getCurrentChannel()); // メンバーペイン
        updateMessageView(event.getConnectionId(),
                service->getCurrentChannel()); // メッセージペイン
    }
    m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン
}
// 招待ストリーム受信時
void CMainWindow::onInvite(CStreamEvent<CInviteMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());
    if (service != NULL){
        CInviteMessage* log = event.getServiceLog();
        m_logHolder->pushLog(event.getServiceLog());
        // 表示の更新
        m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン

        wxMessageDialog dialog(this,
                wxString::Format(wxT("%s-チャンネル[%s]に招待されました。参加しますか？"),
                        service->getName(), log->getChannelName()), "確認",
                wxOK | wxCANCEL);
        if (dialog.ShowModal() == wxID_OK){
            service->joinChannel(log->getChannelName());
        }
    }
}

// キックストリーム受信時
void CMainWindow::onKick(CStreamEvent<CKickMessage>& event)
{
    CChatServiceBase* service = m_serviceHolder->getService(
            event.getConnectionId());
    if (service != NULL){
        m_logHolder->pushLog(event.getServiceLog());
        CKickMessage* log = event.getServiceLog();

        if (log->getTarget() == service->getUser()->getUserName()){
            wxMessageDialog dialog(this,
                    wxString::Format(wxT("%s-チャンネル[%s]からキックされました。"),
                            service->getName(), log->getChannelName()), "確認",
                    wxOK);
            if (dialog.ShowModal() == wxID_OK){
                service->partChannel(log->getChannelName());
            }
        } else{

            if (log->getChannelName() == service->getCurrentChannel()
                    && m_serviceHolder->getCurrentServiceId()
                            == event.getConnectionId()){
                m_view->addMessage(event.getServiceLog());
            }
            service->onGetPartStream(log->getChannelName(), log->getTarget());
            service->addLog(event.getServiceLog());
            updateMemberView(event.getConnectionId(), log->getChannelName());
            // 表示の更新
            m_view->displayLogs(m_logHolder->getLogs(), m_serviceHolder); // ログペイン
        }
    }
}

// サービスを削除する。
void CMainWindow::deleteService(int serviceId)
{
    CChatServiceBase* service = m_serviceHolder->getService(serviceId);
    if (service != NULL){
        wxMessageDialog dialog(this,
                wxString::Format(wxT("サーバー[%s(%s)]の削除をしてもよろしいですか？"),
                        service->getName(), service->getHost()), "確認",
                wxOK | wxCANCEL);

        if (dialog.ShowModal() == wxID_OK){
            m_serviceHolder->deleteService(serviceId);

            // 画面表示の更新
            clearAllView();
            m_view->displayChannels(m_serviceHolder->getServices());
        }
    }
}

// チャンネル追加ダイアログを表示する
void CMainWindow::showAddChannleDialog(int serviceId)
{
    CChatServiceBase* contents = m_serviceHolder->getService(serviceId);
    if (contents == NULL){
        return;
    }
    // 未ログインの時
    if (!contents->IsConnected()){
        return;
    }

    // ダイアログを表示
    CChannelDialog dialog;
    dialog.init(this, "チャンネル名を指定", contents->getName());
    if (dialog.ShowModal() == wxID_OK){
        contents->joinChannel(dialog.getChannelName());
    }
}

// トピック変更ダイアログを表示する
void CMainWindow::showChangeTopicDialog(int serviceId, wxString channelName)
{
    // 未ログインの時
    CChatServiceBase* contents = m_serviceHolder->getService(
            m_serviceHolder->getCurrentServiceId());

    if (contents == NULL){
        return;
    }
    if (!contents->IsConnected()){
        return;
    }
    if (channelName == ""){
        return;
    }
    CChannelStatus* channel = contents->getChannel(channelName);

    // トピック変更ダイアログを表示
    CChangeTopicDialog topicDlg;
    topicDlg.init(this, "トピックを指定", channelName, channel->getTopic());
    if (topicDlg.ShowModal() == wxID_OK){
        contents->onChangeTopic(topicDlg.getTopic());
    }
}

// ニックネーム変更ダイアログを表示する。
void CMainWindow::showChangeNicknameDialog(int serviceId)
{ // 未ログインの時
    CChatServiceBase* contents = m_serviceHolder->getService(serviceId);
    if (contents == NULL){
        return;
    }
    if (!contents->IsConnected()){
        return;
    }
    // ニックネーム変更ダイアログを表示
    CNickChangeDialog dialog;
    dialog.init(this, "ニックネームを指定", contents->getName(),
            contents->getUser()->getNickName());
    if (dialog.ShowModal() == wxID_OK){
        // データ更新
        contents->onNickChange(dialog.getNickName());
    }
}

}
