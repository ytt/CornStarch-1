#include "PaneMessage.hpp"

namespace CornStarch
{

CPaneMessage::CPaneMessage()
{
}

CPaneMessage::~CPaneMessage()
{
    delete m_allFilter;
}
void CPaneMessage::init(wxWindow* parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    m_allFilter = new CAllFilter();
    m_allFilter->setName("All");
    m_allLogCtrl = createTab(m_allFilter, NULL);

}

CPaneMsg* CPaneMessage::createTab(const IFilter* filter,
        const CServiceConfiguration* configuration)
{
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, wxTAB_TRAVERSAL);
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    CPaneMsg* msgPanel = new CPaneMsg();
    msgPanel->init(panel);
    msgPanel->SetBackgroundColour(
            wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    boxSizer->Add(msgPanel, 1, wxEXPAND | wxALL, 5);

    panel->SetSizer(boxSizer);
    panel->Layout();
    boxSizer->Fit(panel);
    this->AddPage(panel, filter->getName(), false);
    msgPanel->setFilter(filter);
    msgPanel->setConfiguration(configuration);
    return msgPanel;
}
void CPaneMessage::displayMessages(const std::vector<CMessage*>& messages,
        const CNickTable& nickTable, const wxString& channelName,
        const CServiceConfiguration* configuration)
{
    vector<IFilter*>* filters = configuration->getFilters(channelName);
    if (filters == NULL){
        return;
    }
    this->Freeze();
    m_messagePanels.clear();
    // 全てページの再セット
    m_messagePanels.push_back(m_allLogCtrl);
    m_allLogCtrl->Clear();
    m_allLogCtrl->setConfiguration(configuration);

    // 現在のページを全て削除。
    while (this->GetPageCount() != 1){
        this->DeletePage(1);
    }
    // ページの作成
    vector<IFilter*>::iterator itFilter = filters->begin();
    while (itFilter != filters->end()){
        CPaneMsg* msgPanel = createTab(*itFilter, configuration);
        m_messagePanels.push_back(msgPanel);
        itFilter++;
    }

    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        CMessage* log = messages[i];
        wxString nickName = nickTable.getNickname(log->getUserName());
        log->setNick(nickName);
        pushLog(log);
    }
    this->Thaw();

    // 一番したまでスクロール
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->ShowPosition((*it)->GetLastPosition());
        it++;
    }
}
// 選択する
void CPaneMessage::find(const wxString& words, int type)
{
    this->SetSelection(0);
    wxString text = m_allLogCtrl->GetValue();
    long selectionFrom;
    long selectionTo;
    // 選択があれば、そこから探す。
    m_allLogCtrl->GetSelection(&selectionFrom, &selectionTo);
    if (selectionFrom == selectionTo){
        selectionTo = 0;
    }
    // 見つかれば選択する
    int index = text.find(words, selectionTo);
    if (index != wxString::npos){
        m_allLogCtrl->SetSelection(index, index + words.Len());
        m_allLogCtrl->ShowPosition(index + words.Len());
        return;
    }
    // 途中からの検索で見つからなければ、先頭から改めて探す
    if (selectionTo != 0){
         index = text.find(words);
         if (index != wxString::npos){
             m_allLogCtrl->SetSelection(index, index + words.Len());
             m_allLogCtrl->ShowPosition(index + words.Len());
         }
    }
}

void CPaneMessage::pushLog(const CMessage* log)
{
    // すべての小ペインに要素を追加
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->pushLog(log);
        it++;
    }
}
void CPaneMessage::clearUnreadBackgroundColor()
{
    // すべての子ペインの背景をクリア
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->clearUnreadBackgroundColor();
        it++;
    }
}
// すべてのテキストボックスをクリア。
void CPaneMessage::clear()
{
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->Clear();
        it++;
    }
}
} /* namespace CornStarch */
