#include "SelectionDialog.hpp"

using namespace std;

namespace CornStarch
{

CSelectionDialog::CSelectionDialog()
{

}

CSelectionDialog::~CSelectionDialog()
{
}
// 初期化を行う
void CSelectionDialog::init(wxWindow* parent, const wxString& title,
        const wxString& header, const wxString& headerContent,
        const wxString& choiceHeader, vector<wxString>& choices)
{
    wxDialog::Create(parent, wxID_ANY, title);
    this->SetSize(400, 140);

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText1 = new wxStaticText(this, wxID_ANY, header, wxDefaultPosition,
            wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    bSizer2->Add(m_staticText1, 0, wxALL, 5);

    m_staticText2 = new wxStaticText(this, wxID_ANY, headerContent,
            wxDefaultPosition, wxDefaultSize, 0);
    m_staticText2->Wrap(-1);
    bSizer2->Add(m_staticText2, 0, wxALL, 5);

    bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText3 = new wxStaticText(this, wxID_ANY, choiceHeader,
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText3->Wrap(-1);
    bSizer3->Add(m_staticText3, 0, wxALL, 5);

    wxString* m_choiceTypeChoices = &choices[0];

    m_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, choices.size(), m_choiceTypeChoices, 0);
    m_choice->SetSelection(0);
    bSizer3->Add(m_choice, 0, wxALL, 5);

    bSizer1->Add(bSizer3, 1, wxEXPAND, 5);

    wxSizer* buttonSizer = wxDialog::CreateButtonSizer(wxOK | wxCANCEL);
    bSizer1->Add(buttonSizer, 0, wxALIGN_RIGHT, 0);
    this->SetSizer(bSizer1);
    // Escで消した時の挙動
    SetEscapeId(wxID_CANCEL);
}

// 選択した要素名を取得する
wxString CSelectionDialog::getValue(void) const
{
    return m_choice->GetStringSelection();
}
}

/* namespace CornStarch */
