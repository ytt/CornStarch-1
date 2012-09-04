#include "PaneMessage.hpp"

namespace CornStarch
{

CPaneMessage::CPaneMessage()
{
}

CPaneMessage::~CPaneMessage()
{
}
void CPaneMessage::init(wxWindow* parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxTAB_TRAVERSAL);
    wxBoxSizer* bSizer6;
    bSizer6 = new wxBoxSizer(wxVERTICAL);

    m_allLogCtrl = new CPaneMsg();
    m_allLogCtrl->init(m_panel1);

    m_allLogCtrl->SetBackgroundColour(
            wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    bSizer6->Add(m_allLogCtrl, 1, wxEXPAND | wxALL, 5);

    m_panel1->SetSizer(bSizer6);
    m_panel1->Layout();
    bSizer6->Fit(m_panel1);
    this->AddPage(m_panel1, wxT("All"), false);
    m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxTAB_TRAVERSAL);
    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer(wxVERTICAL);

    m_chatLogCtrl = new CPaneMsg();
    m_chatLogCtrl->init(m_panel2);
    m_chatLogCtrl->SetBackgroundColour(
            wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    bSizer5->Add(m_chatLogCtrl, 1, wxEXPAND | wxALL, 5);

    m_panel2->SetSizer(bSizer5);
    m_panel2->Layout();
    bSizer5->Fit(m_panel2);
    this->AddPage(m_panel2, wxT("Chat"), false);
    m_panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxTAB_TRAVERSAL);
    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer(wxVERTICAL);

    m_systemLogCtrl = new CPaneMsg();
    m_systemLogCtrl->init(m_panel3);
    m_systemLogCtrl->SetBackgroundColour(
            wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    bSizer4->Add(m_systemLogCtrl, 1, wxEXPAND | wxALL, 5);

    m_panel3->SetSizer(bSizer4);
    m_panel3->Layout();
    bSizer4->Fit(m_panel3);
    this->AddPage(m_panel3, wxT("System"), false);

}

void CPaneMessage::displayMessages(const std::vector<CMessage*>& messages,
        const CNickTable& nickTable, const CServiceConfiguration* configuration)
{

    this->Freeze();
    m_allLogCtrl->Clear();
    m_chatLogCtrl->Clear();
    m_systemLogCtrl->Clear();
    m_allLogCtrl->setConfiguration(configuration);
    m_chatLogCtrl->setConfiguration(configuration);
    m_systemLogCtrl->setConfiguration(configuration);
    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        CMessage* log = messages[i];
        vector<IFilter*> filters = configuration->getFilters(
                log->getChannelName());
        if (isFilterPassed(log,filters)){
            wxString nickName = nickTable.getNickname(log->getUserName());
            log->setNick(nickName);
            pushLog(log);
        }
    }
    this->Thaw();
    m_allLogCtrl->ShowPosition(m_allLogCtrl->GetLastPosition());
    m_chatLogCtrl->ShowPosition(m_chatLogCtrl->GetLastPosition());
    m_chatLogCtrl->ShowPosition(m_chatLogCtrl->GetLastPosition());
}
bool CPaneMessage::isFilterPassed(const CMessage* message,
        const vector<IFilter*>& filters)
{
    vector<IFilter*>::const_iterator it = filters.begin();
    while (it != filters.end()){
        if ((*it)->isValid(message) == false){
            return false;
        }
        it++;
    }
    return true;
}

void CPaneMessage::pushLog(const CMessage* log)
{
    m_allLogCtrl->pushLog(log);
    if (typeid(*log) == typeid(CChatMessage)){
        m_chatLogCtrl->pushLog(log);
    } else{
        m_systemLogCtrl->pushLog(log);
    }
}
void CPaneMessage::clearUnreadBackgroundColor()
{
    m_systemLogCtrl->clearUnreadBackgroundColor();
    m_allLogCtrl->clearUnreadBackgroundColor();
    m_chatLogCtrl->clearUnreadBackgroundColor();

}
void CPaneMessage::clear()
{
    m_systemLogCtrl->Clear();
    m_allLogCtrl->Clear();
    m_chatLogCtrl->Clear();
}
} /* namespace CornStarch */
