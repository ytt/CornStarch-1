#include "PaneRecord.hpp"

using namespace std;

namespace CornStarch
{
;

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
    Create(parent, CPaneRecord::PANE_RECEVE_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL);

    setNavigateHaldler();
    // フォントの設定(個人的にこれが好き)
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
    this->SetBackgroundColour(wxColour(200, 200, 200));
    GetCaret()->Hide();


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
            if (typeid(*logs[i]) == typeid(CChatMessage)){
                writeColoredText("<" + logs[i]->getChannelName() + ">",
                        *wxBLACK);
            }
            pushLog(logs[i]);
        }
    }
    this->ShowPosition(this->GetLastPosition());
}

//////////////////////////////////////////////////////////////////////
// メッセージログを表示
void CPaneRecord::pushServerName(const wxString& serviceName)
{
    writeColoredText(serviceName, *wxBLACK); // 本文を黒で表示
}

}
