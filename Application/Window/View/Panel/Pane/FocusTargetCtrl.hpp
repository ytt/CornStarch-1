#ifndef FOCUSTARGETCTRL_HPP_
#define FOCUSTARGETCTRL_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
namespace CornStarch
{

wxDECLARE_EVENT(myEVT_FOCUSE_NEXT_INPUT_TEXT, wxCommandEvent);
// タブを受け取って、コントロールのフォーカスが移動したことを通知させるためのコントロール
// (MacではProcess_Tabで落ち、KeyDown、Menuからでは飲み込んでしまう)
class CFocusTargetCtrl: public wxTextCtrl
{
    // wxWindowイベントを処理させたいクラスに利用するマクロ
DECLARE_EVENT_TABLE()
    ;

    // フォーカスされたときに呼ぶ
    void onFocused(wxFocusEvent& event);

public:
    CFocusTargetCtrl();
    virtual ~CFocusTargetCtrl();
    void init(wxWindow* parent);

};

} /* namespace CornStarch */
#endif /* FOCUSTARGETCTRL_HPP_ */
