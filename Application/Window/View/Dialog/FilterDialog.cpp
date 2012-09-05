#include "FilterDialog.hpp"
#include "../../Service/Filter/UserNameFilter.hpp"

namespace CornStarch
{

CFilterDialog::CFilterDialog()
{
}

CFilterDialog::~CFilterDialog()
{
}
void CFilterDialog::init(wxWindow* parent, const wxString& channelName,
        vector<wxString>& choices)
{
    wxDialog::Create(parent, wxID_ANY, "タブの追加");
    this->SetSize(400, 200);

    wxBoxSizer* bSizer9;
    bSizer9 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticText1 = new wxStaticText(this,
            wxID_ANY, wxT("チャンネル："), wxPoint(-1, -1), wxSize(100, -1),
            wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    bSizer->Add(m_staticText1, 0, wxALIGN_CENTER, 5);

    wxStaticText* m_staticTextChannel = new wxStaticText(this, wxID_ANY, channelName,
            wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextChannel->Wrap(-1);
    bSizer->Add(m_staticTextChannel, 0, wxALL, 5);

    bSizer9->Add(bSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer12;
    bSizer12 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("条件："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText2->Wrap(-1);
    bSizer12->Add(m_staticText2, 0, wxALIGN_CENTER, 5);
    wxString m_choiceTypeChoices[] = { wxT("ユーザー"), wxT("メッセージ") };
    int m_choiceTypeNChoices = sizeof(m_choiceTypeChoices) / sizeof(wxString);
    m_choiceType = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0);
    m_choiceType->SetSelection(0);
    bSizer12->Add(m_choiceType, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizer12, 1, 0, 5);

    wxBoxSizer* bSizer16;
    bSizer16 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticTextTarget = new wxStaticText(this, wxID_ANY,
            wxT("対象："), wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticTextTarget->Wrap(-1);
    bSizer16->Add(m_staticTextTarget, 0, wxALIGN_CENTER_VERTICAL, 5);

    wxString* m_choiceUsers = &choices[0];
    m_choiceTarget = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, choices.size(), m_choiceUsers, 0);
    m_choiceTarget->SetSelection(0);
    bSizer16->Add(m_choiceTarget, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizer16, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer17;
    bSizer17 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticText7 = new wxStaticText(this, wxID_ANY, wxT("逆条件："),
            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText7->Wrap(-1);
    bSizer17->Add(m_staticText7, 0, wxALL, 5);

    m_checkBoxIsAnti = new wxCheckBox(this, wxID_ANY, wxT("条件に合わないものを表示する。"),
            wxDefaultPosition, wxDefaultSize, 0);
    m_checkBoxIsAnti->SetValue(false);
    bSizer17->Add(m_checkBoxIsAnti, 0, wxALIGN_LEFT, 5);

    bSizer9->Add(bSizer17, 1, wxEXPAND, 5);

// タイトルバーで消した時の挙動
    SetEscapeId(wxID_CANCEL);
// 基本ボタン
    wxSizer* buttonSizer = wxDialog::CreateButtonSizer(wxOK | wxCANCEL);
    bSizer9->Add(buttonSizer, 0, wxALIGN_RIGHT, 0);

    this->SetSizer(bSizer9);
    this->Layout();

    this->Centre(wxBOTH);
}
// 選択した要素を取得する
IFilter* CFilterDialog::getFilter(void) const
{
    CUserNameFilter* filter = new CUserNameFilter();
    filter->setName(m_choiceTarget->GetStringSelection());
    filter->setUserName(m_choiceTarget->GetStringSelection());
    filter->setAntiFilter(m_checkBoxIsAnti->IsChecked());
    return filter;
}
} /* namespace CornStarch */
