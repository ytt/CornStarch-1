#ifndef FILTERDIALOG_HPP_
#define FILTERDIALOG_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>
#include <wx/combobox.h>
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
    wxChoice* m_choiceType;
    wxComboBox* m_comboBoxTarget;
    wxChoice* m_choiceTargetMessageType;

    wxCheckBox* m_checkBoxIsAnti;
    wxTextCtrl* m_textCtrlName; // フィルター名入力欄

    wxBoxSizer* bSizerTarget;
    wxBoxSizer* bSizerType;
    bool validateDialogResult() const; // 入力値の検証
    void onChoiceChanged(wxCommandEvent &event); //タイプ変更時

    // ダイアログが閉じられたときのイベントです。
    void onClose(wxCloseEvent& event);

    // Cancelボタンが押された時のイベントです。
    void onClickCancel(wxCommandEvent& event);

    // OKボタンが押された時のイベントです。
    void onOKCancel(wxCommandEvent& event);
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
