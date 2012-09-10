#include "PaneRecord.hpp"

using namespace std;

namespace CornStarch
{
;
BEGIN_EVENT_TABLE(CPaneRecord, CLogTextCtrl) EVT_LEFT_DCLICK(CPaneRecord::onDoubleClicked)
END_EVENT_TABLE()
CPaneRecord::CPaneRecord(void)
{
}

CPaneRecord::~CPaneRecord(void)
{
}

//////////////////////////////////////////////////////////////////////

const int CPaneRecord::PANE_RECEVE_ID = 10000;
// 初期化を行う
void CPaneRecord::init(wxWindow* parent)
{
    // テキスト領域の作成
    Create(parent, CPaneRecord::PANE_RECEVE_ID, wxEmptyString,
            wxDefaultPosition, wxDefaultSize,
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL);

    setNavigateHaldler();
    // フォントの設定(個人的にこれが好き)
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
    this->SetBackgroundColour(wxColour(200, 200, 200));
    GetCaret()->Hide();

}
void CPaneRecord::onDoubleClicked(wxMouseEvent& event)
{
    wxString value = GetValue();
    int caretPosition = GetCaretPosition();
    wxString valueByCurrentPosition = value.substr(0, caretPosition);
    int count = valueByCurrentPosition.Replace("\n", "");
    // イベント送信
    CMessageControlDoubleClickedEvent* selectedEvent =
            new CMessageControlDoubleClickedEvent();
    selectedEvent->setIndex(count);
    selectedEvent->SetEventType(myEVT_MESSAGE_CONTROL_DOUBLECLICKED); // イベントタイプ
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetEventHandler(),
            selectedEvent);
}

wxString CPaneRecord::getServiceNameFromSelectedText(const wxString lineText)
{
    int index = lineText.find("[");
    return lineText.substr(0, index);
}

wxString CPaneRecord::getChannelNameFromSelectedText(const wxString lineText)
{
    int index = lineText.find("[") + 1;
    int endIndex = lineText.find("]") - 1;
    return lineText.SubString(index, endIndex);

}
// ログ一覧を表示
void CPaneRecord::displayLogs(const vector<CMessage*>& logs,
        const CServiceHolder* services)
{
    Clear();

    size_t size = logs.size();
    for (size_t i = 0; i < size; i++){
        int serviceId = logs[i]->getServiceId();
        CChatServiceBase* service = services->getService(serviceId);
        if (service != NULL){
            pushServerName(service->getName());
            wxString nickName = service->getNickTable().getNickname(
                    logs[i]->getUserName());
            logs[i]->setNick(nickName);
            writeColoredText("[" + logs[i]->getChannelName() + "]", *wxBLACK);
            pushLog(logs[i]);
        }
    }
    this->ShowPosition(this->GetLastPosition());
    GetCaret()->Hide();
}

//////////////////////////////////////////////////////////////////////
// メッセージログを表示
void CPaneRecord::pushServerName(const wxString& serviceName)
{
    writeColoredText(serviceName, *wxBLACK); // 本文を黒で表示
}

}
