#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>

namespace CornStarch
{;

// チャンネル名指定用ダイアログ
class CChannelDialog : public wxDialog
{
private:

    wxStaticText* m_staticText1;
    wxStaticText* m_staticText2;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_channelText; // チャンネル名入力欄

public:
    CChannelDialog(void);
    ~CChannelDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title,const wxString& serverName);

    // チャンネル名を取得する
    wxString getChannelName(void) const;
};

}
