#include "PanePost.hpp"

namespace CornStarch
{
;
BEGIN_EVENT_TABLE(CPanePost, wxTextCtrl) //
EVT_KEY_DOWN(CPanePost::onKeyDown)
END_EVENT_TABLE()
;
CPanePost::CPanePost(void)
{
}

CPanePost::~CPanePost(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPanePost::init(wxWindow* parent)
{
	
    // テキスト領域の作成
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxTE_PROCESS_ENTER
		
	#ifdef _WIN32	
			|wxTE_PROCESS_TAB
#endif
			);
}
void CPanePost::onKeyDown(wxKeyEvent& event)
{
    wxKeyEvent* keyEvent = new wxKeyEvent(event);
    keyEvent->SetEventType(myEVT_KEYDDOWN_ON_POSTPANE);
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetParent()->GetParent()->GetEventHandler(),
            keyEvent);
    if (event.GetModifiers() != wxMOD_ALT){
        event.Skip(true);
    }
}
}
