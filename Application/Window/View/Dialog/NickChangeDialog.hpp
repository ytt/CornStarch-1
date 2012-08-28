#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>

namespace CornStarch
{;

// ニックネーム変更用ダイアログ
class CNickChangeDialog : public wxDialog
{
private:
    wxStaticText* m_staticText1;
    wxStaticText* m_staticText2;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_nickText; // ニックネーム入力欄
public:
    CNickChangeDialog(void);
    ~CNickChangeDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title, const wxString& serviceName, const wxString& nickName);

    // ニックネームを取得する
    wxString getNickName(void) const;
};

}
