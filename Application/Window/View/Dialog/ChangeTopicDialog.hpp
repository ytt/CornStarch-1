#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>

namespace CornStarch
{;

// チャンネルトピック変更用ダイアログ
class CChangeTopicDialog : public wxDialog
{
private:
    //wxTextCtrl* m_topicText; // 新トピック入力用ダイアログ

    wxStaticText* m_staticText1;
    wxStaticText* m_staticText2;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_topicText;
public:
    CChangeTopicDialog(void);
    ~CChangeTopicDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title,const wxString& channelName, const wxString& topic);

    // トピックを取得する
    wxString getTopic(void) const;
};

}
