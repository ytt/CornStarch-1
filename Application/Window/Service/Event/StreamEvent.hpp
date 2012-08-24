#ifndef STREAMEVENT_HPP_
#define STREAMEVENT_HPP_

#include "ConnectionEventBase.hpp"
#include "../Message/InviteMessage.hpp"
#include "../Message/KickMessage.hpp"
#include "../Message/JoinMessage.hpp"
#include "../Message/ChatMessage.hpp"
#include "../Message/MemberMessage.hpp"
#include "../Message/PartMessage.hpp"
#include "../Message/TopicMessage.hpp"

namespace CornStarch
{



template<typename T>
class CStreamEvent: public CConnectionEventBase
{
    T* m_serviceLog;
public:
    CStreamEvent(wxEventType eventType){
        this->SetEventType(eventType);
    }
    virtual ~CStreamEvent(){}

    T* getServiceLog() const
    {
        return m_serviceLog;
    }

    void setServiceLog(T* serviceLog)
    {
        m_serviceLog = serviceLog;
    }
};


wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CStreamEvent<CPartMessage>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CStreamEvent<CMemberMessage>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CStreamEvent<CChatMessage>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CStreamEvent<CJoinMessage>);
wxDECLARE_EVENT(myEVT_THREAD_INVITE, CStreamEvent<CInviteMessage>);
wxDECLARE_EVENT(myEVT_THREAD_KICK, CStreamEvent<CKickMessage>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CStreamEvent<CTopicMessage>);

} /* namespace CornStarch */
#endif /* STREAMEVENT_HPP_ */
