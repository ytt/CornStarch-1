#include "FindDialog.hpp"

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
    this->SetSize(400, 200);
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer9;
    bSizer9 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("キーワード:"),
            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    bSizer->Add(m_staticText1, 0, wxALIGN_CENTER, 5);

    m_searchCtrl1 = new wxSearchCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxSize(200, -1), 0);
#ifndef __WXMAC__
    m_searchCtrl1->ShowSearchButton(true);
#endif
    m_searchCtrl1->ShowCancelButton(false);
    bSizer->Add(m_searchCtrl1, 0, wxALL, 5);

    bSizer9->Add(bSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer12;
    bSizer12 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("タイプ："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText2->Wrap(-1);
    bSizer12->Add(m_staticText2, 0, wxALIGN_CENTER, 5);

    wxString m_choiceTypeChoices[] = { wxT("現在のチャンネル"), wxT("すべてのチャンネル") };
    int m_choiceTypeNChoices = sizeof(m_choiceTypeChoices) / sizeof(wxString);
    m_choiceType = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0);
    m_choiceType->SetSelection(0);
    bSizer12->Add(m_choiceType, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizer12, 1, 0, 5);

    wxBoxSizer* bSizer171;
    bSizer171 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText71 = new wxStaticText(this, wxID_ANY, wxT("結果："),
            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText71->Wrap(-1);
    bSizer171->Add(m_staticText71, 0, wxALL, 5);

    m_richText1 =
            new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                    wxSize(200,150),
                    0 | wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxWANTS_CHARS);
    bSizer171->Add(m_richText1, 1, wxEXPAND | wxALL, 5);

    bSizer9->Add(bSizer171, 1, wxEXPAND, 5);

    this->SetSizer(bSizer9);
    this->Layout();

    this->Centre(wxBOTH);
}
} /* namespace CornStarch */
