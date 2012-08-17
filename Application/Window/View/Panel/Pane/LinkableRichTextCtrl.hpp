#ifndef LINKABLERICHTEXTBOX_HPP_
#define LINKABLERICHTEXTBOX_HPP_

#include <wx/richtext/richtextctrl.h>
namespace CornStarch
{

class CLinkableRichTextCtrl : public wxRichTextCtrl
{
protected:
    virtual void onNavigate(wxTextUrlEvent& event);
    void setNavigateHaldler();
public:
    CLinkableRichTextCtrl();
    virtual ~CLinkableRichTextCtrl();

    // コンテントをリンク加工して表示
    void writeLinkableText(const wxString& content);
};

} /* namespace CornStarch */
#endif /* LINKABLERICHTEXTBOX_HPP_ */
