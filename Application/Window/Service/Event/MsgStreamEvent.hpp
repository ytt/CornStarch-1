#pragma once
#include "ConnectionEventBase.hpp"
#include "../../LogHolder/MessageLog.hpp"

namespace CornStarch
{
;

// メッセージ受信時のイベント
class CMsgStreamEvent: public CConnectionEventBase
{
//private:
//    CMessageData* m_message;
    CMessageLog* m_sericeLog;
public:
    CMsgStreamEvent(void);
    ~CMsgStreamEvent(void);

//    // メッセージを取得する
//    CMessageData getMessage(void) const;
//
//    // メッセージをセットする
//    void setMessage(const CMessageData& message);
    CMessageLog* getServiceLog() const
    {
        return m_sericeLog;
    }

    void setServiceLog(CMessageLog* serverLog)
    {
        m_sericeLog = serverLog;
    }
}

;

}
