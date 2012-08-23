#pragma once
#include "ServiceLog.hpp"

namespace CornStarch
{;

// メッセージのログ
class CMessageLog : public CServiceLog
{
private:
    CMessageData* m_message;

public:
    CMessageLog(void);
    ~CMessageLog(void);

    // 初期化を行う
    void init(const CMessageData& message);

    // メッセージを取得する
    CMessageData getMessage(void) const;
    void setMessage(CMessageData* message)
    {
        m_message = message;
    }

};

}
