#ifndef FILTERDIALOG_HPP_
#define FILTERDIALOG_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>
#include <wx/combobox.h>
#include <wx/calctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include "../../Service/Filter/IFilter.hpp"
using namespace std;
namespace CornStarch
{

class CFilterDialog: public wxDialog
{
DECLARE_EVENT_TABLE()
    enum
    {
        CHOICE_ID = 501
    };
    wxChoice* m_choiceType; // 種類選択
    wxComboBox* m_comboBoxTarget; // 対象ユーザー
    wxChoice* m_choiceTargetMessageType; // メッセージタイプ
    wxCalendarCtrl* m_caldenr;
    wxCheckBox* m_checkBoxIsAnti; // 逆条件下
    wxTextCtrl* m_textCtrlName; // フィルター名入力欄

    wxBoxSizer* bSizerDate;
    wxBoxSizer* bSizerTarget;
    wxBoxSizer* bSizerType;
    bool validateDialogResult() const; // 入力値の検証
    void onChoiceChanged(wxCommandEvent &event); //タイプ変更時

    wxString getMessageTypeInfo(const wxString& text) const; //タイプIDの取得
public:
    CFilterDialog();
    virtual ~CFilterDialog();

    void init(wxWindow* parent, const wxString& channelName,
            vector<wxString>& names);
    // 選択した要素を取得する
    IFilter* getFilter(void) const;
};

} /* namespace CornStarch */
#endif /* FILTERDIALOG_HPP_ */
