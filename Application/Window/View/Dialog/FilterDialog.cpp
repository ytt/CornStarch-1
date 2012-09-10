#include "FilterDialog.hpp"
#include "../../Service/Filter/UserNameFilter.hpp"
#include "../../Service/Filter/MessageTypeFilter.hpp"
#include "../../Service/Filter/DateTimeFilter.hpp"
#include "../../Service/Message/ChatMessage.hpp"
#include "../../Service/Message/InviteMessage.hpp"
#include "../../Service/Message/JoinMessage.hpp"
#include "../../Service/Message/PartMessage.hpp"
#include "../../Service/Message/TopicMessage.hpp"
#include "../../Service/Message/MemberMessage.hpp"

namespace CornStarch
{
BEGIN_EVENT_TABLE(CFilterDialog, wxDialog) // Event宣言
EVT_CHOICE(CHOICE_ID, CFilterDialog::onChoiceChanged)
END_EVENT_TABLE()
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

    wxStaticText* m_staticText1 = new wxStaticText(this, wxID_ANY,
            wxT("チャンネル："), wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    bSizer->Add(m_staticText1, 0, wxALIGN_CENTER, 5);

    wxStaticText* m_staticTextChannel = new wxStaticText(this, wxID_ANY,
            channelName, wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextChannel->Wrap(-1);
    bSizer->Add(m_staticTextChannel, 0, wxALL, 5);

    bSizer9->Add(bSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizerName;
    bSizerName = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticTextName = new wxStaticText(this, wxID_ANY,
            wxT("フィルター名："), wxPoint(-1, -1), wxSize(100, -1),
            wxALIGN_RIGHT);
    m_staticTextName->Wrap(-1);
    bSizerName->Add(m_staticTextName, 0, wxALIGN_CENTER, 5);

    m_textCtrlName = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, 0);

    bSizerName->Add(m_textCtrlName, 0, wxALL, 5);

    bSizer9->Add(bSizerName, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer12;
    bSizer12 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("条件："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText2->Wrap(-1);
    bSizer12->Add(m_staticText2, 0, wxALIGN_CENTER, 5);
    wxString m_choiceTypeChoices[] = { wxT("ユーザー"), wxT("メッセージ"), wxT("日付") };
    int m_choiceTypeNChoices = sizeof(m_choiceTypeChoices) / sizeof(wxString);
    m_choiceType = new wxChoice(this, CHOICE_ID, wxDefaultPosition,
            wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0);
    bSizer12->Add(m_choiceType, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizer12, 1, 0, 5);

    // ユーザー
    bSizerTarget = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticTextTarget = new wxStaticText(this, wxID_ANY,
            wxT("対象："), wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticTextTarget->Wrap(-1);
    bSizerTarget->Add(m_staticTextTarget, 0, wxALIGN_CENTER_VERTICAL, 5);

    wxString* m_choiceUsers = &choices[0];
    m_comboBoxTarget = new wxComboBox(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, choices.size(), m_choiceUsers, 0);
    bSizerTarget->Add(m_comboBoxTarget, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizerTarget, 1, wxEXPAND, 5);

    // メッセージタイプ
    bSizerType = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticTextMessageType = new wxStaticText(this, wxID_ANY,
            wxT("タイプ："), wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticTextMessageType->Wrap(-1);
    bSizerType->Add(m_staticTextMessageType, 0, wxALIGN_CENTER_VERTICAL, 5);

    wxString m_choiceMessageTypeChoices[] = { wxT("チャット"), wxT("参加"), wxT("離脱"),
            wxT("ニックネーム"), wxT("トピック") };
    int m_choiceMessageTypeNChoices = sizeof(m_choiceMessageTypeChoices)
            / sizeof(wxString);
    m_choiceTargetMessageType = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, m_choiceMessageTypeNChoices,
            m_choiceMessageTypeChoices, 0);
    m_choiceTargetMessageType->SetSelection(0);
    bSizerType->Add(m_choiceTargetMessageType, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizerType, 1, wxEXPAND, 5);
    bSizerType->Show(false);

    // カレンダー
    bSizerDate = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* m_staticTextCalender = new wxStaticText(this, wxID_ANY,
            wxT("タイプ："), wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticTextCalender->Wrap(-1);
    bSizerDate->Add(m_staticTextCalender, 0, wxALIGN_CENTER_VERTICAL, 5);
    //m_datePicker1 = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT| wxDP_SPIN);
    //bSizerDate->Add( m_datePicker1, 0, wxALL, 5 );
    m_caldenr = new wxCalendarCtrl(this, wxID_ANY);
    bSizerDate->Add( m_caldenr, 0, wxALL, 5 );

    bSizer9->Add(bSizerDate, 1, wxEXPAND, 5);
    bSizerDate->Show(false);
    // 逆条件
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

    m_choiceType->SetSelection(0);
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
    if (validateDialogResult()){
        if (m_choiceType->GetStringSelection() == "ユーザー"){
            CUserNameFilter* filter = new CUserNameFilter();
            filter->setName(m_textCtrlName->GetValue());
            filter->setUserName(m_comboBoxTarget->GetValue());
            filter->setAntiFilter(m_checkBoxIsAnti->IsChecked());
            return filter;
        } else if(m_choiceType->GetStringSelection() == "メッセージ"){
            CMessageTypeFilter* filter = new CMessageTypeFilter();
            filter->setName(m_textCtrlName->GetValue());
            filter->setTypeInfoName(
                    getMessageTypeInfo(
                            m_choiceTargetMessageType->GetStringSelection()));
            filter->setAntiFilter(m_checkBoxIsAnti->IsChecked());
            return filter;
        }else if(m_choiceType->GetStringSelection() == "日付"){
            CDateTimeFilter* filter = new CDateTimeFilter();
            filter->setName(m_textCtrlName->GetValue());
            filter->setDate(m_caldenr->GetDate());
            filter->setAntiFilter(m_checkBoxIsAnti->IsChecked());
            return filter;
        }
    }
    return NULL;
}

// チョイスが変更されたときのイベントです。
void CFilterDialog::onChoiceChanged(wxCommandEvent &event)
{
    bSizerTarget->Show(false);
    bSizerType->Show(false);
    bSizerDate->Show(false);
    if (m_choiceType->GetStringSelection() == "ユーザー"){
        bSizerTarget->Show(true);
        this->SetSize(400, 200);
    } else if (m_choiceType->GetStringSelection() == "メッセージ"){
        bSizerType->Show(true);
        this->SetSize(400, 200);
    } else if (m_choiceType->GetStringSelection() == "日付"){
        bSizerDate->Show(true);
        this->SetSize(400, 400);
    }
//    this->Fit();
//    this->SetSize(DoGetBestSize());
    this->Layout();
}

wxString CFilterDialog::getMessageTypeInfo(const wxString& text) const
{
    if (text == "チャット"){
        return typeid(CChatMessage).name();
    } else if (text == "参加"){
        return typeid(CJoinMessage).name();
    } else if (text == "離脱"){
        return typeid(CPartMessage).name();
    } else if (text == "トピック"){
        return typeid(CTopicMessage).name();
    } else if (text == "ニックネーム"){
        return typeid(CMemberMessage).name();
    }
    return "";
}
bool CFilterDialog::validateDialogResult() const
{
    if (m_textCtrlName->GetValue() == ""){
        wxMessageBox("名前を入力してください");
        return false;
    }
    return true;
}

} /* namespace CornStarch */
