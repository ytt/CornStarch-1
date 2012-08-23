#include "GetMessageEvent.hpp"

using namespace std;

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
CGetMessageEvent::CGetMessageEvent(void)
{
    this->SetEventType(myEVT_THREAD_GET_MESSAGE); // イベントの種類をセット
}


CGetMessageEvent::~CGetMessageEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// メッセージをセット
void CGetMessageEvent::setMessages(const vector<CMessageData*>& messages)
{
    m_messages = messages;
}

// メッセージを取得
vector<CMessageData*> CGetMessageEvent::getMessages(void) const
{
    return m_messages;
}

}
