#ifndef FILTERDIALOG_HPP_
#define FILTERDIALOG_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>
#include "../../Service/Filter/IFilter.hpp"
using namespace std;
namespace CornStarch
{

class CFilterDialog: public wxDialog
{
    wxChoice* m_choiceType;
    wxChoice* m_choiceTarget;
    wxCheckBox* m_checkBoxIsAnti;
    wxTextCtrl* m_textCtrlValue; // チャンネル名入力欄
public:
    CFilterDialog();
    virtual ~CFilterDialog();

    void init(wxWindow* parent,const wxString& channelName, vector<wxString>& names);
    // 選択した要素を取得する
    IFilter* getFilter(void) const;
};

} /* namespace CornStarch */
#endif /* FILTERDIALOG_HPP_ */
