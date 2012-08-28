#include "ChangeTopicDialog.hpp"

namespace CornStarch
{;

CChangeTopicDialog::CChangeTopicDialog(void)
{
}


CChangeTopicDialog::~CChangeTopicDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CChangeTopicDialog::init(wxWindow* parent, const wxString& title,const wxString& channelName, const wxString& topic)
{
    wxDialog::Create(parent, wxID_ANY, title);
    this->SetSize(400, 120);
    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("チャンネル："), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
    m_staticText1->Wrap( -1 );
    bSizer2->Add( m_staticText1, 0, wxALL, 5 );

    m_staticText2 = new wxStaticText( this, wxID_ANY, channelName, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText2->Wrap( -1 );
    bSizer2->Add( m_staticText2, 0, wxALL, 5 );

    bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxHORIZONTAL );

    m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("トピック："), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT );
    m_staticText3->Wrap( -1 );
    bSizer3->Add( m_staticText3, 0, wxALL, 5 );

    m_topicText = new wxTextCtrl( this, wxID_ANY, topic, wxDefaultPosition, wxSize( 200,-1 ), 0 );
    bSizer3->Add( m_topicText, 0, wxALL, 5 );

    bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

    wxSizer* buttonSizer = wxDialog::CreateButtonSizer(wxOK | wxCANCEL);
    bSizer1->Add(buttonSizer, 0, wxALIGN_RIGHT, 0);
    this->SetSizer( bSizer1 );

    // Escで消した時の挙動
    SetEscapeId(wxID_CANCEL);

}

// チャンネル名を取得する
wxString CChangeTopicDialog::getTopic(void) const
{
    if (m_topicText != NULL){
        return m_topicText->GetValue();
    }

    return "";
}

}
