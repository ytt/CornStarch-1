#include "MainPanel.hpp"

using namespace std;

namespace CornStarch
{
;

CMainPanel::CMainPanel(void) :
        m_memBox(NULL), m_channelPane(NULL), m_postPane(NULL), m_recordPane(
                NULL), m_msgTabTargetPane(NULL), m_messagePane(NULL)
{
}

CMainPanel::~CMainPanel(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainPanel::init(wxWindow* parent)
{
    // 分割ウィンドウを作成する
    CSplitPanel::init(parent);

    // メンバー表示ペインの初期化
    if (m_memBox == NULL){
        m_memBox = new CPaneMember();
        m_memBox->init(getMemPane());
    }

    // チャンネル表示ペインの初期化
    if (m_channelPane == NULL){
        m_channelPane = new CPaneCn();
        m_channelPane->init(getCnPane());
    }

    // メッセージ投稿ペインの初期化
    if (m_postPane == NULL){
        m_postPane = new CPanePost();
        m_postPane->init(getPostPane());
    }

    // メッセージ一覧表示ペインの初期化
    if (m_recordPane == NULL){
        m_recordPane = new CPaneRecord();
        m_recordPane->init(getRecordPane());
    }
    // タブ受取り用ペイン
    if (m_msgTabTargetPane == NULL){
        m_msgTabTargetPane = new CFocusTargetCtrl();
        m_msgTabTargetPane->init(getTabTargetPane());
    }
    // メッセージ用ペイン
    if (m_messagePane == NULL){
        m_messagePane = new CPaneMessage();
        m_messagePane->init(getMsgPane());

    }
    // 分割ウィンドウにセットする
    split();

}

// メッセージペインにメッセージを表示
void CMainPanel::displayMessages(const vector<CMessage*>& messages,
        const CNickTable& nickTable, const wxString& channelName,
        const CServiceConfiguration* configuration)
{
    m_messagePane->Show(false);
    m_messagePane->displayMessages(messages, nickTable, channelName,
            configuration);
    m_messagePane->Show(true);

}
void CMainPanel::addMessage(const CMessage* message)
{
    m_messagePane->pushLog(message);
    m_messagePane->clearUnreadBackgroundColor();
}

void CMainPanel::addUnreadMessage(const CChatMessage* message)
{
    m_channelPane->addUnreadMessage(message);
}
// メンバーペインにメンバーを表示
void CMainPanel::displayMembers(const vector<CMemberData*>& members)
{
    m_memBox->Show(false);
    m_memBox->displayMembers(members);
    m_memBox->Show(true);
}

// チャンネルペインにチャンネルを表示
void CMainPanel::displayChannels(
        const std::map<int, CChatServiceBase*>& services)
{
    m_channelPane->Show(false);
    m_channelPane->displayChannels(services);
    m_channelPane->Show(true);

}

// 文字列を検索
void CMainPanel::find(const wxString& words, int type)
{
    m_messagePane->find(words, type);
}
// メッセージペインをクリアする。
void CMainPanel::clearMessages(void)
{
    m_messagePane->clear();
}

// メンバーペインをクリアする
void CMainPanel::clearMembers(void)
{
    m_memBox->Clear();
}

// チャンネルペインをクリアする
void CMainPanel::clearChannels(void)
{
    wxTreeItemId rootId = m_channelPane->GetRootItem();
    m_channelPane->DeleteChildren(rootId);
}

// ログ一覧ペインにログを表示
void CMainPanel::displayLogs(const std::vector<CMessage*>& logs,
        const CServiceHolder* services)
{
    m_recordPane->displayLogs(logs, services);
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインの文字列をクリアする
void CMainPanel::clearPostPaneText(void)
{
    m_postPane->SetValue(wxEmptyString);
}

// 選択済みチャンネルを決める
void CMainPanel::selectedChannel(int serviceId, const wxString& channel)
{
    m_channelPane->selectChannel(serviceId, channel);
}

// 投稿ペインのIDを取得する
wxWindowID CMainPanel::getPostPaneID(void) const
{
    return m_postPane->GetId();
}

// 投稿ペインにフォーカスを与える。
void CMainPanel::setFocusPostPane(void)
{
    m_postPane->SetFocus();
}
// 投稿ペインに文字を設定する
void CMainPanel::setTextPostPane(const wxString& value)
{
    m_postPane->SetValue(value);
    setFocusPostPane();
    m_postPane->SetInsertionPointEnd();
}
//　投稿ペインに文字を追加する
wxString CMainPanel::getTextPostPane() const
{
    return m_postPane->GetValue();
}
// チャンネルペインのIDを取得する
wxWindowID CMainPanel::getCnPaneID(void) const
{
    return m_channelPane->GetId();
}

// メンバーペインのIDを取得する
wxWindowID CMainPanel::getMemPaneID(void) const
{
    return m_memBox->GetId();
}
// 一つ先のチャンネルを選択します。
void CMainPanel::selectNextChannel()
{
    m_channelPane->selectNextChannel();
}

// 一つ前のチャンネルを選択します。
void CMainPanel::selectPreviousChannel()
{
    m_channelPane->selectPreviousChannel();
}

// 次のタブを選択
void CMainPanel::selectNextTab()
{
    m_messagePane->AdvanceSelection();
}
// 前のタブを選択
void CMainPanel::selectPreviousTab()
{
    m_messagePane->AdvanceSelection(false);
}
//////////////////////////////////////////////////////////////////////

// 画面分割を行う
void CMainPanel::split(void)
{
    m_spMsg->SplitHorizontally(m_messagePane, m_postPane);
    m_spMsgTabTarget->SplitHorizontally(m_spMsg, m_msgTabTargetPane);
    m_spHorL->SplitHorizontally(m_spMsgTabTarget, m_recordPane);
    m_spHorR->SplitHorizontally(m_memBox, m_channelPane);
    this->SplitVertically(m_spHorL, m_spHorR);
}

}
