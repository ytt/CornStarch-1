#include "FocusTargetCtrl.hpp"

namespace CornStarch
{
// イベントテーブル


BEGIN_EVENT_TABLE(CFocusTargetCtrl, wxTextCtrl) //
EVT_SET_FOCUS(CFocusTargetCtrl::onFocused)
END_EVENT_TABLE()
;

CFocusTargetCtrl::CFocusTargetCtrl()
{

}

CFocusTargetCtrl::~CFocusTargetCtrl()
{
}
// 初期化を行う
void CFocusTargetCtrl::init(wxWindow* parent)
{
    // テキスト領域の作成
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 1),
            0 );
}
void CFocusTargetCtrl::onFocused(wxFocusEvent& event)
{
    wxThreadEvent* focusEvent = new wxThreadEvent();
    focusEvent->SetEventType(myEVT_FOCUSE_NEXT_INPUT_TEXT);
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetParent()->GetEventHandler(),
            focusEvent);
}
} /* namespace CornStarch */
