#include "MainView.hpp"

using namespace std;

namespace CornStarch
{
;

CMainView::CMainView(void) :
        m_menuBar(NULL), m_panel(NULL),m_notifier(NULL)
{
}

CMainView::~CMainView(void)
{
//    delete m_dialog;
    delete m_notifier;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainView::init(wxWindow* parent)
{
    // メニューバーを初期化
    if (m_menuBar == NULL){
        m_menuBar = new CMainMenuBar();
        m_menuBar->init();
    }

    // 画面パネルを初期化
    if (m_panel == NULL){
        m_panel = new CMainPanel();
        m_panel->init(parent);
    }

    // 通知クラスを初期化
    if (m_notifier == NULL){
        m_notifier = new CMainNotifier();
        m_notifier->init(parent);
    }
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインのIDを取得する
wxWindowID CMainView::getPostPaneID(void) const
{
    return m_panel->getPostPaneID();
}

// チャンネルペインのIDを取得する
wxWindowID CMainView::getCnPaneID(void) const
{
    return m_panel->getCnPaneID();
}

// 投稿ペインにフォーカスを与える。
void CMainView::setFocusPostPane(void)
{
    m_panel->setFocusPostPane();
}
// メンバーペインのIDを取得する
wxWindowID CMainView::getMemPaneID(void) const
{
    return m_panel->getMemPaneID();
}

// 指定したチャンネルを選択済み項目にする
void CMainView::setSelectedChannel(int serviceId,const wxString& channelName)
{
    m_panel->selectedChannel(serviceId,channelName);
}

// 一つ先のチャンネルを選択します。
void CMainView::selectNextChannel(){
    m_panel->selectNextChannel();
}

// 一つ前のチャンネルを選択します。
void CMainView::selectPreviousChannel(){
    m_panel->selectPreviousChannel();
}
// メッセージ一覧を表示する
void CMainView::displayMessages(const vector<CMessage*>& messages,
        const CNickTable& nickTable,const wxString& channelName,const CServiceConfiguration* configuration)
{
    m_panel->displayMessages(messages, nickTable,channelName,configuration);
}

void CMainView::addMessage(const CMessage* message)
{
    m_panel->addMessage(message);
}

void CMainView::addUnreadMessage(const CChatMessage* message)
{
    m_panel->addUnreadMessage(message);
}

// メンバー一覧を表示する
void CMainView::displayMembers(const vector<CMemberData*>& members)
{
    m_panel->displayMembers(members);
}

// チャンネル一覧を表示する
void CMainView::displayChannels(
        const std::map<int, CChatServiceBase*>& services)
{
    m_panel->displayChannels(services);
}

// 投稿用ペインの文字を消す
void CMainView::clearPostPaneText(void)
{
    m_panel->clearPostPaneText();
}

// ログ一覧にログを表示する
void CMainView::displayLogs(const std::vector<CMessage*>& logs,const CServiceHolder* services)
{
    m_panel->displayLogs(logs,services);
}

// メッセージ一覧をクリアします。
void CMainView::clearMessages(void)
{
    m_panel->clearMessages();
}

// メンバー一覧をクリアします。
void CMainView::clearMembers(void)
{
    m_panel->clearMembers();
}

// チャンネル一覧をクリアします。
void CMainView::clearChannels(void)
{
    m_panel->clearChannels();
}

//////////////////////////////////////////////////////////////////////

// メニューバーを取得する
CMainMenuBar* CMainView::getMenuBar(void) const
{
    return m_menuBar;
}

//////////////////////////////////////////////////////////////////////

// メッセージボックスを表示する
void CMainView::showMsgBox(const wxString& message)
{
    wxMessageBox(message);
}

// 投稿ペインに文字を設定する
void CMainView::setTextPostPane(const wxString& value)
{
    m_panel->setTextPostPane(value);
}
//　投稿ペインに文字を追加する
wxString CMainView::getTextPostPane() const
{
    return m_panel->getTextPostPane();
}
//////////////////////////////////////////////////////////////////////

// メッセージを通知する
void CMainView::messageNotify(const wxString& title, const wxString& message)
{
    m_notifier->messageNotify(title, message);
}

}
