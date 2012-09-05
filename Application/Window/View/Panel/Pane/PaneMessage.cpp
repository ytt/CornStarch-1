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
    m_allLogCtrl = createPage(m_allFilter, NULL);

}

CPaneMsg* CPaneMessage::createPage(const IFilter* filter,
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
    vector<IFilter*> filters = configuration->getFilters(channelName);
    m_messagePanels.clear();
    m_messagePanels.push_back(m_allLogCtrl);
    m_allLogCtrl->Clear();
    m_allLogCtrl->setConfiguration(configuration);
    while (this->GetPageCount() != 1){
        this->DeletePage(1);
    }
    vector<IFilter*>::iterator itFilter = filters.begin();
    while (itFilter != filters.end()){
        CPaneMsg* msgPanel =createPage(*itFilter, configuration);
        m_messagePanels.push_back(msgPanel);
        itFilter++;
    }
    this->Refresh();
    this->Update();

    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        CMessage* log = messages[i];
        wxString nickName = nickTable.getNickname(log->getUserName());
        log->setNick(nickName);
        pushLog(log);
    }
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->ShowPosition((*it)->GetLastPosition());
        it++;
    }
}

void CPaneMessage::pushLog(const CMessage* log)
{
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->pushLog(log);
        it++;
    }
}
void CPaneMessage::clearUnreadBackgroundColor()
{
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->clearUnreadBackgroundColor();
        it++;
    }

}
void CPaneMessage::clear()
{
    vector<CPaneMsg*>::iterator it = m_messagePanels.begin();
    while (it != m_messagePanels.end()){
        (*it)->Clear();
        it++;
    }
}
} /* namespace CornStarch */
