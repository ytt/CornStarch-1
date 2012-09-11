#include "FindDialog.hpp"
#include <iostream>
namespace CornStarch
{
CFindDialog::CFindDialog()
{

}

CFindDialog::~CFindDialog()
{
}

void CFindDialog::init(wxWindow* parent)
{
    wxDialog::Create(parent, wxID_ANY, "検索");
    this->SetSize(300, 110);
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer9;
    bSizer9 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("キーワード:"),
            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    bSizer->Add(m_staticText1, 0, wxALIGN_CENTER, 5);

    m_searchCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxSize(200, -1), wxTE_PROCESS_ENTER);
    bSizer->Add(m_searchCtrl1, 0, wxALL, 5);

    bSizer9->Add(bSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer12;
    bSizer12 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("タイプ："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText2->Wrap(-1);
    bSizer12->Add(m_staticText2, 0, wxALIGN_CENTER, 5);

    wxString m_choiceTypeChoices[] = { wxT("現在のチャンネル")};//, wxT("すべてのチャンネル") };
    int m_choiceTypeNChoices = sizeof(m_choiceTypeChoices) / sizeof(wxString);
    m_choiceType = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0);
    m_choiceType->SetSelection(0);
    bSizer12->Add(m_choiceType, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizer12, 1, 0, 5);

//    wxBoxSizer* bSizer171;
//    bSizer171 = new wxBoxSizer(wxHORIZONTAL);
//
//    m_staticText71 = new wxStaticText(this, wxID_ANY, wxT("結果："),
//            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
//    m_staticText71->Wrap(-1);
//    bSizer171->Add(m_staticText71, 0, wxALL, 5);
//
//    m_richText1 =
//            new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
//                    wxSize(200,150),
//                    0 | wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxWANTS_CHARS);
//    bSizer171->Add(m_richText1, 1, wxEXPAND | wxALL, 5);
//
//    bSizer9->Add(bSizer171, 1, wxEXPAND, 5);
    // パネル上のボタン
    wxButton* ok = new wxButton(this, wxID_ANY, "検索", wxPoint(250, 150));
    bSizer9->Add(ok, 1, wxALIGN_RIGHT, 5);
    this->SetSizer(bSizer9);
    this->Layout();

    this->Centre(wxBOTH);
//    SetDefaultItem(ok);

    // エンターキー押下時
    this->Connect(ok->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(CFindDialog::onFind));

    // エンターキー押下時
    this->Connect(m_searchCtrl1->GetId(), wxEVT_COMMAND_TEXT_ENTER,
            wxCommandEventHandler(CFindDialog::onFind));
}

// 検索
void CFindDialog::onFind(wxCommandEvent& event)
{
    wxCommandEvent* findEvent = new wxCommandEvent();
    findEvent->SetEventType(myEVT_FIND_REQUEST);
    findEvent->SetString(m_searchCtrl1->GetValue());
    wxQueueEvent(
            GetParent()->GetEventHandler(),
            findEvent);
}

// メンバーペインのIDを取得する
wxWindowID CFindDialog::getFindPaneID(void) const
{
    return m_searchCtrl1->GetId();
}
} /* namespace CornStarch */
