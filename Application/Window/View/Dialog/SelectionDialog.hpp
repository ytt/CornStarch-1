#ifndef SELECTIONDIALOG_HPP_
#define SELECTIONDIALOG_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>

using namespace std;
namespace CornStarch
{

class CSelectionDialog: public wxDialog
{
    wxStaticText* m_staticText1;
    wxStaticText* m_staticText2;
    wxStaticText* m_staticText3;
    wxChoice* m_choice;
public:
    CSelectionDialog();
    virtual ~CSelectionDialog();
    void init(wxWindow* parent, const wxString& title,
            const wxString& header, const wxString& headerContent,
            const wxString& choiceHeader, vector<wxString>& choices);

    // 選択した要素名を取得する
    wxString getValue(void) const;
};

} /* namespace CornStarch */
#endif /* SELECTIONDIALOG_HPP_ */
