#include "MsgStreamEvent.hpp"

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
CMsgStreamEvent::CMsgStreamEvent(void)// : m_message(NULL)
{
   this->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
}


CMsgStreamEvent::~CMsgStreamEvent(void)
{
    //delete m_message;
}


//////////////////////////////////////////////////////////////////////
//
//
//// ストリームを取得する
//CMessageData CMsgStreamEvent::getMessage(void) const
//{
//    return *m_message;
//}
//
//// ストリームをセットする
//void CMsgStreamEvent::setMessage(const CMessageData& message)
//{
//    if (m_message == NULL){
//        m_message = new CMessageData();
//    }
//
//    *m_message = message;
//}

}
