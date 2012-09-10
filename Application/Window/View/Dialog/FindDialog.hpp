#ifndef FINDDIALOG_HPP_
#define FINDDIALOG_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>
#include <wx/choice.h>
#include <wx/srchctrl.h>
#include <wx/richtext/richtextctrl.h>
namespace CornStarch
{

wxDECLARE_EVENT(myEVT_FIND_REQUEST, wxCommandEvent);
class CFindDialog: public wxDialog
{
    enum
    {
        CHOICE_ID = 502
    };

    wxStaticText* m_staticText1;
    wxTextCtrl* m_searchCtrl1;
    wxStaticText* m_staticText2;
    wxChoice* m_choiceType;
    wxStaticText* m_staticText71;
    wxRichTextCtrl* m_richText1;
public:
    CFindDialog();
    virtual ~CFindDialog();
    void init(wxWindow* parent);
    // メンバーペインのIDを取得する
    wxWindowID getFindPaneID(void) const;

    void onFind(wxCommandEvent& event);

};

} /* namespace CornStarch */
#endif /* FINDDIALOG_HPP_ */
