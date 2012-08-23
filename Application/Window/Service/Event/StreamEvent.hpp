#ifndef STREAMEVENT_HPP_
#define STREAMEVENT_HPP_

#include "ConnectionEventBase.hpp"
#include "../LogHolder/InviteLog.hpp"
#include "../LogHolder/KickLog.hpp"
#include "../LogHolder/JoinLog.hpp"
#include "../LogHolder/MessageLog.hpp"
#include "../LogHolder/MemberLog.hpp"
#include "../LogHolder/PartLog.hpp"
#include "../LogHolder/TopicLog.hpp"

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


wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CStreamEvent<CPartLog>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CStreamEvent<CMemberLog>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CStreamEvent<CMessageLog>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CStreamEvent<CJoinLog>);
wxDECLARE_EVENT(myEVT_THREAD_INVITE, CStreamEvent<CInviteLog>);
wxDECLARE_EVENT(myEVT_THREAD_KICK, CStreamEvent<CKickLog>);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CStreamEvent<CTopicLog>);

} /* namespace CornStarch */
#endif /* STREAMEVENT_HPP_ */
