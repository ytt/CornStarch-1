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

// 初期化を行う
void CPaneRecord::init(wxWindow* parent)
{
    // テキスト領域の作成
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxRE_MULTILINE | wxRE_READONLY | wxVSCROLL);

    setNavigateHaldler();
    // フォントの設定(個人的にこれが好き)
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
    this->SetBackgroundColour(wxColour(200, 200, 200));
}

// ログ一覧を表示
void CPaneRecord::displayLogs(const vector<CServiceLog*>& logs,const CServiceHolder* services)
{
    Clear();
    GetCaret()->Hide();

    size_t size = logs.size();
    for (size_t i = 0; i < size; i++){
        int serviceId =logs[i]->getServiceId();
        CChatServiceBase* service = services->getService(serviceId);
        pushServerName(service->getName());
        wxString nickName = service->getNickTable().getNickname(logs[i]->getUserName());
        logs[i]->setNick(nickName);
        if (typeid(*logs[i]) == typeid(CMessageLog)){
            writeColoredText("<" + logs[i]->getChannelName() + ">", *wxBLACK);
            pushLog(*(CMessageLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CJoinLog)){
            pushLog(*(CJoinLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CPartLog)){
            pushLog(*(CPartLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CTopicLog)){
            pushLog(*(CTopicLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CMemberLog)){
            pushLog(*(CMemberLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CInviteLog)){
            pushLog(*(CInviteLog*) logs[i]);
        } else if (typeid(*logs[i]) == typeid(CKickLog)){
            pushLog(*(CKickLog*) logs[i]);
        }
        this->Newline();
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
