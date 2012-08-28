#include "NickChangeDialog.hpp"

namespace CornStarch
{;

CNickChangeDialog::CNickChangeDialog(void) : m_nickText(NULL)
{
}


CNickChangeDialog::~CNickChangeDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CNickChangeDialog::init(wxWindow* parent, const wxString& title, const wxString& serviceName, const wxString& nickName)
{
    wxDialog::Create(parent, wxID_ANY, title);
    this->SetSize(400, 120);

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("サーバー："), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
    m_staticText1->Wrap( -1 );
    bSizer2->Add( m_staticText1, 0, wxALL, 5 );

    m_staticText2 = new wxStaticText( this, wxID_ANY, serviceName, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText2->Wrap( -1 );
    bSizer2->Add( m_staticText2, 0, wxALL, 5 );

    bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("ニックネーム："), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
    m_staticText3->Wrap( -1 );
    bSizer3->Add( m_staticText3, 0, wxALL, 5 );

    m_nickText = new wxTextCtrl( this, wxID_ANY, nickName, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer3->Add( m_nickText, 0, wxALL, 5 );

    bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

    wxSizer* buttonSizer = wxDialog::CreateButtonSizer(wxOK | wxCANCEL);
    bSizer1->Add(buttonSizer, 0, wxALIGN_RIGHT, 0);
    this->SetSizer( bSizer1 );
    // Escで消した時の挙動
    SetEscapeId(wxID_CANCEL);

}

// チャンネル名を取得する
wxString CNickChangeDialog::getNickName(void) const
{
    if (m_nickText != NULL){
        return m_nickText->GetValue();
    }

    return "";
}

}
